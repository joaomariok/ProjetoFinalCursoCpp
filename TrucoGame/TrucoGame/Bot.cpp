#include "Bot.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Bot::Bot() : Bot("", Group::NO_GROUP, 0) { }

Bot::Bot(std::string name, Group group, int player_number) : Player(name, group, player_number) {
	// The initial decision making percentage is 5% regardless of the cards it has
	percentage_to_ask_truco_ = 5;
	percentage_to_accept_truco_ = 5;
}

Bot::Bot(const Player& other) : Player(other) {
	// TODO: Is it possible to use other.GetPercentageToAskTruco() and other.GetPercentageToAcceptTruco() here?
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

void Bot::SetPercentageToAskAndAcceptTruco(int percentage_to_ask_truco, int percentage_to_accept_truco) {
	percentage_to_ask_truco_ = percentage_to_ask_truco;
	percentage_to_accept_truco_ = percentage_to_accept_truco;
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
Card Bot::PlayCard(int card_index) {
	std::vector<Card> botCards = GetHand();
	for (int i = 0; i < botCards.size(); i++) {
		// Plays the first cars that is bigger than challengingCard
		if (botCards[i].IsBiggerThan(challenging_card_)) {
			card_index = i;
			break;
		}
	}
	return Player::PlayCard(card_index);
}

void Bot::SetHand(std::vector<Card>& new_hand) {
	//Bot cards are sorted from weakest to strongest.
	std::sort(new_hand.begin(), new_hand.end(), [](Card current_card, Card next_card) {
		return next_card.IsBiggerThan(current_card);
		});

	Player::SetHand(new_hand);
	CategorizeCards(new_hand);
}
