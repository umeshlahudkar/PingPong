#pragma once

#include "Scene.h"
#include "../Game/Ball.h"
#include "../Game/BoundaryCollider.h"
#include "../Game/Player.h"
#include "../Game/GameState.h"

class InputController;

class GameScene : public Scene {

public :
	GameScene();
	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;

	inline void SetGameState(GameState gameState) {  mGameState = gameState; }
	inline GameState GetGameState() const { return mGameState; }
	inline void SetInputController(InputController* inputController) { mInputController = inputController; }

	Player* GetPlayer(PlayerNumber number);
	Player* GetPlayerWhoseTurn();

private :

	void ServeBall(uint32_t deltaTime);
	void UpdateGameRun(uint32_t deltaTime);
	void HandleGoal();
	void ResetGame();
	bool HasGoal();
	Vector2D GetBallPositionAtPlayer1() ;
	Vector2D GetBallPositionAtPlayer2() ;

	Rectangle mBoundary;
	Ball mBall;
	BoundaryCollider mBoundaryCollider;
	InputController* mInputController;
	Player mPlayer1;
	Player mPlayer2;

	GameState mGameState;
	PlayerNumber mLastPlayerTurnNumber;
};