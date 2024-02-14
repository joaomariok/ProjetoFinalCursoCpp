#pragma once
#include "Player.h"

/*Herança*/
class Bot : public Player
{
public:
	Bot();
	Bot(std::string inputName, Group group, int playerNumber);

	void SetChallengingCard(Card card);
	void SetPercentageToChallengeTruco(int percentage);

	bool MakeTrucoDecision() const;

	Card PlayCard(int cardIndex) override;
	void SetHand(std::vector<Card>& newHand) override;

private:
	int percentage_to_challenge_truco_;

	Card challenging_card_;

	bool CardsComparer(Card currentCard, Card nextCard);
};
