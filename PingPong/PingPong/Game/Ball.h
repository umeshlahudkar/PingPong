#pragma once

#include "../Utils/Vector2D.h"
#include "../Shape/Rectangle.h"
#include "../Graphics/Color.h"


class Screen;
struct BoundaryEdge;
class Player;
enum MoveDirection;

class Ball {

public:
	Ball();
	Ball(const Vector2D& position, float radius, const Color& color);

	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);

	void Bounce(BoundaryEdge& edge);
	void SetPosition(const Vector2D& position);
	void SetPositionOnCollision(BoundaryEdge& collidedEdge, Vector2D& collidedPoint);
	void SetInitialVelocity(MoveDirection moveDirection);

	Player* GetBallHitBy() const { return mBallHitBy; }
	void SetBallHitBy(Player* player) { mBallHitBy = player; }

	inline void SetVelocity(Vector2D velocity) { mVelocity = velocity; }
	inline Vector2D GetVelocity() const { return mVelocity; }
	inline void SetSpeed(float speed = 0.2f) { mSpeed = speed; }
	inline Rectangle& GetRectangle() { return mRectangle; }
	inline Vector2D GetPosition() const { return mRectangle.GetCenterPoint(); }
	inline float GetRadius() const { return mRadius; }

private:
	float mRadius;
	float mSpeed = 0.2f;
	Vector2D mVelocity;
	Rectangle mRectangle;
	Color mColor;

	Player* mBallHitBy;
};