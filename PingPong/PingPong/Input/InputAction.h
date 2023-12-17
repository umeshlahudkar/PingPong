#pragma once

#include <functional>
#include <SDL.h>

using InputAction = std::function<void(SDL_KeyCode key)>;

struct ButtonAction {
	SDL_KeyCode key;
	InputAction action;
};