#include "Bot.h"

Bot::Bot() : Bot("", Group::NO_GROUP) { }

Bot::Bot(std::string inputName, Group group) : Player(inputName, group) { }

bool cardsComparer(Card currentCard, Card nextCard) {
	return nextCard.IsBiggerThan(currentCard);
}

void Bot::SortCards() {
	std::vector<Card> sortedHand = GetHand();

	std::sort(sortedHand.begin(), sortedHand.end(), cardsComparer);

	SetHand(sortedHand);
}
