#pragma once

#include <memory>
#include "Controller.h"
#include "CMaoOnzeDlg.h"

using namespace Utils;

class CGamingView : public CDialog
{
	DECLARE_DYNAMIC(CGamingView)

public:
	CGamingView(CWnd* pParent = nullptr);
	virtual ~CGamingView();

	void SetController(int playerNumber, Controller* controller);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMINGVIEW };
#endif

private:
	CStatic backgroundImg;
	CTransparentStatic player1_name, player2_name, player3_name, player4_name, player1_name_score, player2_name_score, player1_score, player2_score, round_value, current_player;
	CTransparentImage card_1, card_2, card_3, card_round, card_p2_1, card_p2_2, card_p2_3, card_p2_round,
		card_p3_1, card_p3_2, card_p3_3, card_p3_round, card_p4_1, card_p4_2, card_p4_3, card_p4_round,
		card_vira, card_vira_back, word_truco_p1, word_truco_p2, word_truco_p3, word_truco_p4, score_1_img, score_2_img, score_3_img;
	CRect card1_rect, card2_rect, card3_rect;
	CButton check_hide_card_btn;

	int player_number_;
	bool mao_de_onze_dialog_opened = false;
	bool game_over_dialog_opened = false;
	Controller* controller_;

	void HideAnyTrucoImage();
	bool IsHideCardBtnChecked() const;
	void ShowTrucoImageBasedOnPlayerPosition(int gamingViewNumber);
	void LoadCardAsset(CTransparentImage* cardComponent, Card* card, bool hideIfNotExist = true);
	void LoadCardBackAsset(CTransparentImage* cardComponent, Card* card, bool isHalfCard);
	CString GetCardAssetPath(Card* card);
	CTransparentImage* GetCardComponent(int playerIndex, int numberOfPlayers, int cardIndex);
	CTransparentImage* GetRoundCardComponent(int playerIndex, int numberOfPlayers);
	CTransparentStatic* GetStaticComponent(int playerIndex, int numberOfPlayers);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedTrucoBtn();
	afx_msg void OnBnClickedDesceBtn();
	afx_msg void OnBnClickedPassoBtn();
	afx_msg void OnBnClickedSaveGameBtn();
	afx_msg void OnCard1Clicked();
	afx_msg void OnCard2Clicked();
	afx_msg void OnCard3Clicked();
	afx_msg LRESULT OnCustomMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBotPlayMessage(WPARAM wParam, LPARAM lParam);
	void SendMessageToParent(GameEvents gameEvent);

	DECLARE_MESSAGE_MAP()
};
