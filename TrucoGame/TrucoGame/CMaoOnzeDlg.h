#pragma once
#include "afxdialogex.h"
#include "Controls/CTransparentImage.h"
#include "Controls/CTransparentStatic.h"
#include "Utils.h"
#include <vector>

// CMaoOnzeDlg dialog

class CMaoOnzeDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaoOnzeDlg)

public:
	CMaoOnzeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMaoOnzeDlg();

	std::vector<CString> m_assetsPath;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAO_ONZE_DLG };
#endif
private:
	CStatic backgroundImg;
	CTransparentStatic mao_onze_text;
	CTransparentImage card_1, card_2, card_3;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedNo();
	DECLARE_MESSAGE_MAP()
};
