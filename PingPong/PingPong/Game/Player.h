#pragma once
#include <string>
#include "Paddle.h"
#include "../Utils/Vector2D.h"

#include <iostream>

class Ball;
//class Vector2D;
enum PaddlePosition;
class Screen;
class Color;

enum PlayerNumber {
	UP = 1,
	DOWN
};

class Player {

public:
	void Init(std::string name, const Vector2D& position, int width, int height, PlayerNumber number, const Color& color);

	void Update(Ball& ball, uint32_t deltaTime);
	void Draw(Screen& screen);

	void SetMoveDirection(MoveDirection moveDirection);
	float GetHeight();

	inline PlayerNumber GetPlayerNumber() const { return mNumber; }
	inline Vector2D GetPosition() const { return mPaddle.GetCenterPoint(); }
	inline const std::string& GetPlayerName() const { return mName; }
	inline int GetGoalCount() const { return mGoalCount; }
	inline void IncrementGoalCount() { mGoalCount++; }
	inline MoveDirection GetMoveDirection() const { return mPaddle.GetMovementDirection(); }
	inline void SetTurn(bool myTurn) { mIsMyTurn = myTurn; }
	inline bool IsMyTurn() const { return mIsMyTurn; }

private:

	std::string GetGoalText();

	std::string mName;
	int mGoalCount = 0;
	Paddle mPaddle;
	PlayerNumber mNumber;
	bool mIsMyTurn = false;
	Color mColor;
};