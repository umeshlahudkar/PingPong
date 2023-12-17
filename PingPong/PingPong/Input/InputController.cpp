

#include "InputController.h"
#include "../Game/Paddle.h"
#include "../Game/Player.h"
#include "../Game/GameState.h"
#include "../Game/Ball.h"
#include "../Scene/GameScene.h"
#include "GameController.h"
#include "../Game/PingPong.h"

InputController::InputController() : mQuitAction(nullptr), mGameController(nullptr) {

}

void InputController::Init(InputAction quitAction) {
	mQuitAction = quitAction;
}

void InputController::Update(uint32_t deltaTime) {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		if (PingPong::GetInstance().GetActiveSceneType() != SceneType::Gameplay_Scene) {
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				mQuitAction(SDLK_0);
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				InputAction action = mGameController->GetAction(static_cast<SDL_KeyCode>(sdlEvent.key.keysym.sym));
				action(static_cast<SDL_KeyCode>(sdlEvent.key.state));
				break;
			}
		}
		else
		{
			switch (sdlEvent.type)
			{
				case SDL_QUIT:
					mQuitAction(SDLK_0);
					break;

				case SDL_KEYDOWN:
					switch (sdlEvent.key.keysym.sym)
					{
						case SDLK_LEFT:
							mIsLeftKeyPressed = true;
							break;

						case SDLK_RIGHT:
							mIsRightKeyPressed = true;
							break;

						case SDLK_a:
							mIsAKeyPressed = true;
							break;

						case SDLK_d:
							mIsDKeyPressed = true;
							break;
					}
					break;

				case SDL_KEYUP:
					switch (sdlEvent.key.keysym.sym)
					{
						case SDLK_LEFT:
							mIsLeftKeyPressed = false;
							break;

						case SDLK_RIGHT:
							mIsRightKeyPressed = false;
							break;

						case SDLK_a:
							mIsAKeyPressed = false;
							break;

						case SDLK_d:
							mIsDKeyPressed = false;
							break;
					}
					break;
			}

			HandlePlayer1InputAction();
			HandlePlayer2InputAction();
		}
		
	}
}

void InputController::SetInputController(GameController* gameController) {
	mGameController = gameController;
}

void InputController::SetReference(GameScene* gameScene, Player& player1, Player& player2, Ball& ball) {
	mGameScene = gameScene;
	mPlayer1 = &player1;
	mPlayer2 = &player2;
	mBall = &ball;
}


void InputController::HandlePlayerInputAction(Player* player, bool isLeftKeyPressed, bool isRightKeyPressed) {
	if (isLeftKeyPressed && isRightKeyPressed) {
		player->SetMoveDirection(MoveDirection::NONE);
	}
	else if (isLeftKeyPressed) {
		if (mGameScene->GetGameState() == GameState::In_Ball_Serve &&
			mGameScene->GetPlayerWhoseTurn()->GetPlayerNumber() == player->GetPlayerNumber()) {
			mBall->SetInitialVelocity(MoveDirection::LEFT);
			mGameScene->SetGameState(GameState::In_Game_Run);
		}
		player->SetMoveDirection(MoveDirection::LEFT);
	}
	else if (isRightKeyPressed) {
		if (mGameScene->GetGameState() == GameState::In_Ball_Serve &&
			mGameScene->GetPlayerWhoseTurn()->GetPlayerNumber() == player->GetPlayerNumber()) {
			mBall->SetInitialVelocity(MoveDirection::RIGHT);
			mGameScene->SetGameState(GameState::In_Game_Run);
		}
		player->SetMoveDirection(MoveDirection::RIGHT);
	}
	else {
		player->SetMoveDirection(MoveDirection::NONE);
	}
}

void InputController::HandlePlayer1InputAction() {
	HandlePlayerInputAction(mPlayer1, mIsLeftKeyPressed, mIsRightKeyPressed);
}

void InputController::HandlePlayer2InputAction() {
	HandlePlayerInputAction(mPlayer2, mIsAKeyPressed, mIsDKeyPressed);
}
