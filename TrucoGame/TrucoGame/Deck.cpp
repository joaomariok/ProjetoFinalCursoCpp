#include "Deck.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <ctime>

Deck::Deck() {
	ResetDeck();
}

void Deck::ResetDeck() {
	current_card_index_ = 0;
	InitializeDeck();
	Shuffle();
}

void Deck::InitializeDeck() {
	for (int suit = Card::DIAMONDS; suit <= Card::CLUBS; ++suit) {
		for (int rank = Card::FOUR; rank <= Card::THREE; ++rank) {
			cards_.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
		}
	}
}

void Deck::Shuffle() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards_.begin(), cards_.end(), g);
	current_card_index_ = 0;
}

Card Deck::DrawCard() {
	if (current_card_index_ < cards_.size()) {
		return cards_[current_card_index_++];
	}
	// Handle out-of-cards situation (e.g., reshuffle or end of the game)
	// For simplicity, this example does not implement reshuffling.
	return Card(Card::Suit::DIAMONDS, Card::Rank::FOUR);
}

void Deck::AddCard(Card& card) {
	cards_.push_back(card);
}

std::vector<Card> Deck::DrawHand() {
	std::vector<Card> hand = std::vector<Card>();
	hand.push_back(DrawCard());
	hand.push_back(DrawCard());
	hand.push_back(DrawCard());
	return hand;
}
