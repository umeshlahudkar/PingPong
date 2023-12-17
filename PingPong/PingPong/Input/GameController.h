#pragma once

#include "InputAction.h"
#include <vector>

class GameController {
public :

	static SDL_KeyCode EnterKey();
	static SDL_KeyCode LeftArrow();
	static SDL_KeyCode RightArrow();
	static SDL_KeyCode UpArrow();
	static SDL_KeyCode DownArrow();
	static SDL_KeyCode LeftKey();
	static SDL_KeyCode RightKey();

	static bool IsPressed(SDL_KeyCode key);
	static bool IsReleased(SDL_KeyCode key);

	void SetButtonActionForKey(const ButtonAction& action);
	InputAction GetAction(SDL_KeyCode key);

private :
	std::vector<ButtonAction> buttonActions;
};