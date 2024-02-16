#pragma once
#include <vector>
#include <string>

class SerializablePlayer
{
public:
	SerializablePlayer();
	~SerializablePlayer();
	SerializablePlayer(int player_number, std::string name, int score, int round_score, std::vector<int> card_1, std::vector<int> card_2, std::vector<int> card_3, int group);

	std::string GetName();
	int GetPlayerNumber() const { return s_player_number_; }
	int GetScore() const { return s_score_; }
	int GetRoundScore() const { return s_round_score_; }
	std::vector<int> GetCard_1() const { return std::vector<int> { s_card1_suit, s_card1_rank, s_card1_is_manilha }; }
	std::vector<int> GetCard_2() const { return std::vector<int> { s_card2_suit, s_card2_rank, s_card2_is_manilha }; }
	std::vector<int> GetCard_3() const { return std::vector<int> { s_card3_suit, s_card3_rank, s_card3_is_manilha }; }
	int GetGroup() const { return s_group_;  }

private:
	int s_player_number_ = 0;
	char s_name_[20] = "";
	int s_score_ = 0;
	int s_round_score_ = 0;

	//Card 1
	int s_card1_suit = 0;
	int s_card1_rank = 0;
	int s_card1_is_manilha = 0;
	//Card 2
	int s_card2_suit = 0;
	int s_card2_rank = 0;
	int s_card2_is_manilha = 0;
	//Card 3
	int s_card3_suit = 0;
	int s_card3_rank = 0;
	int s_card3_is_manilha = 0;

	int s_group_ = 0;
};

