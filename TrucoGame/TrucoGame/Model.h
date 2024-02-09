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

		Round(std::vector<Player*>& players);

		void PlayCard();
		Player* GetWinner() { return current_winner_; }
	private:
		std::vector<Player*> players_;
		Player* current_player_ = nullptr;
		Player* current_winner_ = nullptr;
		std::vector<Card> discarded_cards_;
		int first_player_ = 0;
	};

	class HandRound {
	public:
		HandRound(std::vector<Player*>& players, Card vira);

		Card GetVira() const { return vira_; }
	private:
		std::unique_ptr<Round> current_round_ = nullptr;
		std::vector<Player*> players_;
		Card vira_;
		int current_hand_value_ = 1;
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

	void Init(std::string player_one_name, std::string player_two_name, bool hasFourPlayers);
	Player* GetPlayer(int position) const;
	Card* GetVira();
    bool GetHasFourPlayers() const;

    Deck GetDeck() const;

    void SetPlayer(int position, Player player);
    void SetDeck(Deck deck);

	int GetCurrentRound() { return current_round_; }

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
	int current_round_ = 0;
};

