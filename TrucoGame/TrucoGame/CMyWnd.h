#pragma once

#include "afxwin.h"
#include <memory>
#include <tuple>

#include "Controller.h"

class CMyWnd : public CFrameWnd {
private:
	CEdit playerOneEdit, playerTwoEdit;
	CButton startButton;
	CStatic titleLabel, playerOneLabel, playerTwoLabel;

	std::unique_ptr<Controller> controller_ = nullptr;

public:
	CMyWnd();

	std::tuple<bool, bool> checkIfPlayerNamesAreEmpty();

	afx_msg void OnButtonClicked();
	DECLARE_MESSAGE_MAP()
};