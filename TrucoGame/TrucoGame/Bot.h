#pragma once
#include "Player.h"
#include <algorithm>

class Bot : public Player
{
public:
	Bot();
	Bot(std::string inputName, Group group);

	void SortCards();
	int DefineWhichCardWillBePlayed(Card challengingCard);
};
