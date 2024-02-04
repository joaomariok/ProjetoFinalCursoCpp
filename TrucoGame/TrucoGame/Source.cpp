#include "pch.h"
#include "CMainWnd.h"

class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL CMyApp::InitInstance() {

	AfxInitRichEdit();
	AfxOleInit();

	//Registering the custom class to allow its use in TrucoGame.rc
	WNDCLASS wndClass;
	memset(&wndClass, 0, sizeof(WNDCLASS));
	wndClass.lpfnWndProc = ::DefWindowProc;
	wndClass.hInstance = AfxGetInstanceHandle();
	wndClass.lpszClassName = _T("CTransparentImage");
	AfxRegisterClass(&wndClass);

	m_pMainWnd = new CMainWnd();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMyApp mfcApp;
