

#include "GameController.h"

SDL_KeyCode GameController::EnterKey() {
	return SDLK_KP_ENTER;
}

SDL_KeyCode GameController::LeftArrow() {
	return SDLK_LEFT;
}

SDL_KeyCode GameController::RightArrow() {
	return SDLK_RIGHT;
}
SDL_KeyCode GameController::UpArrow() {
	return SDLK_UP;
}

SDL_KeyCode GameController::DownArrow() {
	return SDLK_DOWN;
}

SDL_KeyCode GameController::LeftKey() {
	return SDLK_a;
}

SDL_KeyCode GameController::RightKey() {
	return SDLK_d;
}

bool GameController::IsPressed(SDL_KeyCode key) {
	return key == SDL_PRESSED;
}
bool GameController::IsReleased(SDL_KeyCode key) {
	return key == SDL_RELEASED;
}

void GameController::SetButtonActionForKey(const ButtonAction& action) {
	buttonActions.push_back(action);
}

InputAction GameController::GetAction(SDL_KeyCode key) {
	for (int i = 0; i < buttonActions.size(); i++) {
		if (buttonActions[i].key == key) {
			return buttonActions[i].action;
		}
	}
	return [](SDL_KeyCode) {};
}