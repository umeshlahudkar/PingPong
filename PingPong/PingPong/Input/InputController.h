#pragma once

#include "InputAction.h"

class Player;
union SDL_Event;
class Ball;
class GameController;
class GameScene;

class InputController {

public:

	InputController();
	void Init(InputAction quitAction);
	void Update(uint32_t deltaTime);

	void SetInputController(GameController* gameController);

	void SetReference(GameScene* gameScene, Player& player1, Player& player2, Ball& ball);

private:
	void HandlePlayerInputAction(Player* player, bool isLeftKeyPressed, bool isRightKeyPressed);

	void HandlePlayer1InputAction();
	void HandlePlayer2InputAction();

	bool mIsLeftKeyPressed = false;
	bool mIsRightKeyPressed = false;

	bool mIsAKeyPressed = false;
	bool mIsDKeyPressed = false;

	InputAction mQuitAction;
	GameController* mGameController;
	GameScene* mGameScene;
	Player* mPlayer1;
	Player* mPlayer2;
	Ball* mBall;
};