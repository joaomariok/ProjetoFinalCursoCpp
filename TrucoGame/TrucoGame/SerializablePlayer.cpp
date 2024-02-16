#include "SerializablePlayer.h"

SerializablePlayer::SerializablePlayer() { }

SerializablePlayer::~SerializablePlayer() = default;

SerializablePlayer::SerializablePlayer(int player_number, std::string name, int score, int round_score, std::vector<int> card_1, std::vector<int> card_2, std::vector<int> card_3, int group)
{
	name.copy(s_name_, sizeof(s_name_));
	s_player_number_ = player_number;
	s_score_ = score;
	s_round_score_ = round_score;
	s_group_ = group;
	s_card1_suit = card_1[0];
	s_card1_rank = card_1[1];
	s_card1_is_manilha = card_1[2];

	s_card2_suit = card_2[0];
	s_card2_rank = card_2[1];
	s_card2_is_manilha = card_2[2];

	s_card3_suit = card_3[0];
	s_card3_rank = card_3[1];
	s_card3_is_manilha = card_3[2];
}
std::string SerializablePlayer::GetName()
{
	std::string str(s_name_, strlen(s_name_));
	return str;
}