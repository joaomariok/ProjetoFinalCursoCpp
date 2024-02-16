#include "pch.h"
#include "framework.h"
#include <tuple>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include "CMainWnd.h"

CMainWnd::CMainWnd() {
	Create(NULL, _T("Truco Game"), DS_MODALFRAME | DS_CENTER | WS_POPUP | WS_CAPTION | WS_SYSMENU, CRect(100, 100, 1420, 940));

	background.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, 1300, 800), this);
	backgroundBmp.LoadBitmap(IDB_BACKGROUNDMENU);
	background.SetBitmap((HBITMAP)backgroundBmp.Detach());

	playerOneLabel.Create(_T("Jogador 1:"), WS_CHILD | WS_VISIBLE | SS_NOTIFY, CRect(350, 340, 420, 360), this);
	playerOneEdit.Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(450, 340, 590, 360), this, 1);

	playerTwoLabel.Create(_T("Jogador 2:"), WS_CHILD | WS_VISIBLE, CRect(350, 370, 420, 390), this);
	playerTwoEdit.Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(450, 370, 590, 390), this, 2);

	startButton.Create(_T("Jogar"), WS_CHILD | WS_VISIBLE, CRect(375, 470, 622, 500), this, 3);

	loadGameButton.Create(_T("Carregar Jogo"), WS_CHILD | WS_VISIBLE, CRect(665, 470, 912, 500), this, 6);

	twoPlayersRBtn.Create(_T("2 jogadores"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(725, 340, 972, 360), this, 4);
	fourPlayerRBtn.Create(_T("4 jogadores"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(725, 370, 972, 390), this, 5);

	twoPlayersRBtn.SetCheck(BST_CHECKED);
	hasFourPlayers = false;
}

CMainWnd::~CMainWnd() {}

std::tuple<bool, bool> CMainWnd::CheckIfPlayerNamesAreEmpty() {
	CString playerOneName, playerTwoName;
	playerOneEdit.GetWindowText(playerOneName);
	playerTwoEdit.GetWindowText(playerTwoName);
	return std::make_tuple(playerOneName.Trim().IsEmpty(), playerTwoName.Trim().IsEmpty());
}

void CMainWnd::InitGameViews() {
	if (!controller_) {
		// Safe guard if controller is null
		return;
	}

	if (gamingView_2.GetSafeHwnd() == NULL) {
		gamingView_2.SetController(2, controller_.get());
		gamingView_2.Create(IDD_GAMINGVIEW, this);
		gamingView_2.ShowWindow(SW_SHOW);
	}
	if (gamingView_1.GetSafeHwnd() == NULL) {
		gamingView_1.SetController(1, controller_.get());
		gamingView_1.Create(IDD_GAMINGVIEW, this);
		gamingView_1.ShowWindow(SW_SHOW);
	}
	startButton.EnableWindow(FALSE);

	std::thread([&]() {
		while (gamingView_1.IsWindowVisible() && gamingView_2.IsWindowVisible())
		{
			OutputDebugStringW(L"Starting Bot thread\n");

			Bot* botPlayer = dynamic_cast<Bot*>(controller_->GetCurrentPlayer());
			Bot* trucoBotPlayer = dynamic_cast<Bot*>(controller_->GetCurrentTrucoPlayer());

			if (botPlayer || trucoBotPlayer) {
				GameEvents gameEvent = NONE;

				if (controller_->IsInTrucoState()) {
					if (trucoBotPlayer != NULL)
						gameEvent = ExecuteBotDecisionMaking(*trucoBotPlayer);
					else
						continue;
				}
				else if (botPlayer != NULL) {
					gameEvent = ExecuteBotDecisionMaking(*botPlayer);
				}
				else {
					continue;
				}

				SendBotMessageToGamingView(&gamingView_1, gameEvent, 1);
				SendBotMessageToGamingView(&gamingView_2, gameEvent, 2);
			}

			OutputDebugStringW(L"Sleeping for 4 seconds\n");
			std::this_thread::sleep_for(std::chrono::seconds(4));
		}
		}).detach();
}

GameEvents CMainWnd::ExecuteBotDecisionMaking(Bot& bot) {
	GameEvents gameEvent = NONE;

	if (controller_->CanRespondTruco(&bot)) {
		if (bot.RespondTruco()) {
			gameEvent = CONTINUE;
			OnCustomMessage(CONTINUE, 0);
		}
		else {
			gameEvent = QUIT;
			OnCustomMessage(QUIT, 0);
		}
	}
	else if (!controller_->IsInTrucoState() && controller_->CanAskForTruco() && bot.AskTruco()) {
		gameEvent = TRUCO;
		OnCustomMessage(TRUCO, 0);
	}
	else {
		controller_->PlayCard(0);
	}

	return gameEvent;
}

void CMainWnd::OnButtonClicked() {
	bool isPlayerOneEmpty, isPlayerTwoEmpty;

	std::tie(isPlayerOneEmpty, isPlayerTwoEmpty) = CheckIfPlayerNamesAreEmpty();

	if (isPlayerOneEmpty || isPlayerTwoEmpty) {
		AfxMessageBox(L"Por favor, preencha os nomes dos jogadores antes de iniciar a partida!");
		return;
	}

	CString playerOneName, playerTwoName;
	playerOneEdit.GetWindowText(playerOneName);
	playerTwoEdit.GetWindowText(playerTwoName);

	std::string playerOneString(CW2A(playerOneName.GetString()));
	std::string playerTwoString(CW2A(playerTwoName.GetString()));

	if (!controller_) {
		controller_ = std::make_unique<Controller>(this);
	}
	controller_->Init(playerOneString, playerTwoString, hasFourPlayers);

	InitGameViews();
}

void CMainWnd::OnLoadGameButtonClicked() {
	if (gamingView_1.GetSafeHwnd() != NULL || gamingView_2.GetSafeHwnd() != NULL) {
		AfxMessageBox(L"Uma partida já foi iniciada nessa instância. Por favor reabra o programa para carregar um jogo salvo.");
	}
	else {
		controller_ = std::make_unique<Controller>(this);
		if (!controller_->ThereIsALoad()) {
			AfxMessageBox(L"Não há um jogo salvo para carregar. Inicie um novo jogo e clique no botão Salvar.");
		}
		else if (controller_->LoadGame()) {
			InitGameViews();
		}
	}
}

void CMainWnd::OnTwoPlayersClicked() {
	hasFourPlayers = false;
}

void CMainWnd::OnFourPlayersClicked() {
	hasFourPlayers = true;
}

LRESULT CMainWnd::OnCustomMessage(WPARAM wParam, LPARAM lParam) {
	//Message received
	GameEvents gameEvent = static_cast<GameEvents>(wParam);
	int playerNumber = static_cast<int>(lParam);
	bool alreadySentEvent = false;

	switch (gameEvent) {
	case CARD1_PICKED:
		controller_->PlayCard(0);
		break;
	case CARD1_PICKED_HIDDEN:
		controller_->PlayCard(0, true);
		break;
	case CARD2_PICKED:
		controller_->PlayCard(1);
		break;
	case CARD2_PICKED_HIDDEN:
		controller_->PlayCard(1, true);
		break;
	case CARD3_PICKED:
		controller_->PlayCard(2);
		break;
	case CARD3_PICKED_HIDDEN:
		controller_->PlayCard(2, true);
		break;
	case TRUCO:
		controller_->Trucar();
		if (playerNumber == 1) {
			SendMessageToGamingView(&gamingView_2, TRUCO_FROM_OPPONENT);
			alreadySentEvent = true;
		}
		else if (playerNumber == 2) {
			SendMessageToGamingView(&gamingView_1, TRUCO_FROM_OPPONENT);
			alreadySentEvent = true;
		}
		break;
	case CONTINUE:
		controller_->AcceptTruco();
		break;
	case QUIT:
		controller_->RunFromTruco();
		break;
	case RUN_FROM_MAO_DE_ONZE:
		controller_->RunFromMaoDeOnze();
		break;
	default:
		break;
	}

	//Send message to update the views
	if (!alreadySentEvent) {
		SendMessageToGamingView(&gamingView_1, NONE);
		SendMessageToGamingView(&gamingView_2, NONE);
	}

	return 0;
}

void CMainWnd::SendMessageToGamingView(CGamingView* gamingView, GameEvents gameEvent) {
	::PostMessage(gamingView->GetSafeHwnd(), WM_CUSTOM_MESSAGE, WPARAM(gameEvent), LPARAM(0));
}

void CMainWnd::SendBotMessageToGamingView(CGamingView* gamingView, GameEvents gameEvent, int gamingViewNumber) {
	::PostMessage(gamingView->GetSafeHwnd(), WM_BOT_PLAY_MESSAGE, WPARAM(gameEvent), LPARAM(gamingViewNumber));
}

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_BN_CLICKED(3, OnButtonClicked)
	ON_BN_CLICKED(6, OnLoadGameButtonClicked)
	ON_BN_CLICKED(4, OnTwoPlayersClicked)
	ON_BN_CLICKED(5, OnFourPlayersClicked)
	ON_MESSAGE(WM_CUSTOM_MESSAGE, OnCustomMessage)
END_MESSAGE_MAP()