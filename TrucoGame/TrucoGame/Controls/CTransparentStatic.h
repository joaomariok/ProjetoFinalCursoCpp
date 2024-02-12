#pragma once

class CTransparentStatic : public CStatic {
	DECLARE_DYNAMIC(CTransparentStatic)
public:
	void SetText(LPCTSTR lpszText, COLORREF color = RGB(0,0,0), int fonSize = 10, BOOL alignCenter = false);

protected:
	CString m_strText;
	COLORREF foreground = RGB(0,0,0);
	int fontSize = 10;
	BOOL alignCenter = false;
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT);
	afx_msg void PreSubclassWindow();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};