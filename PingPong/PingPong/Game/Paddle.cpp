
#include "Paddle.h"
#include "PingPong.h"
#include "../Graphics/Color.h"
#include "Ball.h"
#include "Player.h"


Paddle::Paddle() : Paddle(Vector2D::Zero(), 0, 0, nullptr ,Color::White()) {

}

Paddle::Paddle(const Vector2D& position, int width, int height, Player* player, const Color& color) {
	Init(Rectangle(position, width, height));
	mColor = color;
	mPlayer = player;
	mMoveDirection = MoveDirection::NONE;
}

void Paddle::MovedBy(const Vector2D position) {
	GetRectangle().MoveBy(position);
}

void Paddle::Update(uint32_t deltaTime) {

	if (mMoveDirection != MoveDirection::NONE) {
		HandleMovement(deltaTime);
		BoundWithinScreenBoundary();
		SetUpEdges();
	}
}

void Paddle::HandleMovement(uint32_t deltaTime) {

	if (mMoveDirection == MoveDirection::LEFT) {
		MovedBy(Vector2D::Left() * mSpeed * deltaTime);
	}
	else if (mMoveDirection == MoveDirection::RIGHT) {
		MovedBy(Vector2D::Right() * mSpeed * deltaTime);
	}
}


void Paddle::BoundWithinScreenBoundary() {

	if (GetRectangle().GetTopLeftPoint().GetX() < 0)
	{
		GetRectangle().MoveTo(Vector2D(0, GetRectangle().GetTopLeftPoint().GetY()));
	}
	else if (GetRectangle().GetBottomRightPoint().GetX() > PingPong::GetInstance().Width() - 1)
	{
		GetRectangle().MoveTo(Vector2D((PingPong::GetInstance().Width() - 1) - GetRectangle().GetWidth(), GetRectangle().GetTopLeftPoint().GetY()));
	}
}


void Paddle::BounceBall(Ball& ball, BoundaryEdge& edge) const {

	Vector2D collidedPoint;
	ball.SetPositionOnCollision(edge, collidedPoint);

	if ((edge.normal == UP_DIR && mPlayer->GetPlayerNumber() == PlayerNumber::DOWN) ||
		(edge.normal == DOWN_DIR && mPlayer->GetPlayerNumber() == PlayerNumber::UP))
	{
		float lineLength = edge.line.Length();
		float distanceFromP0 = Vector2D::Distance(edge.line.GetP0(), collidedPoint);
		float distanceFromP1 = Vector2D::Distance(edge.line.GetP1(), collidedPoint);

		if (((distanceFromP0 / lineLength) <= mCornerBounceAmount) || ((distanceFromP1 / lineLength) <= mCornerBounceAmount)) {
			ball.SetVelocity(-ball.GetVelocity());
			return;
		}
	}
	ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
}

void Paddle::Draw(Screen& screen) {
	screen.Draw(GetRectangle(), mColor, true);
}

float Paddle::GetWidth()  {
	float width = GetRectangle().GetWidth();
	return width;
}

float Paddle::GetHeight()  {
	float height = GetRectangle().GetHeight();
	return height;
}

