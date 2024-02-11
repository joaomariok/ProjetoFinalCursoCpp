#include "Model.h"

#include "Card.h"
#include "Deck.h"

namespace player_utils {

/*
* Auxiliary function to get the next player in vector of players, knowing pointer to <current_player>.
*/
Player* GetNextPlayer(const std::vector<Player*>& players, const Player* current_player) {
	for (size_t i = 0; i < players.size(); i++) {
		if (players.at(i) == current_player) {
			return players.at(i == players.size() - 1 ? 0 : i + 1);
		}
	}

	return nullptr;
}

/*
* Auxiliary function to get the player that is in the same group as <current_player>.
*/
Player* GetOtherGroupPlayer(const std::vector<Player*>& players, const Player* current_player) {
	if (current_player->GetGroup() == Player::Group::NO_GROUP) {
		return nullptr;
	}

	for (Player* player : players) {
		if (player != current_player && player->GetGroup() == current_player->GetGroup()) {
			return player;
		}
	}

	return nullptr;
}

}

//////////////////////////////////////////
/// ROUND
Model::Round::Round(std::vector<Player*>& players, Card* vira, Player* first_player) :
	players_(players), vira_(vira), discarded_cards_(std::vector<Card>()), first_player_(first_player) {
	current_player_ = first_player;
}

void Model::Round::PlayCard() {
	Card played_card = current_player_->PlayCard();
	discarded_cards_.push_back(played_card);
	if (discarded_cards_.size() == 1 || IsBiggestCard(played_card)) {
		current_winner_ = current_player_;
	}
	current_player_ = player_utils::GetNextPlayer(players_, current_player_);
	if (current_player_ == first_player_) {
		// Acabou a rodada
		current_winner_->IncreaseRoundScore();
		if (Player* other_player = player_utils::GetOtherGroupPlayer(players_, current_winner_)) {
			other_player->IncreaseRoundScore();
		}
	}
}

void Model::Round::Truco() {
	// TODO
}

void Model::Round::AcceptTruco() {
	// TODO
}

void Model::Round::RunFromTruco() {
	current_winner_ = current_player_;
}

bool Model::Round::HasWinner() const {
	return WasLastPlayer() || DidSomebodyWin();
}

bool Model::Round::WasLastPlayer() const {
	for (Player* player : players_) {
		if (player->GetHand().size() != 0) {
			return false;
		}
	}
	return true;
}

bool Model::Round::DidSomebodyWin() const {
	for (Player* player : players_) {
		if (player->GetRoundScore() >= 2) {
			return true;
		}
	}
	return false;
}

bool Model::Round::IsBiggestCard(Card current_card) const {
	for (Card card : discarded_cards_) {
		if (card.IsBiggerThan(current_card)) {
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////
/// HAND ROUND
Model::HandRound::HandRound(std::vector<Player*>& players, Deck* deck, Player* first_player) :
	players_(players), first_player_(first_player) {
	for (Player* player : players) {
		std::vector<Card> player_hand = deck->DrawHand();
		player->SetHand(player_hand);
	}
	vira_ = new Card(deck->DrawCard());
	current_round_number_ = 0;
	InitRound();
}

Model::HandRound::~HandRound() {
	delete vira_;
}

void Model::HandRound::InitRound() {
	Player* previous_winner = current_round_ ? current_round_->GetWinner() : players_.back();
	current_round_ = std::make_unique<Round>(players_, vira_, player_utils::GetNextPlayer(players_, previous_winner));
	current_round_number_++;
}

void Model::HandRound::PlayCard() {
	current_round_->PlayCard();
	if (current_round_->HasWinner()) {
		Player* winner = current_round_->GetWinner();
		winner->IncreaseScore(current_hand_value_);
		if (Player* other_player = player_utils::GetOtherGroupPlayer(players_, winner)) {
			other_player->IncreaseScore(current_hand_value_);
		}
	}
}

void Model::HandRound::AcceptTruco() {
	current_hand_value_ = 3;
	current_round_->AcceptTruco();
}

void Model::HandRound::RunFromTruco() {
	current_hand_value_ = 1;
	current_round_->RunFromTruco();
}

Player* Model::HandRound::MaybeGetWinner() const {
	for (Player* player : players_) {
		if (player->GetScore() >= WIN_POINTS) {
			return player;
		}
	}
	return nullptr;
}

//////////////////////////////////////////
/// MODEL

void Model::Init(std::string player_one_name, std::string player_two_name, bool has_four_players) {
	player_one_ = std::make_unique<Player>(player_one_name);
	player_two_ = std::make_unique<Player>(player_two_name);
	has_four_players_ = has_four_players;

	players_ = std::vector<Player*>();
	players_.push_back(player_one_.get());
	players_.push_back(player_two_.get());

	if (has_four_players) {
		player_one_->SetGroup(Player::Group::GROUP_1);
		player_two_->SetGroup(Player::Group::GROUP_2);
		player_three_ = std::make_unique<Player>("Bot player 1", Player::Group::GROUP_1);
		player_four_ = std::make_unique<Player>("Bot player 2", Player::Group::GROUP_2);
		players_.push_back(player_three_.get());
		players_.push_back(player_four_.get());
	}

	ResetGame();
}

void Model::InitHandRound() {
	deck_ = std::make_unique<Deck>();
	Player* previous_first_player = current_hand_round_ ? current_hand_round_->GetFirstPlayer() : players_.back();
	current_hand_round_ = std::make_unique<HandRound>(players_, deck_.get(), player_utils::GetNextPlayer(players_, previous_first_player));
	current_hand_round_number_++;
}

void Model::ResetGame() {
	current_hand_round_number_ = 0;
	current_hand_round_ = nullptr;
	InitHandRound();
}

void Model::PlayCard() {
	current_hand_round_->PlayCard();
	Player* winner = current_hand_round_->MaybeGetWinner();
	if (winner) {
		// Game finished
	}
}

Player* Model::GetPlayer(int position) const {
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

Card* Model::GetVira() const {
	return current_hand_round_->GetVira();
}

Deck* Model::GetDeck() const {
	return deck_.get();
}

void Model::SetPlayer(int position, Player player) {
	switch (position) {
		case 1:
			player_one_ = std::make_unique<Player>(player);
		case 2:
			player_two_ = std::make_unique<Player>(player);
		case 3:
			player_three_ = std::make_unique<Player>(player);
		case 4:
			player_four_ = std::make_unique<Player>(player);
	}
}

void Model::SetDeck(Deck deck) {
	deck_ = std::make_unique<Deck>(deck);
}