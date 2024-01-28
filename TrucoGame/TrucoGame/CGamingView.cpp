// CGamingView.cpp : implementation file
//

//#include "pch.h"
#include "afxdialogex.h"
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
}

void CGamingView::OnPaint()
{

}


BEGIN_MESSAGE_MAP(CGamingView, CDialog)
END_MESSAGE_MAP()


// CGamingView message handlers
