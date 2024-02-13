#include "Bot.h"

Bot::Bot() : Bot("", Group::NO_GROUP, 0) { }

Bot::Bot(std::string inputName, Group group, int playerNumber) : Player(inputName, group, playerNumber) { }

bool cardsComparer(Card currentCard, Card nextCard) {
	return nextCard.IsBiggerThan(currentCard);
}

void Bot::SortCards() {
	std::vector<Card> sortedHand = GetHand();

	std::sort(sortedHand.begin(), sortedHand.end(), cardsComparer);

	SetHand(sortedHand);
}

void Bot::SetChallengingCard(Card card) { challengingCard = card; }

/*Polimorfismo*/
Card Bot::PlayCard(int cardIndex) {
	std::vector<Card> botCards = GetHand();
	for (int i = 0; i < botCards.size(); i++) {
		// Plays the first cars that is bigger than challengingCard
		if (botCards[i].IsBiggerThan(challengingCard)) {
			cardIndex = i;
			break;
		}
	}
	return Player::PlayCard(cardIndex);
}

void Bot::SetHand(std::vector<Card>& newHand) {
	//SetHand sorted for Bot players
	std::sort(newHand.begin(), newHand.end(), cardsComparer);
	Player::SetHand(newHand);
}
