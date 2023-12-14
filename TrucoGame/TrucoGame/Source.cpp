#include "afxwin.h"

class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

class CMyWnd : public CFrameWnd {
private:
	CEdit edit;
	CButton button;

public:
	CMyWnd() {
		Create(NULL, _T("Windows MFC"), WS_OVERLAPPEDWINDOW, CRect(100, 100, 1200, 800));

		edit.Create(WS_CHILD | WS_BORDER | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			CRect(50, 50, 450, 250), this, 1);

		button.Create(_T("Enviar"), WS_CHILD | WS_VISIBLE, CRect(470, 220, 570, 250), this, 2);
	}

	CString getEditText() {
		CString textString;
		edit.GetWindowText(textString);
		return textString;
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
	ON_COMMAND(2, OnButtonClicked)
END_MESSAGE_MAP()

void CMyWnd::OnButtonClicked() {
	CString editText = getEditText();
	AfxMessageBox(editText);
}

CMyApp mfcApp;
