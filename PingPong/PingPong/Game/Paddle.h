#pragma once

#include "BoxCollider.h"
#include "../Graphics/Color.h"

enum MoveDirection
{
	NONE,
	LEFT,
	RIGHT
};

class Screen;
class Ball;
class Player;

class Paddle : public BoxCollider {

public:
	Paddle();
	Paddle(const Vector2D& position, int width, int height, Player* player, const Color& color);

	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);

	void MovedBy(const Vector2D position);
	void BounceBall(Ball& ball, BoundaryEdge& edge) const;

	float GetWidth() ;
	float GetHeight() ;

	inline void SetMovementDirection(MoveDirection direction) { mMoveDirection = direction; }
	inline MoveDirection GetMovementDirection() const { return mMoveDirection; }

private:
	void BoundWithinScreenBoundary();
	void HandleMovement(uint32_t deltaTime);

	MoveDirection mMoveDirection;
	float mSpeed = 0.2f;
	float mCornerBounceAmount = 0.2f;
	Color mColor;
	Player* mPlayer;
};