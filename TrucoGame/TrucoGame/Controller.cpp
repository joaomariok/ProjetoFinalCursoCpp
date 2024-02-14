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

void Controller::Init(std::string player_one_name, std::string player_two_name, bool has_four_players) {
	model_->Init(player_one_name, player_two_name, has_four_players);
}

std::vector<Card> Controller::GetPlayerHand(Player* player) {
	return player->GetHand();
}

void Controller::PlayCard(int card_index) {
	model_->PlayCard(card_index);
}

bool Controller::LoadGame() {
	Model tmp_model;
	bool response = save_->LoadGame(tmp_model);
	if (response) {
		model_->Load(tmp_model);
	}
	return response;
}

bool Controller::SaveGame() {
	return save_->SaveGame(*model_);
}

void Controller::Trucar() {
	model_->GetCurrentHandRound()->Truco();
	model_->CheckHandRoundFinished();
}

void Controller::AcceptTruco() {
	model_->GetCurrentHandRound()->AcceptTruco();
	model_->CheckHandRoundFinished();
}

void Controller::RunFromTruco() {
	model_->GetCurrentHandRound()->RunFromTruco();
	model_->CheckHandRoundFinished();
}

std::vector<Card> Controller::GetDiscardedCards()
{
	Model::Round* current_round = model_->GetCurrentRound();
	if (current_round != nullptr)
		return current_round->GetDiscardedCards();
	return std::vector<Card>();
}

bool Controller::IsPlayerTurn(Player* player) const {
	Model::Round* current_round = model_->GetCurrentRound();
	if (current_round)
		return current_round->GetCurrentPlayer() == player;
	return false;
}

bool Controller::IsInTrucoState() const {
	Model::Round* current_round = model_->GetCurrentRound();
	return current_round ? current_round->IsInTrucoState() : false;
}

bool Controller::CanRespondTruco(Player* player) const {
	Model::Round* current_round = model_->GetCurrentRound();
	return current_round ? current_round->CanRespondTruco(player) : false;
}

bool Controller::CanPlay(Player* player) const {
	return IsPlayerTurn(player) && !IsInTrucoState();
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