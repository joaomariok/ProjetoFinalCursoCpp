#include "Player.h"

Player::Player(std::string inputName)
{
	name = inputName;
	score = 0;
}

std::string Player::GetName() {
	return name;
}

int Player::GetScore() {
	return score;
}

void Player::IncreaseScore(int inputScore) {
	score += inputScore;
}

std::vector<Card> Player::GetHand() {
	return hand;
}

void Player::SetHand(std::vector<Card>& newHand) {
	hand = newHand;
}
