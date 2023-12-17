
#include "GameScene.h"
#include <iostream>
#include "../Input/InputController.h"
#include "../Graphics/Screen.h"
#include "../Game/PingPong.h"

GameScene::GameScene() : Scene(SceneType::Gameplay_Scene) {

}

void GameScene::Init() {
	mGameState = GameState::In_Ball_Serve;

	float width = PingPong::GetInstance().Width() - 1;
	float height = PingPong::GetInstance().Height() - 1;

	int playerWidth = 50;
	int playrHeight = 5;

	mBoundary = {Vector2D(0, 14), width, height-28};

	mBoundaryCollider.Init(Rectangle(Vector2D::Zero(), width, height));

	mPlayer1.Init("Player 1", Vector2D(width/2, 15), playerWidth, playrHeight, PlayerNumber::UP, Color::Orange());
	mPlayer2.Init("Player 2", Vector2D(width/2, height - (15 + playrHeight)), playerWidth, playrHeight, PlayerNumber::DOWN, Color::Cyan());

	mBall = { GetBallPositionAtPlayer1(), 5.0f, Color::Yellow() };
	mBall.SetPosition(GetBallPositionAtPlayer1());
	mBall.SetBallHitBy(&mPlayer1);

	mPlayer1.SetTurn(true);
	mLastPlayerTurnNumber = mPlayer1.GetPlayerNumber();

	mInputController->SetReference(this, mPlayer1, mPlayer2, mBall);
}

void GameScene::Update(uint32_t deltaTime) {

	if (mGameState == GameState::In_Ball_Serve)
	{
		ServeBall(deltaTime);
	}
	else if (mGameState == GameState::In_Game_Run)
	{
		UpdateGameRun(deltaTime);

		if (HasGoal() && mBall.GetBallHitBy() != nullptr) {
			HandleGoal();
		}
	}
}

void GameScene::Draw(Screen& screen) {

	screen.Draw(mBoundary, Color::White(), false);

	mBall.Draw(screen);

	mPlayer1.Draw(screen);
	mPlayer2.Draw(screen);
}


void GameScene::ServeBall(uint32_t deltaTime) {
	mPlayer1.Update(mBall, deltaTime);
	mPlayer2.Update(mBall, deltaTime);
}

void GameScene::UpdateGameRun(uint32_t deltaTime) {
	mBall.Update(deltaTime);

	BoundaryEdge edge;
	if (mBoundaryCollider.HasCollided(mBall, edge)) {
		mBall.Bounce(edge);
		return;
	}

	mPlayer1.Update(mBall, deltaTime);
	mPlayer2.Update(mBall, deltaTime);
}

void GameScene::HandleGoal() {
	
	if (mBall.GetPosition().GetY() <= GetPlayer(PlayerNumber::UP)->GetPosition().GetY())
	{
		mPlayer2.IncrementGoalCount();
	}
	else
	{
		mPlayer1.IncrementGoalCount();
	}

	mBall.SetVelocity(Vector2D::Zero());
	mPlayer1.SetTurn(false);
	mPlayer2.SetTurn(false);

	mGameState = GameState::In_Ball_Serve;

	PlayerNumber nextPlayerTurnNumber = mLastPlayerTurnNumber == PlayerNumber::UP ? PlayerNumber::DOWN : PlayerNumber::UP;

	if (nextPlayerTurnNumber == PlayerNumber::UP)
	{
		mBall.SetPosition(GetBallPositionAtPlayer1());
		mPlayer1.SetTurn(true);
	}
	else
	{
		mBall.SetPosition(GetBallPositionAtPlayer2());
		mPlayer2.SetTurn(true);
	}
	mLastPlayerTurnNumber = nextPlayerTurnNumber;
}

bool GameScene::HasGoal() {
	return (mBall.GetPosition().GetY() < mPlayer1.GetPosition().GetY()) ||
		   (mBall.GetPosition().GetY() > mPlayer2.GetPosition().GetY());
}

Vector2D GameScene::GetBallPositionAtPlayer1() {
	float xPos = mPlayer1.GetPosition().GetX();
	float yPos = mPlayer1.GetPosition().GetY() + ((mPlayer1.GetHeight() / 2) + 1 );

	return Vector2D(xPos, yPos);
}

Vector2D GameScene::GetBallPositionAtPlayer2() {
	float xPos = mPlayer2.GetPosition().GetX();
	float yPos = mPlayer2.GetPosition().GetY() - ((mPlayer2.GetHeight() / 2) + 2 * mBall.GetRadius() + 1);

	return Vector2D(xPos, yPos);
}

Player* GameScene::GetPlayer(PlayerNumber number) {
	if (mPlayer1.GetPlayerNumber() == number) {
		return &mPlayer1;
	}
	return &mPlayer2;
}

Player* GameScene::GetPlayerWhoseTurn() {
	if (mPlayer1.IsMyTurn()) {
		return &mPlayer1;
	}
	return &mPlayer2;
}

void GameScene::ResetGame() {

}