// CMaoOnzeDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CMaoOnzeDlg.h"
#include "resource.h"

// CMaoOnzeDlg dialog

IMPLEMENT_DYNAMIC(CMaoOnzeDlg, CDialog)

CMaoOnzeDlg::CMaoOnzeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAO_ONZE_DLG, pParent)
{

}

CMaoOnzeDlg::~CMaoOnzeDlg()
{
}

void CMaoOnzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BACKGROUND_ONZE, backgroundImg);
	DDX_Control(pDX, IDC_MAO_ONZE_TEXT, mao_onze_text);
	DDX_Control(pDX, IDC_MAO_ONZE_CARD1, card_1);
	DDX_Control(pDX, IDC_MAO_ONZE_CARD2, card_2);
	DDX_Control(pDX, IDC_MAO_ONZE_CARD3, card_3);
}

BOOL CMaoOnzeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap backgroundBmp;
	backgroundBmp.LoadBitmap(IDB_BACKGROUND_ONZE);
	backgroundImg.SetBitmap((HBITMAP)backgroundBmp.Detach());

	mao_onze_text.SetText(L"Estas são as cartas do seu parceiro. Deseja seguir?", RGB(255, 255, 255), 12);

	if (m_assetsPath.size() >= 3) {
		card_1.LoadImage(m_assetsPath[0]);
		card_2.LoadImage(m_assetsPath[1]);
		card_3.LoadImage(m_assetsPath[2]);
	}

	/*CUSTOMIZE BUTTON FONT*/
	CFont font;
	font.CreateFontW(10, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	CButton* viewButton = static_cast<CButton*>(GetDlgItem(ID_YES));
	if (viewButton != nullptr)
		viewButton->SetFont(&font);
	viewButton = static_cast<CButton*>(GetDlgItem(ID_NO));
	if (viewButton != nullptr)
		viewButton->SetFont(&font);

	return TRUE;
}

void CMaoOnzeDlg::OnBnClickedYes()
{
	EndDialog(ID_YES);
}

void CMaoOnzeDlg::OnBnClickedNo()
{
	EndDialog(ID_NO);
}

BEGIN_MESSAGE_MAP(CMaoOnzeDlg, CDialog)
	ON_BN_CLICKED(ID_YES, &CMaoOnzeDlg::OnBnClickedYes)
	ON_BN_CLICKED(ID_NO, &CMaoOnzeDlg::OnBnClickedNo)
END_MESSAGE_MAP()