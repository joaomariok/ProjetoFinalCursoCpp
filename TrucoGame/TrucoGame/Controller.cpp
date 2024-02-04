#include "pch.h"
#include "Controller.h"

Controller::Controller(CMainWnd* view) :
	view_(view),
	model_(std::make_unique<Model>()) {
}

Controller::~Controller() {
	view_ = nullptr;
}

void Controller::Init(std::string player_one_name, std::string player_two_name) {
	model_->Init(player_one_name, player_two_name);
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
