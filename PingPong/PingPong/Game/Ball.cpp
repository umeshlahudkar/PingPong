

#include "Ball.h"
#include "../Graphics/Color.h"
#include "BoundaryEdge.h"
#include "../Graphics/Screen.h"
#include "../Shape/Circle.h"
#include "Paddle.h"
#include "Player.h"


Ball::Ball() : Ball(Vector2D::Zero(), 0.0f, Color::White()) {

}

Ball::Ball(const Vector2D& position, float radius, const Color& color) {
	mRadius = radius;
	mColor = color;
	mBallHitBy = nullptr;
	mVelocity = Vector2D(0, 0);
	mRectangle = { position - Vector2D(radius , radius), 2 * radius, 2 * radius };
}


void Ball::Bounce(BoundaryEdge& edge) {
	Vector2D vec;
	SetPositionOnCollision(edge, vec);
	mVelocity = mVelocity.Reflect(edge.normal);
}


void Ball::Update(uint32_t deltaTime) {
	mRectangle.MoveBy(mVelocity * mSpeed * deltaTime);
}

void Ball::Draw(Screen& screen) {
	Circle circle = { mRectangle.GetCenterPoint(), mRadius };
	screen.Draw(circle, mColor, true);
}

void Ball::SetPosition(const Vector2D& position) {
	mRectangle.MoveTo(position);
}

void Ball::SetPositionOnCollision(BoundaryEdge& collidedEdge, Vector2D& collidedPoint) {
	if (collidedEdge.normal == UP_DIR) {
		mRectangle.MoveTo(Vector2D(mRectangle.GetTopLeftPoint().GetX(), collidedEdge.line.GetP0().GetY() - mRectangle.GetHeight()));
	}
	else if (collidedEdge.normal == DOWN_DIR) {
		mRectangle.MoveTo(Vector2D(mRectangle.GetTopLeftPoint().GetX(), collidedEdge.line.GetP0().GetY() + 1));
	}
	else if (collidedEdge.normal == LEFT_DIR) {
		mRectangle.MoveTo(Vector2D(collidedEdge.line.GetP0().GetX() - mRectangle.GetWidth(), mRectangle.GetTopLeftPoint().GetY()));
	}
	else if (collidedEdge.normal == RIGHT_DIR) {
		mRectangle.MoveTo(Vector2D(collidedEdge.line.GetP0().GetX() + 1, mRectangle.GetTopLeftPoint().GetY()));
	}

	collidedPoint = collidedEdge.line.ClosestPoint(mRectangle.GetCenterPoint());
}

void Ball::SetInitialVelocity(MoveDirection moveDirection) {

	if (moveDirection == MoveDirection::LEFT) {
		if (mBallHitBy->GetPlayerNumber() == PlayerNumber::DOWN) {
			mVelocity = Vector2D(-1, -1).Normalize();
		}
		else {
			mVelocity = Vector2D(-1, 1).Normalize();
		}
	}
	else if (moveDirection == MoveDirection::RIGHT) {
		if (mBallHitBy->GetPlayerNumber() == PlayerNumber::DOWN) {
			mVelocity = Vector2D(1, 1).Normalize();
		}
		else {
			mVelocity = Vector2D(1, -1).Normalize();
		}
	}
}
