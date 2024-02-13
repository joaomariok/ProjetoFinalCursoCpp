#include "pch.h"
#include "Controller.h"

Controller::Controller(CMainWnd* view) :
	view_(view),
	model_(std::make_unique<Model>()),
	save_(std::make_unique<Save>()) {
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

	if (model_->GetHasFourPlayers() && GetDiscardedCards().size() > 0) {
		Card playedCard = GetDiscardedCards().back();
		BotPlayCard(playerNumber, playedCard, visible);
	}
}

void Controller::BotPlayCard(int challengingplayerNumber, Card challengingCard, bool ischallengingCardVisible) {
	int nextPlayerNumber = challengingplayerNumber < 4 ? challengingplayerNumber + 1 : 0;
	Player* nextPlayer = model_->GetPlayer(nextPlayerNumber);

	// Checks if next player is bot
	Bot* botPlayer = dynamic_cast<Bot*>(nextPlayer);

	if (botPlayer != nullptr) {
		int playCardIndex = botPlayer->DefineWhichCardWillBePlayed(challengingCard);
		PlayCard(nextPlayerNumber, playCardIndex, true);

		//::PostMessage(view_->GetSafeHwnd(), WM_BOT_PLAY_MESSAGE, WPARAM(""), LPARAM(0));
	}
}

bool Controller::LoadGame() {
	bool response = save_->LoadGame(*model_);
	if (response) {
		model_->Init(model_->GetPlayer(1)->GetName(), model_->GetPlayer(2)->GetName(), model_->GetHasFourPlayers());
	}
	return response;
}

bool Controller::SaveGame() {
	return save_->SaveGame(*model_);
}

void Controller::Trucar(Player* player, int value) {
}

void Controller::AcceptTruco(Player* player) {
}

void Controller::RunFromTruco(Player* player) {
}

std::vector<Card> Controller::GetDiscardedCards()
{
	Model::Round* current_round = model_->GetCurrentRound();
	if (current_round != nullptr)
		return current_round->GetDiscardedCards();
	return std::vector<Card>();
}

BOOL Controller::IsPlayerTurn(Player* player)
{
	Model::Round* current_round = model_->GetCurrentRound();
	if (current_round)
		return current_round->GetCurrentPlayer() == player;
	return false;
}

std::vector<Player*> Controller::GetHandRoundWinners()
{
	Model::HandRound* current_handRound = model_->GetCurrentHandRound();
	if (current_handRound)
		return current_handRound->GetHandRoundWinners();
	return std::vector<Player*>();
}

Player* Controller::GetCurrentPlayer()
{
	Model::Round* current_round = model_->GetCurrentRound();
	if (current_round)
		return current_round->GetCurrentPlayer();
	return nullptr;
}

int Controller::GetCurrentHandValue()
{
	Model::HandRound* currentHandRound = model_->GetCurrentHandRound();
	if (currentHandRound)
		return currentHandRound->GetCurrentHandValue();
	return 1;
}
