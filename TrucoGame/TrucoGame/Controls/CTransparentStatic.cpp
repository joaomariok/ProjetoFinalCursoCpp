#include "../pch.h"
#include "../framework.h"
#include "CTransparentStatic.h"

IMPLEMENT_DYNAMIC(CTransparentStatic, CStatic)

BOOL CTransparentStatic::OnEraseBkgnd(CDC* /*pDC*/)
{
    // Prevent from default background erasing.
    return FALSE;
}

BOOL CTransparentStatic::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.dwExStyle |= WS_EX_TRANSPARENT;
    return CStatic::PreCreateWindow(cs);
}

HBRUSH CTransparentStatic::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
    pDC->SetBkMode(TRANSPARENT);
    return reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
}

void CTransparentStatic::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();

    const LONG_PTR exStyle = GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
    SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);
}

BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()