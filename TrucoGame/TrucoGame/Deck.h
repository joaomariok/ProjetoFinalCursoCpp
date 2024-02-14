#pragma once
#include "Card.h"
#include <vector>

using Cards = std::vector<Card>;

class Deck
{
public:
	Deck();
	Deck(const Deck& other) = default;
	Deck(Deck&& other) noexcept = default;
	Deck& operator=(const Deck& other) = default;
	Deck& operator=(Deck&& other) noexcept = default;
	~Deck() = default;
	void ResetDeck();
	void Shuffle();
	Card DrawCard();
	void SetManilhas(Card& vira);
	void AddCard(Card& card);
	Cards DrawHand();

private:
	Cards cards_;
	int current_card_index_;
	void InitializeDeck();
};