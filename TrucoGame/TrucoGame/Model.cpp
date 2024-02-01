#include "Model.h"

#include "Card.h"
#include "Deck.h"
#include "Player.h"

void Model::Init(std::string player_one_name, std::string player_two_name)
{
	player_one_ = std::make_unique<Player>(player_one_name);
	player_two_ = std::make_unique<Player>(player_two_name);

	deck_ = std::make_unique<Deck>();

	std::vector<Card> player_one_hand = deck_->DrawHand();
	player_one_->SetHand(player_one_hand);

	std::vector<Card> player_two_hand = deck_->DrawHand();
	player_two_->SetHand(player_two_hand);

	vira_ = deck_->DrawCard();
}
