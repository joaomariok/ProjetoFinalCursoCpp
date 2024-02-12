#pragma once

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Model.h"
#include "Save.h"

class CMainWnd;

class Controller
{
public:
	Controller(CMainWnd* view);
	~Controller();

	void Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers);

	std::vector<Card> GetPlayerHand(Player* player);

	void PlayCard(int playerNumber, int cardIndex, bool visible);
	void BotPlayCard(int challengingplayerNumber, Card challengingCard, bool ischallengingCardVisible);

	void Trucar(Player* player, int value);
	void AcceptTruco(Player* player);
	void RunFromTruco(Player* player);
	bool LoadGame();
	bool SaveGame();
	int GetPlayerScore(Player* player);
	int GetNumberOfPlayers();
	Player* GetPlayer(int position);
	Card* GetVira();
	std::vector<Card> GetDiscardedCards();
	BOOL IsPlayerTurn(Player* player);

private:
	CMainWnd* view_;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Save> save_ = nullptr;
};

