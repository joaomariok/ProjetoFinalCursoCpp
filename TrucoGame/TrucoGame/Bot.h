#pragma once
#include "Player.h"

/*Herança*/
class Bot : public Player
{
public:
	Bot();
	Bot(std::string name, Group group, int player_number);
	Bot(const Player& other);

	void Reset(const Player& player) override;

	void SetChallengingCard(Card card);

	int GetPercentageToAskTruco() const { return percentage_to_ask_truco_; }
	int GetPercentageToAcceptTruco() const { return percentage_to_accept_truco_; };
	void SetPercentageToAskAndAcceptTruco(int percentage_to_ask_truco, int percentage_to_accept_truco);

	bool AskTruco();
	bool RespondTruco();

	Card PlayCard(int card_index) override;
	void SetHand(std::vector<Card>& new_hand) override;

private:
	int percentage_to_ask_truco_;
	int percentage_to_accept_truco_;

	Card challenging_card_;

	int MakeTrucoDecision() const;
	void CategorizeCards(std::vector<Card>& hand);
};
