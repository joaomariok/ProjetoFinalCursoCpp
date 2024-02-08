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
    //Default default constructor 
    Model() = default;
    //Default COPY constructor 
    Model(const Model& other) = default;
    //Default MOVE constructor 
    Model(Model&& other) noexcept = default;
    //Default copy assignment operator 
    Model& operator=(const Model& other) = default;
    //Default move assignment operator 
    Model& operator=(Model&& other) noexcept = default;
    //Default destructor 
    ~Model() = default;

	void Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers);
	Player* GetPlayer(int position) const;
	Card* GetVira();
    bool GetHasFourPlayers() const;

    Deck GetDeck() const;

    void SetPlayer(int position, Player player);
    void SetDeck(Deck deck);

private:
    bool has_four_players_ = false;
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Player> player_three_ = nullptr;
	std::unique_ptr<Player> player_four_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;
	std::vector<Card*> discarded_cards_;
	Card vira_;
};

