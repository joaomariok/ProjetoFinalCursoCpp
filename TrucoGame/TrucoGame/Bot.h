#pragma once
#include "Player.h"

class Bot : public Player
{
public:
	Bot();
	Bot(std::string inputName, Group group);
};
