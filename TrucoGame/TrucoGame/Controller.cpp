#include "pch.h"
#include "Controller.h"

Controller::Controller(CMainWnd* view) :
	view_(view),
	model_(std::make_unique<Model>()) {
}

Controller::~Controller() {
	view_ = nullptr;
}

void Controller::Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers) {
	model_->Init(player_one_name, player_two_name, hasFourPlayers);
}

std::vector<Card> Controller::GetPlayerHand(Player* player) {
	return player->GetHand();
}

void Controller::PlayCard(int playerNumber, int cardIndex, bool visible) {
	model_->PlayCard(cardIndex);
	Card playedCard = model_->GetLastDiscardedCard();

	if (model_->GetHasFourPlayers())
		BotPlayCard(playerNumber, playedCard, visible);
}

void Controller::BotPlayCard(int challengingplayerNumber, Card challengingCard, bool ischallengingCardVisible) {
	int nextIndex = challengingplayerNumber < 4 ? challengingplayerNumber + 1 : 0;
	Player* nextPlayer = model_->GetPlayer(nextIndex);

	Bot* botPlayer = dynamic_cast<Bot*>(nextPlayer);

	if (botPlayer != nullptr) {
		//...
	}
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

int Controller::GetNumberOfPlayers()
{
	return model_->GetHasFourPlayers() ? 4 : 2;
}

Player* Controller::GetPlayer(int position)
{
	return model_->GetPlayer(position);
}

Card* Controller::GetVira()
{
	return model_->GetVira();
}
