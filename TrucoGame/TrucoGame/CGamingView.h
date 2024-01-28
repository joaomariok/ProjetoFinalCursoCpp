#pragma once
#include "afxdialogex.h"


class CGamingView : public CDialog
{
	DECLARE_DYNAMIC(CGamingView)

public:
	CGamingView(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGamingView();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMINGVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void OnPaint();

	DECLARE_MESSAGE_MAP()
};
