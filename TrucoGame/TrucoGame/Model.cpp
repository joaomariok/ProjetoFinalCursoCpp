#include "Model.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

void Model::Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers)
{
	if (hasFourPlayers) {
		player_one_ = std::make_unique<Player>(player_one_name);
		player_two_ = std::make_unique<Player>(player_two_name);
		player_three_ = std::make_unique<Player>("Bot player 1");
		player_four_ = std::make_unique<Player>("Bot player 2");

		deck_ = std::make_unique<Deck>();

		std::vector<Card> player_one_hand = deck_->DrawHand();
		player_one_->SetHand(player_one_hand);

		std::vector<Card> player_two_hand = deck_->DrawHand();
		player_two_->SetHand(player_two_hand);

		std::vector<Card> player_three_hand = deck_->DrawHand();
		player_three_->SetHand(player_three_hand);

		std::vector<Card> player_four_hand = deck_->DrawHand();
		player_four_->SetHand(player_four_hand);
	}
	else {
		player_one_ = std::make_unique<Player>(player_one_name);
		player_two_ = std::make_unique<Player>(player_two_name);

		deck_ = std::make_unique<Deck>();

		std::vector<Card> player_one_hand = deck_->DrawHand();
		player_one_->SetHand(player_one_hand);

		std::vector<Card> player_two_hand = deck_->DrawHand();
		player_two_->SetHand(player_two_hand);
	}
	vira_ = deck_->DrawCard();
}

Player* Model::GetPlayer(int position)
{
	switch (position) {
		case 1:
			return player_one_.get();
		case 2:
			return player_two_.get();
		case 3:
			return player_three_.get();
		case 4:
			return player_four_.get();
	}
	return nullptr;
}

Card* Model::GetVira()
{
	return &vira_;
}
