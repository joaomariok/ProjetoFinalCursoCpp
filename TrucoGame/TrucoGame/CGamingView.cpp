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
}

CGamingView::~CGamingView()
{
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

	//card_1.ModifyStyle(0, SS_NOTIFY);
	//card_1.SubclassDlgItem(IDC_CARD_1, this);
	//CStatic* backgroundImg = (CStatic*)GetDlgItem(IDC_BACKGROUND);

	CBitmap backgroundBmp;
	backgroundBmp.LoadBitmap(IDB_BACKGROUND_4PLAYERS);
	backgroundImg.SetBitmap((HBITMAP)backgroundBmp.Detach());

	card_1.Create(_T("Card1"),SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP , CRect(505, 538, 594, 678), this, IDC_CARD_1);
	card_1.LoadImage(_T("Assets/Diamond07.png"));
	card_2.Create(_T("Card2"), SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP, CRect(612, 538, 702, 678), this, IDC_CARD_2);
	card_2.LoadImage(_T("Assets/Diamond07.png"));
	card_3.Create(_T("Card3"), SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP | SS_NOTIFY | WS_TABSTOP, CRect(720, 538, 810, 678), this, IDC_CARD_3);
	card_3.LoadImage(_T("Assets/Diamond07.png"));

	card_p2_1.LoadImage(_T("Assets/CardBackRotated.png"));
	card_p2_2.LoadImage(_T("Assets/CardBackRotated.png"));
	card_p2_3.LoadImage(_T("Assets/CardBackRotated.png"));

	card_p3_1.LoadImage(_T("Assets/CardBack2.png"));
	card_p3_2.LoadImage(_T("Assets/CardBack2.png"));
	card_p3_3.LoadImage(_T("Assets/CardBack2.png"));

	card_p4_1.LoadImage(_T("Assets/CardBackRotated.png"));
	card_p4_2.LoadImage(_T("Assets/CardBackRotated.png"));
	card_p4_3.LoadImage(_T("Assets/CardBackRotated.png"));

	word_truco_p1.LoadImage(_T("Assets/Truco.png"));
	word_truco_p2.LoadImage(_T("Assets/Truco.png"));
	word_truco_p4.LoadImage(_T("Assets/Truco.png"));

	score_1_img.LoadImage(_T("Assets/Red.png"));
	score_2_img.LoadImage(_T("Assets/Blue.png"));
	score_3_img.LoadImage(_T("Assets/Red.png"));

	card_manilha.LoadImage(_T("Assets/Club13.png"));
	card_manilha_back.LoadImage(_T("Assets/CardBackRotated.png"));

	return TRUE;
}

void CGamingView::OnPaint()
{
	CPaintDC dc(this);
}

void CGamingView::OnBnClickedTrucoBtn()
{
	word_truco_p1.ShowWindow(SW_SHOW);
}

void CGamingView::OnBnClickedDesceBtn()
{
}

void CGamingView::OnBnClickedPassoBtn()
{
}

void CGamingView::OnCard1Clicked()
{
	card_1.ShowWindow(SW_HIDE);
	card_round.LoadImage(_T("Assets/Diamond07.png"));
	card_round.Invalidate();
}

void CGamingView::OnCard2Clicked()
{
	card_2.ShowWindow(SW_HIDE);
}

void CGamingView::OnCard3Clicked()
{
	card_3.ShowWindow(SW_HIDE);
}

BEGIN_MESSAGE_MAP(CGamingView, CDialog)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_CARD_1, OnCard1Clicked)
	ON_STN_CLICKED(IDC_CARD_2, OnCard2Clicked)
	ON_STN_CLICKED(IDC_CARD_3, OnCard3Clicked)
	ON_BN_CLICKED(IDC_TRUCO_BTN, OnBnClickedTrucoBtn)
	ON_BN_CLICKED(IDC_DESCE_BTN, OnBnClickedDesceBtn)
	ON_BN_CLICKED(IDC_PASSO_BTN, OnBnClickedPassoBtn)
END_MESSAGE_MAP()
