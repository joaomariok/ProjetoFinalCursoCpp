#pragma once

#include "Controller.h"
#include "CGamingView.h"
#include "resource.h"

class CMainWnd : public CFrameWnd {
private:
	CEdit playerOneEdit, playerTwoEdit;
	CButton startButton;
	CStatic titleLabel, playerOneLabel, playerTwoLabel;
	CGamingView gamingView_1, gamingView_2;
	
	std::unique_ptr<Controller> controller_ = nullptr;

public:
	CMainWnd();

	std::tuple<bool, bool> checkIfPlayerNamesAreEmpty();

	afx_msg void OnButtonClicked();
	DECLARE_MESSAGE_MAP()
};