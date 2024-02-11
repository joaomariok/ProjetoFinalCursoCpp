#include "Bot.h"

Bot::Bot() : Bot("") { }

Bot::Bot(std::string inputName, Group group = Group::NO_GROUP) : Player(inputName, group) { }
