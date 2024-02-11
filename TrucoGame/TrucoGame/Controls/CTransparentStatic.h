#pragma once

class CTransparentStatic : public CStatic {
	DECLARE_DYNAMIC(CTransparentStatic)

protected:
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT);
	afx_msg void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
};