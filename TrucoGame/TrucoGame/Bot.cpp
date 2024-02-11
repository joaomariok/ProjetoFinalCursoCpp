#include "Bot.h"

Bot::Bot() : Bot("", Group::NO_GROUP) { }

Bot::Bot(std::string inputName, Group group) : Player(inputName, group) { }
