#include "afxwin.h"
#include <tuple>

class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

class CMyWnd : public CFrameWnd {
private:
	CEdit playerOneEdit, playerTwoEdit;
	CButton startButton;
	CStatic titleLabel, playerOneLabel, playerTwoLabel;

public:
	CMyWnd() {
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

	std::tuple<bool, bool> checkIfPlayerNamesAreEmpty() {
		CString playerOneName, playerTwoName;
		playerOneEdit.GetWindowText(playerOneName);
		playerTwoEdit.GetWindowText(playerTwoName);
		return std::make_tuple(playerOneName.Trim().IsEmpty(), playerTwoName.Trim().IsEmpty());
	}

	afx_msg void OnButtonClicked();
	DECLARE_MESSAGE_MAP()
};

BOOL CMyApp::InitInstance() {
	m_pMainWnd = new CMyWnd();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMyWnd, CFrameWnd)
	ON_COMMAND(3, OnButtonClicked)
END_MESSAGE_MAP()

void CMyWnd::OnButtonClicked() {
	bool isPlayerOneEmpty, isPlayerTwoEmpty;

	std::tie(isPlayerOneEmpty, isPlayerTwoEmpty) = checkIfPlayerNamesAreEmpty();

	if (isPlayerOneEmpty || isPlayerTwoEmpty)
		AfxMessageBox(L"Por favor, preencha os nomes dos jogadores antes de iniciar a partida!");
}

CMyApp mfcApp;
