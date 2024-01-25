#include "Deck.h"

Deck::Deck()
{
	currentCardIndex = 0;
	InitializeDeck();
}

void Deck::InitializeDeck() {
	/*for (int type = Card::SPADES; type <= Card::CLUBS; ++type) {
		for (int value = Card::TWO; value <= Card::ACE; ++value) {
			cards.emplace_back(static_cast<Card::Type>(type), static_cast<Card::Value>(value));
		}
	}*/
}

void Deck::Shuffle() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	//std::random_shuffle(cards.begin(), cards.end());
	currentCardIndex = 0;
}

Card Deck::DrawCard() {
	if (currentCardIndex < cards.size()) {
		return cards[currentCardIndex++];
	}
	// Handle out-of-cards situation (e.g., reshuffle or end of the game)
	// For simplicity, this example does not implement reshuffling.
	return Card("SPADES", "TWO");
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
