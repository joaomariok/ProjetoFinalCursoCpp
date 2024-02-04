#include "../pch.h"
#include "../framework.h"
#include "CTransparentImage.h"

IMPLEMENT_DYNAMIC(CTransparentImage, CStatic)

CTransparentImage::CTransparentImage() : m_pImage(nullptr) {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CTransparentImage::~CTransparentImage() {
	delete m_pImage;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void CTransparentImage::LoadImage(LPCTSTR pszFileName) {
	delete m_pImage;
	m_pImage = new Gdiplus::Image(pszFileName);
}

void CTransparentImage::afx_msg OnPaint() {
	CPaintDC dc(this);
	if (m_pImage && !m_pImage->GetLastStatus()) {
		Graphics graphics(dc.m_hDC);
		CRect rect;
		GetClientRect(&rect);
		graphics.DrawImage(m_pImage, rect.left, rect.top, rect.Width(), rect.Height());
	}
}

BEGIN_MESSAGE_MAP(CTransparentImage, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()