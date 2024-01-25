#pragma once
#include "Card.h"
#include <vector>
#include <algorithm>
#include <ctime>

class Deck
{
private:
	std::vector<Card> cards;
	int currentCardIndex;
	void InitializeDeck();

public:
	Deck();
	void Shuffle();
	Card DrawCard();
	void AddCard(Card& card);
	std::vector<Card> DrawHand();
};