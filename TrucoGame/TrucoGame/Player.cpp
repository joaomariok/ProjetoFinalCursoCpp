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

std::string Player::GetName() {
	return name_;
}

int Player::GetScore() {
	return score_;
}

void Player::IncreaseScore(int inputScore) {
	score_ += inputScore;
}

std::vector<Card> Player::GetHand() {
	return hand_;
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
