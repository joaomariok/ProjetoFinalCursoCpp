#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Card.h"

//class Card;
class Deck;
class Player;

class Model
{
public:
	Model() = default;
	~Model() = default;

	void Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers);
	Player* GetPlayer(int position);
	Card* GetVira();

private:
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Player> player_three_ = nullptr;
	std::unique_ptr<Player> player_four_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;
	std::vector<Card*> discarded_cards_;
	Card vira_;
};

