#include "Player.h"

Player::Player(std::string inputName, Group group, int playerNum)
{
	name_ = inputName;
	playerNumber = playerNum;
	score_ = 0;
	round_score_ = 0;
	group_ = group;
	hand_ = std::vector<Card>();
}

Player::Player(const Player& other) {
	name_ = other.GetName();
	playerNumber = other.GetPlayerNumber();
	score_ = other.GetScore();
	round_score_ = other.GetRoundScore();
	group_ = other.GetGroup();
	hand_ = other.GetHand();
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

void Player::Reset(const Player& player) {
	name_ = player.GetName();
	playerNumber = player.GetPlayerNumber();
	score_ = player.GetScore();
	round_score_ = player.GetRoundScore();
	group_ = player.GetGroup();
	hand_.clear();
}

void Player::SetGroup(Group group) {
	group_ = group;
}

void Player::IncreaseRoundScore() {
	round_score_++;
}

Player::~Player() = default;
