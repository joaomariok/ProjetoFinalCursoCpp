#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Player
{
public:
	enum Group { NO_GROUP, GROUP_1, GROUP_2 };

	Player();
	Player(std::string inputName, Group group = Group::NO_GROUP, int playerNumber = 0);

	virtual Card PlayCard(int cardIndex);

	std::string GetName() const { return name_; }
	int GetPlayerNumber() const { return playerNumber; }

	void IncreaseScore(int inputScore);
	int GetScore() const { return score_; }

	virtual void SetHand(std::vector<Card>& newHand);
	std::vector<Card> GetHand() const { return hand_; }

	void SetGroup(Group group);
	Group GetGroup() const { return group_; }

	void IncreaseRoundScore();
	int GetRoundScore() const { return round_score_; }
	void ResetRoundScore() { round_score_ = 0; }

	virtual ~Player();
	/*void PrintHand();
	void Truco();*/

private:
	int playerNumber;
	std::string name_;
	int score_;
	int round_score_;
	std::vector<Card> hand_;
	Group group_;
};