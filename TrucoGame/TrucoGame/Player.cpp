#include "Player.h"

Player::Player(std::string inputName, Group group, int playerNum)
{
	name_ = inputName;
	playerNumber = playerNum;
	score_ = 0;
	round_score_ = 0;
	group_ = group;
}

Player::Player() : Player("") {}

void Player::IncreaseScore(int inputScore) {
	score_ += inputScore;
}

void Player::SetHand(std::vector<Card>& newHand) {
	hand_ = newHand;
}

Card Player::PlayCard(int cardIndex) {
	Card card = hand_.at(cardIndex);
	hand_.erase(hand_.begin() + cardIndex);
	return card;
}

void Player::SetGroup(Group group) {
	group_ = group;
}

void Player::IncreaseRoundScore() {
	round_score_++;
}

Player::~Player() = default;
