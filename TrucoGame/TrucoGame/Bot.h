#pragma once
#include "Player.h"

/*Herança*/
class Bot : public Player
{
public:
	Bot();
	Bot(std::string inputName, Group group, int playerNumber);

	void SetChallengingCard(Card card);
	void SetPercentageToAskAndAcceptTruco(int percentageToAsk, int percentageToAccept);

	bool AskTruco();
	bool AcceptTruco();

	Card PlayCard(int cardIndex) override;
	void SetHand(std::vector<Card>& newHand) override;

private:
	int percentage_to_ask_truco_;
	int percentage_to_accept_truco_;

	Card challenging_card_;

	int MakeTrucoDecision() const;
	bool CardsComparer(Card currentCard, Card nextCard);
};
