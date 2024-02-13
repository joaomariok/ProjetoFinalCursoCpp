#include "Bot.h"
#include <algorithm>

Bot::Bot() : Bot("", Group::NO_GROUP, 0) { }

Bot::Bot(std::string inputName, Group group, int playerNumber) : Player(inputName, group, playerNumber) { }

void Bot::SetChallengingCard(Card card) {
	challenging_card_ = card;
}

/*Polimorfismo*/
Card Bot::PlayCard(int cardIndex) {
	std::vector<Card> botCards = GetHand();
	for (int i = 0; i < botCards.size(); i++) {
		// Plays the first cars that is bigger than challengingCard
		if (botCards[i].IsBiggerThan(challenging_card_)) {
			cardIndex = i;
			break;
		}
	}
	return Player::PlayCard(cardIndex);
}

bool Bot::CardsComparer(Card currentCard, Card nextCard) {
	return nextCard.IsBiggerThan(currentCard);
}

void Bot::SetHand(std::vector<Card>& newHand) {
	//Bot cards are sorted from weakest to strongest.
	std::sort(newHand.begin(), newHand.end(), CardsComparer);
	Player::SetHand(newHand);
}
