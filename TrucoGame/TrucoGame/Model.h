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
		~Round() = default;

		void PlayCard(int cardIndex);
		void Truco();
		void AcceptTruco();
		void RunFromTruco();
		bool HasWinner() const;

		Player* GetWinner() { return current_winner_; }
		Player* GetCurrentPlayer() { return current_player_; }

	private:
		bool WasLastPlayer() const;
		bool DidSomebodyWin() const;
		bool IsBiggestCard(Card card) const;

		std::vector<Player*> players_;
		std::vector<Card> discarded_cards_;

		Player* current_player_ = nullptr;
		Player* current_winner_ = nullptr;
		Card* vira_;
		Player* first_player_;
	};

	class HandRound {
	public:
		HandRound(std::vector<Player*>& players, Deck* deck, Player* first_player);
		~HandRound();

		void InitRound();

		void PlayCard(int cardIndex);
		void AcceptTruco();
		void RunFromTruco();
		Player* MaybeGetWinner() const;

		Card* GetVira() const { return vira_; }
		Player* GetFirstPlayer() const { return first_player_; }

	private:
		std::unique_ptr<Round> current_round_ = nullptr;

		std::vector<Player*> players_;

		Player* first_player_;
		Card* vira_;

		int current_hand_value_ = 1;
		int current_round_number_ = 0;
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

	void InitHandRound();
	void ResetGame();

	void PlayCard(int cardIndex);

    void SetPlayer(int position, Player player);
	Player* GetPlayer(int position) const;

    void SetDeck(Deck deck);
    Deck* GetDeck() const;

	Card* GetVira() const;
	bool GetHasFourPlayers() const { return has_four_players_; }
	int GetCurrentRound() const { return current_hand_round_number_; }

private:
	std::unique_ptr<HandRound> current_hand_round_ = nullptr;
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Player> player_three_ = nullptr;
	std::unique_ptr<Player> player_four_ = nullptr;
	std::unique_ptr<Deck> deck_ = nullptr;

	std::vector<Player*> players_;

	int current_hand_round_number_ = 0;
    bool has_four_players_ = false;
};

