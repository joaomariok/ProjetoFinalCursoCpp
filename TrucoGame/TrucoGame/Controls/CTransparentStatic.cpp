#include "../pch.h"
#include "../framework.h"
#include "CTransparentStatic.h"

IMPLEMENT_DYNAMIC(CTransparentStatic, CStatic)

void CTransparentStatic::SetText(LPCTSTR lpszText, COLORREF color, int size, BOOL center)
{
    m_strText = lpszText;
    fontSize = size;
    foreground = color;
    alignCenter = center;
    Invalidate();
}

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
    CFont font;
    font.CreatePointFont(100, _T("Arial"));
    LOGFONT lf;
    font.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    font.DeleteObject();
    font.CreateFontIndirect(&lf);
    pDC->SelectObject(&font);

    pDC->SetTextColor(foreground);
    pDC->SetBkMode(TRANSPARENT);

    return reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
}

void CTransparentStatic::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();

    const LONG_PTR exStyle = GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
    SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);
}

void CTransparentStatic::OnPaint()
{
    CPaintDC dc(this);

    CFont font;
    font.CreatePointFont(fontSize * 10, _T("Arial"));

    LOGFONT lf;
    font.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;

    font.DeleteObject();
    font.CreateFontIndirect(&lf);
    dc.SelectObject(&font);

    CRect rcClient;
    GetClientRect(&rcClient);

    dc.SetTextColor(foreground);
    dc.SetBkMode(TRANSPARENT);

    CString m_string;
    GetWindowText(m_string);
    dc.DrawText(m_strText != "" ? m_strText : m_string, &rcClient, (alignCenter ? DT_CENTER : DT_LEFT) | DT_TOP | DT_VCENTER | DT_SINGLELINE);

    CStatic::OnPaint();
}

BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_PAINT()
END_MESSAGE_MAP()