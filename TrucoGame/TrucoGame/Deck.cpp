#include "Deck.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <ctime>
#include <thread>
#include <future>

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

	constexpr int total_threads = 4;
	const size_t batch_size = cards_.size() / total_threads;
	std::vector<Cards> results;
	Cards shuffled_deck = Cards();

	for (size_t i = 0; i < total_threads; i++) {
		const size_t begin = i * batch_size;
		const size_t end = begin + batch_size - 1;
		Cards batch_vector(cards_.begin() + begin, cards_.begin() + end);
		results.emplace_back(
			std::async(std::launch::async, [&](Cards cards) {
				std::shuffle(cards.begin(), cards.end(), g);
				return cards;
				}, batch_vector).get());
	}

	for (auto& result : results) {
		shuffled_deck.reserve(result.size()); // preallocate memory
		shuffled_deck.insert(shuffled_deck.end(), result.begin(), result.end());
	}

	cards_ = shuffled_deck;
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

void Deck::SetManilhas(Card& vira) {
	Card::Rank manilhas_rank;
	Card::Rank vira_rank = vira.GetRank();

	manilhas_rank = vira_rank == Card::THREE ?
		Card::FOUR : static_cast<Card::Rank>(vira_rank + 1);

	int i = 0, manilhas_count = 0;

	while (manilhas_count < 4) {
		if (cards_[i].GetRank() == manilhas_rank) {
			cards_[i].SetIsManilha();
			manilhas_count++;
		}
		i++;
	}
}

void Deck::AddCard(Card& card) {
	cards_.push_back(card);
}

Cards Deck::DrawHand() {
	constexpr int HAND_SIZE = 3;
	Cards hand = Cards();
	for (size_t i = 0; i < HAND_SIZE; i++) {
		hand.push_back(DrawCard());
	}
	return hand;
}
