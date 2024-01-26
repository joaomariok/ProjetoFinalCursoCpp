#include "Deck.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <ctime>

Deck::Deck() {
	currentCardIndex = 0;
	InitializeDeck();
}

void Deck::InitializeDeck() {
	for (int suit = Card::SPADES; suit <= Card::CLUBS; ++suit) {
		for (int rank = Card::TWO; rank <= Card::ACE; ++rank) {
			cards.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
		}
	}
}

void Deck::Shuffle() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
	currentCardIndex = 0;
}

Card Deck::DrawCard() {
	if (currentCardIndex < cards.size()) {
		return cards[currentCardIndex++];
	}
	// Handle out-of-cards situation (e.g., reshuffle or end of the game)
	// For simplicity, this example does not implement reshuffling.
	return Card(Card::Suit::SPADES, Card::Rank::TWO);
}

void Deck::AddCard(Card& card) {
	cards.push_back(card);
}

std::vector<Card> Deck::DrawHand() {
	std::vector<Card> hand = std::vector<Card>();
	hand.push_back(DrawCard());
	hand.push_back(DrawCard());
	hand.push_back(DrawCard());
	return hand;
}
