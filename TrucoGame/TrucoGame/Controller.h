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
	int GetPlayerScore(Player* player) { return player->GetScore(); }
	int GetNumberOfPlayers() { return model_->GetHasFourPlayers() ? 4 : 2; }
	Player* GetPlayer(int position) { return model_->GetPlayer(position); }
	Card* GetVira() { return model_->GetVira(); }
	std::vector<Card> GetDiscardedCards();
	BOOL IsPlayerTurn(Player* player);
	std::vector<Player*> GetHandRoundWinners();
	Player* GetCurrentPlayer();
	int GetFirstPlayerIndex() { return model_->GetFirstPlayerIndex(); }
	int GetCurrentHandValue();

private:
	CMainWnd* view_;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Save> save_ = nullptr;
};

