// CGamingView.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CGamingView.h"
#include "resource.h"

// CGamingView dialog

IMPLEMENT_DYNAMIC(CGamingView, CDialog)

CGamingView::CGamingView(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GAMINGVIEW, pParent)
{
	playerNumber = 0;
	controller = nullptr;
}

CGamingView::~CGamingView()
{
}

void CGamingView::SetController(int playerNumber_, Controller *controller_)
{
	playerNumber = playerNumber_;
	controller = controller_;
}

void CGamingView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BACKGROUND, backgroundImg);
	/*PLAYER 1 ELEMENTS*/
	DDX_Control(pDX, IDC_P1_CARD_ROUND, card_round);
	/*PLAYER 2 ELEMENTS*/
	DDX_Control(pDX, IDC_CARD_P2_1, card_p2_1);
	DDX_Control(pDX, IDC_CARD_P2_2, card_p2_2);
	DDX_Control(pDX, IDC_CARD_P2_3, card_p2_3);
	DDX_Control(pDX, IDC_P2_CARD_ROUND, card_p2_round);
	/*PLAYER 3 ELEMENTS*/
	DDX_Control(pDX, IDC_CARD_P3_1, card_p3_1);
	DDX_Control(pDX, IDC_CARD_P3_2, card_p3_2);
	DDX_Control(pDX, IDC_CARD_P3_3, card_p3_3);
	DDX_Control(pDX, IDC_P3_CARD_ROUND, card_p3_round);
	/*PLAYER 4 ELEMENTS*/
	DDX_Control(pDX, IDC_CARD_P4_1, card_p4_1);
	DDX_Control(pDX, IDC_CARD_P4_2, card_p4_2);
	DDX_Control(pDX, IDC_CARD_P4_3, card_p4_3);
	DDX_Control(pDX, IDC_P4_CARD_ROUND, card_p4_round);

	DDX_Control(pDX, IDC_MANILHA, card_manilha);
	DDX_Control(pDX, IDC_MANILHA_BACK, card_manilha_back);
	DDX_Control(pDX, IDC_TRUCO_P1, word_truco_p1);
	DDX_Control(pDX, IDC_TRUCO_P2, word_truco_p2);
	DDX_Control(pDX, IDC_TRUCO_P4, word_truco_p4);

	DDX_Control(pDX, IDC_SCORE_1, score_1_img);
	DDX_Control(pDX, IDC_SCORE_2, score_2_img);
	DDX_Control(pDX, IDC_SCORE_3, score_3_img);

	DDX_Control(pDX, IDC_PLAYER1_NAME, player1_name);
	DDX_Control(pDX, IDC_PLAYER2_NAME, player2_name);
	DDX_Control(pDX, IDC_PLAYER3_NAME, player3_name);
	DDX_Control(pDX, IDC_PLAYER4_NAME, player4_name);
	DDX_Control(pDX, IDC_PLAYER1_NAME_SCORE, player1_name_score);
	DDX_Control(pDX, IDC_PLAYER2_NAME_SCORE, player2_name_score);
	DDX_Control(pDX, IDC_PLAYER1_SCORE, player1_score);
	DDX_Control(pDX, IDC_PLAYER2_SCORE, player2_score);
	DDX_Control(pDX, IDC_ROUND_VALUE, round_value);
}

BOOL CGamingView::OnInitDialog()
{
	CDialog::OnInitDialog();

	/* DIALOG TITLE */
	CString title;
	title.Format(_T("Jogador %d"), playerNumber);
	SetWindowText(title);

	/* BACKGROUND AND PLAYERS INFO*/
	/*GROUP1: RED, GROUP2: BLUE*/
	int numberOfPlayers = controller->GetNumberOfPlayers();
	CBitmap backgroundBmp;
	if (numberOfPlayers == 2) {
		backgroundBmp.LoadBitmap(IDB_BACKGROUND_2PLAYERS);
		player2_name.ShowWindow(SW_HIDE);
		player4_name.ShowWindow(SW_HIDE);
		for (int i = 1; i <= numberOfPlayers; ++i) {
			Player* player = controller->GetPlayer(i);
			if (player != nullptr) {
				if (i == playerNumber)
					player1_name.SetText(CStringW(player->GetName().c_str()), player->GetGroup() == Player::Group::GROUP_1 ? RGB(0, 0, 255) : RGB(255, 0, 0), 8, true);
				else
					player3_name.SetText(CStringW(player->GetName().c_str()), player->GetGroup() == Player::Group::GROUP_1 ? RGB(0, 0, 255) : RGB(255, 0, 0), 8, true);
			}
		}
	}
	else {
		backgroundBmp.LoadBitmap(IDB_BACKGROUND_4PLAYERS);
		for (int i = 1; i <= numberOfPlayers; ++i) {
			Player* player = controller->GetPlayer(i);
			if (player != nullptr) {
				CTransparentStatic* textComponent = GetStaticComponent(i, numberOfPlayers);
				if (textComponent != nullptr)
					textComponent->SetText(CStringW(player->GetName().c_str()), player->GetGroup() == Player::Group::GROUP_1 ? RGB(0, 0, 255) : RGB(255, 0, 0), 8, true);
			}
		}
	}
	backgroundImg.SetBitmap((HBITMAP)backgroundBmp.Detach());

	/* CREATING CLICKABLE CARDS */
	card_1.Create(_T("Card1"),SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP , CRect(505, 538, 594, 678), this, IDC_CARD_1);
	card_2.Create(_T("Card2"), SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP, CRect(612, 538, 702, 678), this, IDC_CARD_2);
	card_3.Create(_T("Card3"), SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP, CRect(720, 538, 810, 678), this, IDC_CARD_3);

	word_truco_p1.LoadImage(_T("Assets/Truco.png"));
	word_truco_p2.LoadImage(_T("Assets/Truco.png"));
	word_truco_p4.LoadImage(_T("Assets/Truco.png"));

	score_1_img.LoadImage(_T("Assets/Red.png"));
	score_2_img.LoadImage(_T("Assets/Blue.png"));
	score_3_img.LoadImage(_T("Assets/Red.png"));

	LoadCardAsset(&card_manilha, controller->GetVira());
	card_manilha_back.LoadImage(_T("Assets/CardBackRotated.png"));

	return TRUE;
}

void CGamingView::OnPaint()
{
	CPaintDC dc(this);

	/* PAINT ALL PLAYER CARDS */
	int numberOfPlayers = controller->GetNumberOfPlayers();
	for (int i = 1; i <= numberOfPlayers; ++i)
	{
		Player* player = controller->GetPlayer(i);
		if (player != nullptr) {
			std::vector<Card> cards = player->GetHand();
			if (i == playerNumber) { //Is the current player, so it must to show its cards
				LoadCardAsset(&card_1, cards.size() > 0 ? &cards[0] : nullptr);
				LoadCardAsset(&card_2, cards.size() > 1 ? &cards[1] : nullptr);
				LoadCardAsset(&card_3, cards.size() > 2 ? &cards[2] : nullptr);
			}
			else {
				LoadCardBackAsset(GetCardComponent(i, numberOfPlayers, 0), cards.size() > 0 ? &cards[0] : nullptr, numberOfPlayers == 4 ? (playerNumber == 1 ? i == 3 : i == 4) : true);
				LoadCardBackAsset(GetCardComponent(i, numberOfPlayers, 1), cards.size() > 1 ? &cards[1] : nullptr, numberOfPlayers == 4 ? (playerNumber == 1 ? i == 3 : i == 4) : true);
				LoadCardBackAsset(GetCardComponent(i, numberOfPlayers, 2), cards.size() > 2 ? &cards[2] : nullptr, numberOfPlayers == 4 ? (playerNumber == 1 ? i == 3 : i == 4) : true);
			}
		}
	}
	/*PAINT ROUND CARDS*/
	std::vector<Card> discardedCards = controller->GetDiscardedCards();
	if (discardedCards.size() > 0) {
		LoadCardAsset(GetRoundCardComponent(1, numberOfPlayers), discardedCards.size() > 0 ? &discardedCards[0] : nullptr, false);
		LoadCardAsset(GetRoundCardComponent(2, numberOfPlayers), discardedCards.size() > 1 ? &discardedCards[1] : nullptr, false);
		if (numberOfPlayers > 2) {
			LoadCardAsset(GetRoundCardComponent(3, numberOfPlayers), discardedCards.size() > 2 ? &discardedCards[2] : nullptr, false);
			LoadCardAsset(GetRoundCardComponent(4, numberOfPlayers), discardedCards.size() > 3 ? &discardedCards[3] : nullptr, false);
		}
	}
}

void CGamingView::OnBnClickedTrucoBtn()
{
	word_truco_p1.ShowWindow(SW_SHOW);
	SendMessageToParent(TRUCO);
}

void CGamingView::OnBnClickedDesceBtn()
{
	SendMessageToParent(CONTINUE);
}

void CGamingView::OnBnClickedPassoBtn()
{
	SendMessageToParent(QUIT);
}

void CGamingView::OnBnClickedSaveGameBtn()
{
	bool response = controller->SaveGame();
	if (!response) {
		//Call dialog error
	}
}

void CGamingView::OnCard1Clicked()
{
	card_1.ShowWindow(SW_HIDE);
	SendMessageToParent(CARD1_PICKED);
}

void CGamingView::OnCard2Clicked()
{
	card_2.ShowWindow(SW_HIDE);
	SendMessageToParent(CARD2_PICKED);
}

void CGamingView::OnCard3Clicked()
{
	card_3.ShowWindow(SW_HIDE);
	SendMessageToParent(CARD3_PICKED);
}

LRESULT CGamingView::OnCustomMessage(WPARAM wParam, LPARAM lParam)
{
	//Message received
	Invalidate();
	return 0;
}

void CGamingView::SendMessageToParent(GameEvents gameEvent)
{
	::PostMessage(GetParent()->GetSafeHwnd(), WM_CUSTOM_MESSAGE, WPARAM(gameEvent), LPARAM(playerNumber));
}

CTransparentStatic* CGamingView::GetStaticComponent(int playerIndex, int numberOfPlayers)
{
	if (numberOfPlayers == 2) //The position of player 2 is on top
		return playerNumber == playerIndex ? &player1_name : &player3_name;

	if (numberOfPlayers == 4) { //The position of players respect its index
		if (playerNumber == playerIndex)
			return &player1_name;
		if (playerNumber == 1) {
			if (playerIndex == 2)
				return &player2_name;
			else if (playerIndex == 3)
				return &player3_name;
			else if (playerIndex == 4)
				return &player4_name;
		}
		if (playerNumber == 2) {
			if (playerIndex == 3)
				return &player2_name;
			else if (playerIndex == 4)
				return &player3_name;
			else if (playerIndex == 1)
				return &player4_name;
		}
	}
	return nullptr;
}

CTransparentImage* CGamingView::GetCardComponent(int playerIndex, int numberOfPlayers, int cardIndex)
{
	if (numberOfPlayers == 2) //The position of player 2 is on top
		return cardIndex == 0 ? &card_p3_1 : cardIndex == 1 ? &card_p3_2 : &card_p3_3;
	
	if (numberOfPlayers == 4) { //The position of players respect its index
		if (playerNumber == 1) {
			if (playerIndex == 2)
				return cardIndex == 0 ? &card_p2_1 : cardIndex == 1 ? &card_p2_2 : &card_p2_3;
			else if (playerIndex == 3)
				return cardIndex == 0 ? &card_p3_1 : cardIndex == 1 ? &card_p3_2 : &card_p3_3;
			else if (playerIndex == 4)
				return cardIndex == 0 ? &card_p4_1 : cardIndex == 1 ? &card_p4_2 : &card_p4_3;
		}
		if (playerNumber == 2) {
			if (playerIndex == 3)
				return cardIndex == 0 ? &card_p2_1 : cardIndex == 1 ? &card_p2_2 : &card_p2_3;
			else if (playerIndex == 4)
				return cardIndex == 0 ? &card_p3_1 : cardIndex == 1 ? &card_p3_2 : &card_p3_3;
			else if (playerIndex == 1)
				return cardIndex == 0 ? &card_p4_1 : cardIndex == 1 ? &card_p4_2 : &card_p4_3;
		}
	}
	return nullptr;
}

CTransparentImage* CGamingView::GetRoundCardComponent(int playerIndex, int numberOfPlayers)
{
	if (numberOfPlayers == 2) //The position of player 2 is on top
		return playerNumber == playerIndex ? &card_round : &card_p3_round;

	if (numberOfPlayers == 4) { //The position of players respect its index
		if (playerNumber == playerIndex)
			return &card_round;
		if (playerNumber == 1) {
			if (playerIndex == 2)
				return &card_p2_round;
			else if (playerIndex == 3)
				return &card_p3_round;
			else if (playerIndex == 4)
				return &card_p4_round;
		}
		if (playerNumber == 2) {
			if (playerIndex == 3)
				return &card_p2_round;
			else if (playerIndex == 4)
				return &card_p3_round;
			else if (playerIndex == 1)
				return &card_p4_round;
		}
	}
	return nullptr;
}

void CGamingView::LoadCardBackAsset(CTransparentImage* cardComponent, Card* card, bool isHalfCard)
{
	if (cardComponent == nullptr)
		return;

	if (card == nullptr) {
		cardComponent->ShowWindow(SW_HIDE);
		return;
	}
	cardComponent->LoadImage(isHalfCard ? _T("Assets/CardBack2.png") : _T("Assets/CardBackRotated.png"));

}

void CGamingView::LoadCardAsset(CTransparentImage* cardComponent, Card* card, bool hideIfNotExist)
{
	if (cardComponent == nullptr)
		return;

	//Player does not have this card anymore, so hide it
	if (card == nullptr) {
		if (hideIfNotExist) cardComponent->ShowWindow(SW_HIDE);
		return;
	}

	if (!cardComponent->IsWindowVisible())
		cardComponent->ShowWindow(SW_SHOW);

	CString cardSuit, cardRank;

	switch (card->GetSuit()) {
		case Card::Suit::SPADES:
			cardSuit = "Spade";
			break;
		case Card::Suit::HEARTS:
			cardSuit = "Heart";
			break;
		case Card::Suit::DIAMONDS:
			cardSuit = "Diamond";
			break;
		case Card::Suit::CLUBS:
			cardSuit = "Club";
			break;
	}

	switch (card->GetRank()) {
		case Card::Rank::ACE:
			cardRank = "01";
			break;
		case Card::Rank::TWO:
			cardRank = "02";
			break;
		case Card::Rank::THREE:
			cardRank = "03";
			break;
		case Card::Rank::FOUR:
			cardRank = "04";
			break;
		case Card::Rank::FIVE:
			cardRank = "05";
			break;
		case Card::Rank::SIX:
			cardRank = "06";
			break;
		case Card::Rank::SEVEN:
			cardRank = "07";
			break;
		case Card::Rank::JACK:
			cardRank = "11";
			break;
		case Card::Rank::QUEEN:
			cardRank = "12";
			break;
		case Card::Rank::KING:
			cardRank = "13";
			break;
	}
	CString assetsPath;
	assetsPath.Format(_T("Assets/%s%s.png"), cardSuit, cardRank);
	cardComponent->LoadImage(assetsPath);
}

BEGIN_MESSAGE_MAP(CGamingView, CDialog)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_CARD_1, OnCard1Clicked)
	ON_STN_CLICKED(IDC_CARD_2, OnCard2Clicked)
	ON_STN_CLICKED(IDC_CARD_3, OnCard3Clicked)
	ON_BN_CLICKED(IDC_TRUCO_BTN, OnBnClickedTrucoBtn)
	ON_BN_CLICKED(IDC_DESCE_BTN, OnBnClickedDesceBtn)
	ON_BN_CLICKED(IDC_PASSO_BTN, OnBnClickedPassoBtn)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveGameBtn)
	ON_MESSAGE(WM_CUSTOM_MESSAGE, OnCustomMessage)
END_MESSAGE_MAP()
