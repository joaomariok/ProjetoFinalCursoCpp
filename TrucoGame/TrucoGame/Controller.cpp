#include "Controller.h"

Controller::Controller(CMyWnd* view, std::string player_one_name, std::string player_two_name) :
	view_(view),
	player_one_(std::make_unique<Player>(player_one_name)),
	player_two_(std::make_unique<Player>(player_two_name)) {
	deck_ = std::make_unique<Deck>();

	std::vector<Card> player_one_hand = deck_->DrawHand();
	player_one_->SetHand(player_one_hand);

	std::vector<Card> player_two_hand = deck_->DrawHand();
	player_two_->SetHand(player_two_hand);

	vira_ = deck_->DrawCard();
}

Controller::~Controller() {
	view_ = nullptr;
}

std::vector<Card> Controller::GetPlayerHand(Player* player) {
	return player->GetHand();
}

void Controller::PlayCard(Player* player, Card card, bool visible) {
}

void Controller::Trucar(Player* player, int value) {
}

void Controller::AcceptTruco(Player* player) {
}

void Controller::RunFromTruco(Player* player) {
}

int Controller::GetPlayerScore(Player* player) {
	return player->GetScore();
}
