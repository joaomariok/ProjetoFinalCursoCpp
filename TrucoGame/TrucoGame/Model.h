#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"

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

		void PlayCard();
		void Truco();
		void AcceptTruco();
		void RunFromTruco();
		Player* GetWinner() { return current_winner_; }
		Player* GetCurrentPlayer() { return current_player_; }
	private:
		std::vector<Player*> players_;
		Player* current_player_ = nullptr;
		Player* current_winner_ = nullptr;
		std::vector<Card> discarded_cards_;
		Card* vira_;
		Player* first_player_;
	};

	class HandRound {
	public:
		HandRound(std::vector<Player*>& players, Deck* deck, Player* first_player);
		~HandRound();

		Card* GetVira() const { return vira_; }
		Player* GetFirstPlayer() const { return first_player_; }
		void InitRound();

		void AcceptTruco();
		void RunFromTruco();
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
	Player* GetPlayer(int position) const;
	Card* GetVira();
    bool GetHasFourPlayers() const;

    Deck GetDeck() const;

    void SetPlayer(int position, Player player);
    void SetDeck(Deck deck);

	int GetCurrentRound() { return current_hand_round_number_; }

	void InitHandRound();

private:
    bool has_four_players_ = false;
	std::unique_ptr<HandRound> current_hand_round_ = nullptr;
	std::unique_ptr<Player> player_one_ = nullptr;
	std::unique_ptr<Player> player_two_ = nullptr;
	std::unique_ptr<Player> player_three_ = nullptr;
	std::unique_ptr<Player> player_four_ = nullptr;
	std::vector<Player*> players_;
	std::unique_ptr<Deck> deck_ = nullptr;
	int current_hand_round_number_ = 0;
};

