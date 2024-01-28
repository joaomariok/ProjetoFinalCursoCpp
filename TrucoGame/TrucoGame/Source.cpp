#include "afxwin.h"
#include "CMainWnd.h"
#include <tuple>

class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL CMyApp::InitInstance() {
	m_pMainWnd = new CMainWnd();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMyApp mfcApp;
