#include "Player.h"

Player::Player(std::string inputName)
{
	name_ = inputName;
	score_ = 0;
	round_score_ = 0;
}

Player::Player() {
	name_ = "";
	score_ = 0;
}

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

Card Player::PlayCard()
{
	Card card = hand_.back();
	hand_.pop_back();
	return card;
}
