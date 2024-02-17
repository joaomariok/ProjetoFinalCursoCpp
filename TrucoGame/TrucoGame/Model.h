#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Card.h"
#include "Bot.h"

class Deck;

class Model
{
public:
	static constexpr int WIN_POINTS = 12;

	class Round {
	public:
		static constexpr int MAX_ROUNDS = 3;

		Round(std::vector<Player*>& players, Card* vira, Player* first_player);
		Round(const Round& other) = default;
		Round(Round&& other) noexcept = default;
		Round& operator=(const Round& other) = default;
		Round& operator=(Round&& other) noexcept = default;
		~Round() = default;

		void PlayCard(int card_index, bool is_hidden = false);
		void Truco();
		void AcceptTruco();
		void RunFromTruco();
		void RunFromMaoDeOnze();
		bool HasWinner() const;
		bool IsInTrucoState() const { return is_in_truco_state_; }
		bool CanAskForTruco() const { return can_ask_for_truco_; }
		bool CanRespondTruco(Player* player) const;

		Player* GetWinner() { return current_winner_; }
		Player* GetCurrentPlayer() { return current_player_; }
		Player* GetCurrentTrucoPlayer() { return current_truco_player_; }
		Player* GetFirstPlayer() { return first_player_; }
		std::vector<Card> GetDiscardedCards() { return discarded_cards_; }
		bool IsRoundFinished() { return current_player_ == first_player_; }
		void ClearRound(Player* first_player);

	private:
		bool WasLastPlayer() const;
		bool DidSomebodyWin() const;
		bool IsBiggestCard(Card card) const;

		std::vector<Player*> players_;
		std::vector<Card> discarded_cards_;

		Player* current_player_ = nullptr;
		Player* current_truco_player_ = nullptr;
		Player* current_winner_ = nullptr;
		Card* vira_;
		Player* first_player_;
		bool is_in_truco_state_ = false;
		bool can_ask_for_truco_ = true;
	};

	class HandRound {
	public:
		enum HandState { MAO_NORMAL, MAO_DE_ONZE, MAO_DE_FERRO };

		HandRound(std::vector<Player*>& players, Deck* deck, Player* first_player);
		HandRound(const HandRound& other) = default;
		HandRound(HandRound&& other) noexcept = default;
		HandRound& operator=(const HandRound& other) = default;
		HandRound& operator=(HandRound&& other) noexcept = default;
		~HandRound();

		void InitRound();

		void PlayCard(int card_index, bool is_hidden = false);
		void Truco();
		void AcceptTruco();
		void RunFromTruco();
		void RunFromMaoDeOnze();
		Player* MaybeGetWinner() const;
		bool CanSeeCardsInHand() const;

		Card* GetVira() const { return vira_; }
		int GetCurrentHandValue() const { return current_hand_value_; }
		int GetCurrentRoundNumber() const { return current_round_number_; }
		Player* GetFirstPlayer() const { return first_player_; }
		Round* GetCurrentRound() { return current_round_.get(); }
		std::vector<Player*> GetRoundWinners() { return round_winners_; };
		void ClearHandRound(Deck* deck, Player* first_player);
		bool IsFinished() const { return is_finished_; }
		HandState GetHandState() { return state_; }

	private:
		void UpdateHandState();
		void IncreaseScoreForWinner();
		bool CanAskForTruco() const;

		std::unique_ptr<Round> current_round_ = nullptr;
		std::vector<Player*> round_winners_;
		std::vector<Player*> players_;

		Player* first_player_;
		Card* vira_;

		HandState state_;
		int current_hand_value_ = 1;
		int current_round_number_ = 0;
		bool is_finished_ = false;
	};

	//Default default constructor 
	Model() = default;
	//Default COPY constructor 
	Model(const Model& other) = default;
	//Default MOVE constructor 
	Model(Model&& other) noexcept = default;
	//Default copy assignment operator 
	Model& operator=(const Model& other) = default;
	//Default move assignment operator 
	Model& operator=(Model&& other) noexcept = default;
	//Default destructor 
	~Model() = default;

	void Init(std::string player_one_name, std::string player_two_name, bool has_four_players);
	void Load(Model* model);

	void InitHandRound();
	void ResetGame();
	void CheckHandRoundFinished();

	void PlayCard(int cardIndex, bool is_hidden = false);

	void SetPlayer(int position, Player player);
	Player* GetPlayer(int position) const;

	void SetDeck(Deck* deck);
	Deck* GetDeck() const;

	Card* GetVira() const;
	bool GetHasFourPlayers() const { return has_four_players_; }
	void SetHasFourPlayers(bool has_four_players);
	int GetCurrentHandRoundNumber() const { return current_hand_round_number_; }
	void SetCurrentHandRoundNumber(int current_hand_round_number) { current_hand_round_number_ = current_hand_round_number; }
	int GetFirstPlayerIndex();
	Model::HandRound* GetCurrentHandRound() { return current_hand_round_.get(); }
	Model::Round* GetCurrentRound() { return current_hand_round_->GetCurrentRound(); }
	bool IsMaoDeOnze() { return current_hand_round_->GetHandState() == HandRound::MAO_DE_ONZE; }
	bool IsMaoDeFerro() { return current_hand_round_->GetHandState() == HandRound::MAO_DE_FERRO; }
	bool IsGameFinished() const { return is_finished_; }

private:
	std::unique_ptr<HandRound> current_hand_round_ = nullptr;
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Bot> player_three_ = nullptr;
	std::unique_ptr<Bot> player_four_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;

	std::vector<Player*> players_;

	int current_hand_round_number_ = 0;
	bool has_four_players_ = false;
	bool is_finished_ = false;
};
