

#include "Player.h"
#include "Ball.h"
#include "Paddle.h"
#include "../Graphics/Color.h"
#include "../Graphics/Screen.h"
#include "PingPong.h"
#include "../Shape/Rectangle.h"


void Player::Init(std::string name, const Vector2D& position, int width, int height, PlayerNumber number, const Color& color) {
	mPaddle = Paddle(position, width, height, this, color);
	mName = name;
    mGoalCount = 0;
	mNumber = number;
	mColor = color;
}

void Player::Update(Ball& ball, uint32_t deltaTime) {

	mPaddle.Update(deltaTime);

	BoundaryEdge edge;
	if (mPaddle.HasCollided(ball.GetRectangle(), edge)) {
		mPaddle.BounceBall(ball, edge);
		ball.SetBallHitBy(this);
	}
}

void Player::Draw(Screen& screen) {
	mPaddle.Draw(screen);

	if ( mNumber == PlayerNumber::UP) {
		screen.Draw(PingPong::GetInstance().GetFont(), GetGoalText(),
			PingPong::GetInstance().GetFont().GetDrawPosition(GetGoalText(), Rectangle(Vector2D(2, 0), 5, 10), BFXA_CENTER, BFYA_CENTER), mColor);
	}
	else if (mNumber == PlayerNumber::DOWN)
	{
		screen.Draw(PingPong::GetInstance().GetFont(), GetGoalText(),
			PingPong::GetInstance().GetFont().GetDrawPosition(GetGoalText(), Rectangle(Vector2D(2, screen.GetHeight()-10), 5, 10), BFXA_CENTER, BFYA_CENTER), mColor);
	}
	

}

void Player::SetMoveDirection(MoveDirection moveDirection) {
	mPaddle.SetMovementDirection(moveDirection);
}

float Player::GetHeight() {
	return mPaddle.GetHeight();
}

std::string Player::GetGoalText() {

	std::string text;
	text = "Goal " + std::to_string(GetGoalCount());

	return text;
}
