#include "Model.h"
#include "Card.h"
#include "Deck.h"

/*
* Auxiliary function to get the next player in vector of players, knowing pointer to current player.
*/
Player* GetNextPlayer(const std::vector<Player*>& players, const Player* current_player) {
	for (size_t i = 0; i < players.size(); i++) {
		if (players.at(i) == current_player) {
			return players.at(i == players.size() - 1 ? 0 : i + 1);
		}
	}

	return nullptr;
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
	if (discarded_cards_.size() == 0/* || <É a maior carta do descarte>*/) {
		current_winner_ = current_player_;
	}
	current_player_ = GetNextPlayer(players_, current_player_);
}

void Model::Round::Truco()
{
	// TODO
}

void Model::Round::AcceptTruco()
{
	// TODO
}

void Model::Round::RunFromTruco()
{
	current_winner_ = current_player_;
}

//////////////////////////////////////////
/// HAND ROUND
Model::HandRound::HandRound(std::vector<Player*>& players, Deck* deck, Player* first_player) :
	players_(players), first_player_(first_player) {
	for (auto player : players) {
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
	current_round_ = std::make_unique<Round>(players_, vira_, GetNextPlayer(players_, previous_winner));
	current_round_number_++;
}

void Model::HandRound::AcceptTruco()
{
	current_hand_value_ = 3;
	current_round_->AcceptTruco();
}

void Model::HandRound::RunFromTruco()
{
	current_hand_value_ = 1;
	current_round_->RunFromTruco();
}

//////////////////////////////////////////
/// MODEL

void Model::Init(std::string player_one_name, std::string player_two_name, bool has_four_players)
{
	player_one_ = std::make_unique<Player>(player_one_name);
	player_two_ = std::make_unique<Player>(player_two_name);
	has_four_players_ = has_four_players;

	players_ = std::vector<Player*>();
	players_.push_back(player_one_.get());
	players_.push_back(player_two_.get());

	if (has_four_players) {
		player_three_ = std::make_unique<Player>("Bot player 1");
		player_four_ = std::make_unique<Player>("Bot player 2");
		players_.push_back(player_three_.get());
		players_.push_back(player_four_.get());
	}

	current_hand_round_number_ = 0;
	InitHandRound();
}

void Model::InitHandRound() {
	deck_ = std::make_unique<Deck>();
	Player* previous_first_player = current_hand_round_ ? current_hand_round_->GetFirstPlayer() : players_.back();
	current_hand_round_ = std::make_unique<HandRound>(players_, deck_.get(), GetNextPlayer(players_, previous_first_player));
	current_hand_round_number_++;
}

Player* Model::GetPlayer(int position) const
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

Card* Model::GetVira() {
	return current_hand_round_->GetVira();
}

bool Model::GetHasFourPlayers() const {
	return has_four_players_;
}

Deck Model::GetDeck() const {
	return *deck_.get();
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