#include "Bot.h"

Bot::Bot() : Bot("", Group::NO_GROUP) { }

Bot::Bot(std::string inputName, Group group) : Player(inputName, group) { }

bool cardsComparer(Card currentCard, Card nextCard) {
	return nextCard.IsBiggerThan(currentCard);
}

/// <summary>
/// Bot cards are sorted from weakest to strongest.
/// </summary>
void Bot::SortCards() {
	std::vector<Card> sortedHand = GetHand();

	std::sort(sortedHand.begin(), sortedHand.end(), cardsComparer);

	SetHand(sortedHand);
}

int Bot::DefineWhichCardWillBePlayed(Card challengingCard) {
	SortCards();
	std::vector<Card> botCards = GetHand();

	for (int i = 0; i < botCards.size(); i++) {
		// Plays the first cars that is bigger than challengingCard
		if (botCards[i].IsBiggerThan(challengingCard)) {
			return i;
		}
		// If no card is bigger than challengingCard, just plays the weakest one
		else if (i == botCards.size() - 1) {
			return 0;
		}
	}
}
