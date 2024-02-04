#pragma once

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

class CTransparentImage : public CStatic {
	DECLARE_DYNAMIC(CTransparentImage)

public:
	CTransparentImage();
	virtual ~CTransparentImage();
	void LoadImage(LPCTSTR pszFileName);

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::Image* m_pImage;
	ULONG_PTR gdiplusToken;
};