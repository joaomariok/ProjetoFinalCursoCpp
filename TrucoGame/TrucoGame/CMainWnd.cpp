#include "CMainWnd.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_COMMAND(3, OnButtonClicked)
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	Create(NULL, _T("Truco Game"), WS_OVERLAPPEDWINDOW, CRect(100, 100, 1300, 800));

	titleLabel.Create(_T("♣♠ TRUCO ♠♣"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(240, 100, 960, 200), this);

	CFont* titleFont = new CFont;
	titleFont->CreatePointFont(800, _T("Arial"));
	titleLabel.SetFont(titleFont);

	playerOneLabel.Create(_T("Jogador 1:"), WS_CHILD | WS_VISIBLE, CRect(240, 300, 310, 320), this);
	playerOneEdit.Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(310, 300, 450, 320), this, 1);

	playerTwoLabel.Create(_T("Jogador 2:"), WS_CHILD | WS_VISIBLE, CRect(240, 330, 310, 350), this);
	playerTwoEdit.Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(310, 330, 450, 350), this, 2);

	startButton.Create(_T("Jogar"), WS_CHILD | WS_VISIBLE, CRect(550, 450, 650, 480), this, 3);
}

std::tuple<bool, bool> CMainWnd::checkIfPlayerNamesAreEmpty() {
	CString playerOneName, playerTwoName;
	playerOneEdit.GetWindowText(playerOneName);
	playerTwoEdit.GetWindowText(playerTwoName);
	return std::make_tuple(playerOneName.Trim().IsEmpty(), playerTwoName.Trim().IsEmpty());
}

void CMainWnd::OnButtonClicked() {
	bool isPlayerOneEmpty, isPlayerTwoEmpty;

	std::tie(isPlayerOneEmpty, isPlayerTwoEmpty) = checkIfPlayerNamesAreEmpty();

	if (isPlayerOneEmpty || isPlayerTwoEmpty) {
		AfxMessageBox(L"Por favor, preencha os nomes dos jogadores antes de iniciar a partida!");
		return;
	}

	CString playerOneName, playerTwoName;
	playerOneEdit.GetWindowText(playerOneName);
	playerTwoEdit.GetWindowText(playerTwoName);

	if (gamingView_1.GetSafeHwnd() == NULL) {
		gamingView_1.Create(IDD_GAMINGVIEW, this);
		gamingView_1.ShowWindow(SW_SHOW);
	}
	if (gamingView_2.GetSafeHwnd() == NULL) {
		gamingView_2.Create(IDD_GAMINGVIEW, this);
		gamingView_2.ShowWindow(SW_SHOW);
	}
		 
	//for (int i = 0; i < 2; i++) {
	//	CGamingView* gamingView;
	//	//Verifica se o identificador da janela (HWND) associado a classe é valida
	//	if (gamingView->GetSafeHwnd() == NULL) {
	//		gamingViews.p(gamingView);
	//		gamingView->Create(IDD_GAMINGVIEW, this);
	//		gamingView->ShowWindow(SW_SHOW);
	//	}
	//}

	controller_ = std::make_unique<Controller>(this, std::string("Player 1"), std::string("Player 2"));
}