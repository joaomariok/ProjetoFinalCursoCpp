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
	Card playedCard = GetDiscardedCards().back();

	if (model_->GetHasFourPlayers())
		BotPlayCard(playerNumber, playedCard, visible);
}

void Controller::BotPlayCard(int challengingplayerNumber, Card challengingCard, bool ischallengingCardVisible) {
	int nextIndex = challengingplayerNumber < 4 ? challengingplayerNumber + 1 : 0;
	Player* nextPlayer = model_->GetPlayer(nextIndex);
	Bot* botPlayer = dynamic_cast<Bot*>(nextPlayer);

	if (botPlayer != nullptr) {
		// Bot cards are sorted from weakest to strongest
		botPlayer->SortCards();
		std::vector<Card> botCards = botPlayer->GetHand();

		for (int i = 0; i < botCards.size(); i++) {
			// Plays the first cars that is bigger than challengingCard
			if (botCards[i].IsBiggerThan(challengingCard)) {
				PlayCard(nextIndex, i, true);
				break;
			}
			// If no card is bigger than challengingCard, just plays the weakest one
			else if (i == botCards.size() - 1) {
				PlayCard(nextIndex, 0, true);
				break;
			}
		}

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
	if (current_round != nullptr)
	{
		return current_round->GetCurrentPlayer() == player;
	}
	return false;
}
