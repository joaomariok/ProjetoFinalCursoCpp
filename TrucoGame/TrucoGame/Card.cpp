#include "Card.h"

Card::Card(std::string inputValue, std::string inputType)
{
	value = inputValue;
	type = inputType;
}

std::string Card::GetValue() {
	return value;
}

std::string Card::GetType() {
	return type;
}
