#pragma once

#include <memory>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Model.h"

class CMainWnd;

class Controller
{
public:
	Controller(CMainWnd* view);
	~Controller();

	void Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers);

	std::vector<Card> GetPlayerHand(Player* player);

	void PlayCard(int cardIndex);

	void Trucar(Player* player, int value);
	void AcceptTruco(Player* player);
	void RunFromTruco(Player* player);
	int GetPlayerScore(Player* player);
	int GetNumberOfPlayers();
	Player* GetPlayer(int position);
	Card* GetVira();
	std::vector<Card> GetDiscardedCards();

private:
	CMainWnd* view_;
	std::unique_ptr<Model> model_ = nullptr;
};

