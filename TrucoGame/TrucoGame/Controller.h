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

	void Init(std::string player_one_name, std::string player_two_name);

	std::vector<Card> GetPlayerHand(Player* player);

	void PlayCard(Player* player, Card card, bool visible);

	void Trucar(Player* player, int value);
	void AcceptTruco(Player* player);
	void RunFromTruco(Player* player);

	int GetPlayerScore(Player* player);

private:
	CMainWnd * view_;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	Card vira_;
};
