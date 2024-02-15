#include "Player.h"

Player::Player(std::string name, Group group, int player_number)
{
	name_ = name;
	player_number_ = player_number;
	score_ = 0;
	round_score_ = 0;
	group_ = group;
	hand_ = std::vector<Card>();
}

Player::Player(const Player& other) {
	name_ = other.GetName();
	player_number_ = other.GetPlayerNumber();
	score_ = other.GetScore();
	round_score_ = other.GetRoundScore();
	group_ = other.GetGroup();
	hand_ = other.GetHand();
}

Player::Player() : Player("") {}

void Player::IncreaseScore(int input_score) {
	score_ += input_score;
}

void Player::SetHand(std::vector<Card>& new_hand) {
	hand_ = new_hand;
}

Card Player::PlayCard(int card_index) {
	Card card = hand_.at(card_index);
	hand_.erase(hand_.begin() + card_index);
	return card;
}

void Player::Reset(const Player& player) {
	name_ = player.GetName();
	player_number_ = player.GetPlayerNumber();
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
