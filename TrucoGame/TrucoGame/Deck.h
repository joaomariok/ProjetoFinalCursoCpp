#pragma once
#include "Card.h"
#include <vector>

class Deck
{
public:
	Deck();
	~Deck() = default;
	void Shuffle();
	Card DrawCard();
	void AddCard(Card& card);
	std::vector<Card> DrawHand();

private:
	std::vector<Card> cards;
	int currentCardIndex;
	void InitializeDeck();
};