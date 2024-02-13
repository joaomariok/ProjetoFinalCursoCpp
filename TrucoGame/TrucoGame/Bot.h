#pragma once
#include "Player.h"

/*Herança*/
class Bot : public Player
{
public:
	Bot();
	Bot(std::string inputName, Group group, int playerNumber);

	void SetChallengingCard(Card card);

	Card PlayCard(int cardIndex) override;
	void SetHand(std::vector<Card>& newHand) override;

private:
	Card challenging_card_;
	bool CardsComparer(Card currentCard, Card nextCard);
};
