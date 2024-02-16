#pragma once

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Model.h"
#include "Save.h"

class CMainWnd;

class Controller
{
public:
	Controller(CMainWnd* view);
	~Controller();

	void Init(std::string player_one_name, std::string player_two_name, bool has_four_players);

	std::vector<Card> GetPlayerHand(Player* player);

	void PlayCard(int card_index, bool is_hidden = false);

	void Trucar();
	void AcceptTruco();
	void RunFromTruco();
	void RunFromMaoDeOnze();
	bool LoadGame();
	void SaveGame();
	bool ThereIsALoad() { return save_->ThereIsALoad(); }
	int GetPlayerScore(Player* player) { return player->GetScore(); }
	int GetNumberOfPlayers() { return model_->GetHasFourPlayers() ? 4 : 2; }
	Player* GetPlayer(int position) { return model_->GetPlayer(position); }
	Card* GetVira() { return model_->GetVira(); }
	std::vector<Card> GetDiscardedCards();
	bool IsPlayerTurn(Player* player) const;
	bool IsInTrucoState() const;
	bool CanAskForTruco() const;
	bool CanRespondTruco(Player* player) const;
	bool CanPlay(Player* player) const;
	std::vector<Player*> GetHandRoundWinners();
	Player* GetCurrentPlayer();
	Player* GetCurrentTrucoPlayer();
	int GetFirstPlayerIndex() { return model_->GetFirstPlayerIndex(); }
	int GetCurrentHandValue();
	int GetCurrentHandRoundNumber() const { return model_->GetCurrentHandRoundNumber(); }
	int GetCurrentRoundNumber();
	bool IsMaoDeFerro() { return model_->IsMaoDeFerro(); }
	bool IsMaoDeOnze() { return model_->IsMaoDeOnze(); }
	void ShowResponse(int response, std::string inputType);

private:
	CMainWnd* view_;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Save> save_ = nullptr;
};

