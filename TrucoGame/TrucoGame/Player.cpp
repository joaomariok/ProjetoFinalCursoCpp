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
}

void Player::SetGroup(Group group) {
	group_ = group;
}

void Player::IncreaseRoundScore() {
	round_score_++;
}

void Player::DeserializePlayer(SerializablePlayer s_player)
{
	name_ = s_player.GetName();
	player_number_ = s_player.GetPlayerNumber();
	score_ = s_player.GetScore();
	round_score_ = s_player.GetRoundScore();
	group_ = static_cast<Group>(s_player.GetGroup());
	hand_.clear();

	std::vector<int> s_card = s_player.GetCard_1();
	Card card = Card(static_cast<Card::Suit>(s_card[0]), static_cast<Card::Rank>(s_card[1]));
	if (s_card[2] == 1) card.SetIsManilha();
	hand_.push_back(card);

	s_card = s_player.GetCard_2();
	card = Card(static_cast<Card::Suit>(s_card[0]), static_cast<Card::Rank>(s_card[1]));
	if (s_card[2] == 1) card.SetIsManilha();
	hand_.push_back(card);

	s_card = s_player.GetCard_3();
	card = Card(static_cast<Card::Suit>(s_card[0]), static_cast<Card::Rank>(s_card[1]));
	if (s_card[2] == 1) card.SetIsManilha();
	hand_.push_back(card);
}

SerializablePlayer Player::SerializePlayer()
{
	std::vector<int> s_card_1;
	if (hand_.size() > 0) {
		s_card_1.push_back(static_cast<int>(hand_[0].GetSuit()));
		s_card_1.push_back(static_cast<int>(hand_[0].GetRank()));
		s_card_1.push_back(static_cast<int>(hand_[0].IsManilha()));
	}

	std::vector<int> s_card_2;
	if (hand_.size() > 1) {
		s_card_2.push_back(static_cast<int>(hand_[1].GetSuit()));
		s_card_2.push_back(static_cast<int>(hand_[1].GetRank()));
		s_card_2.push_back(static_cast<int>(hand_[1].IsManilha()));
	}

	std::vector<int> s_card_3;
	if (hand_.size() > 2) {
		s_card_3.push_back(static_cast<int>(hand_[2].GetSuit()));
		s_card_3.push_back(static_cast<int>(hand_[2].GetRank()));
		s_card_3.push_back(static_cast<int>(hand_[2].IsManilha()));
	}

	SerializablePlayer s_player = SerializablePlayer(player_number_, name_, score_, round_score_, s_card_1, s_card_2, s_card_3, static_cast<int>(group_));
	return s_player;
}

Player::~Player() = default;