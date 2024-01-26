#pragma once

#include <memory>
#include <vector>

class Card;
class Deck;
class Player;

class Model
{
public:
	Model() = default;
	~Model() = default;

private:
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;
	std::vector<Card*> discarded_cards_;
};

