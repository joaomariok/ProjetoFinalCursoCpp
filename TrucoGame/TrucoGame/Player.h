#pragma once
#include "Card.h"
#include "SerializablePlayer.h"
#include <vector>
#include <string>

class Player
{
public:
	enum Group { NO_GROUP, GROUP_1, GROUP_2 };

	Player();
	Player(std::string name, Group group = Group::NO_GROUP, int player_number = 0);
	Player(const Player& other);
	Player(Player&& other) noexcept = default;
	Player& operator=(const Player& other) = default;
	Player& operator=(Player&& other) noexcept = default;

	virtual Card PlayCard(int card_index);
	virtual void Reset(const Player& player);

	std::string GetName() const { return name_; }
	int GetPlayerNumber() const { return player_number_; }

	void IncreaseScore(int input_score);
	int GetScore() const { return score_; }

	virtual void SetHand(std::vector<Card>& new_hand);
	std::vector<Card> GetHand() const { return hand_; }

	void SetGroup(Group group);
	Group GetGroup() const { return group_; }

	void IncreaseRoundScore();
	int GetRoundScore() const { return round_score_; }
	void ResetRoundScore() { round_score_ = 0; }

	void DeserializePlayer(SerializablePlayer s_player);
	SerializablePlayer SerializePlayer();

	virtual ~Player();

private:
	int player_number_;
	std::string name_;
	int score_;
	int round_score_;
	std::vector<Card> hand_;
	Group group_;
};