#pragma once

#define WM_CUSTOM_MESSAGE (WM_APP + 1)

namespace Utils
{
	enum GameEvents { CARD1_PICKED, CARD2_PICKED, CARD3_PICKED, TRUCO, CONTINUE, QUIT };
}