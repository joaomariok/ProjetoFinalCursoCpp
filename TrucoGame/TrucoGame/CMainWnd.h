#pragma once

#include "Controller.h"
#include "CGamingView.h"
#include "resource.h"

class CMainWnd : public CFrameWnd {
private:
	CBitmap backgroundBmp;
	CEdit playerOneEdit, playerTwoEdit;
	CButton startButton, loadGameButton, twoPlayersRBtn, fourPlayerRBtn;
	CStatic background, playerOneLabel, playerTwoLabel;
	CGamingView gamingView_1, gamingView_2;

	bool hasFourPlayers;
	std::unique_ptr<Controller> controller_ = nullptr;

public:
	CMainWnd();
	~CMainWnd();

	std::tuple<bool, bool> checkIfPlayerNamesAreEmpty();

	afx_msg void OnButtonClicked();
	afx_msg void OnLoadGameButtonClicked();
	afx_msg void OnTwoPlayersClicked();
	afx_msg void OnFourPlayersClicked();
	afx_msg LRESULT OnCustomMessage(WPARAM wParam, LPARAM lParam);
	void SendMessageToGamingView(CGamingView* gamingView);
	DECLARE_MESSAGE_MAP()
};