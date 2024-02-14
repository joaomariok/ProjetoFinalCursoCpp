#include "Bot.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Bot::Bot() : Bot("", Group::NO_GROUP, 0) { }

Bot::Bot(std::string inputName, Group group, int playerNumber) : Player(inputName, group, playerNumber) {
	// The initial decision making percentage is 5% regardless of the cards it has
	percentage_to_ask_truco_ = 5;
	percentage_to_accept_truco_ = 5;
}

Bot::Bot(const Player& other) : Player(other) {
	percentage_to_ask_truco_ = 5;
	percentage_to_accept_truco_ = 5;
}

void Bot::Reset(const Player& player) {
	Player::Reset(player);
	percentage_to_ask_truco_ = 5;
	percentage_to_accept_truco_ = 5;
}

void Bot::SetChallengingCard(Card card) {
	challenging_card_ = card;
}

void Bot::SetPercentageToAskAndAcceptTruco(int percentageToAsk, int percentageToAccept) {
	percentage_to_ask_truco_ = percentageToAsk;
	percentage_to_accept_truco_ = percentageToAccept;
}

int Bot::MakeTrucoDecision() const {
	srand(time(0));
	return rand() % 100;
}

bool Bot::AskTruco() {
	int randomNumber = MakeTrucoDecision();
	return randomNumber < percentage_to_ask_truco_;
}

bool Bot::RespondTruco() {
	int randomNumber = MakeTrucoDecision();
	return randomNumber < percentage_to_accept_truco_;
}

void Bot::CategorizeCards(std::vector<Card>& hand) {
	int percentageToAskTruco = 5, percentageToAcceptTruco = 5;

	for (Card& card : hand) {
		if (card.IsZap()) {
			percentageToAskTruco += 40;
			percentageToAcceptTruco += 80;
		}
		else if (card.IsManilha()) {
			percentageToAskTruco += 10;
			percentageToAcceptTruco += 20;
		}
		else if (card.GetRank() == Card::THREE) {
			percentageToAskTruco += 5;
			percentageToAcceptTruco += 10;
		}
	}

	SetPercentageToAskAndAcceptTruco(percentageToAskTruco, percentageToAcceptTruco);
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

void Bot::SetHand(std::vector<Card>& newHand) {
	//Bot cards are sorted from weakest to strongest.
	std::sort(newHand.begin(), newHand.end(), [](Card currentCard, Card nextCard) {
		return nextCard.IsBiggerThan(currentCard);
		});

	Player::SetHand(newHand);
	CategorizeCards(newHand);
}
