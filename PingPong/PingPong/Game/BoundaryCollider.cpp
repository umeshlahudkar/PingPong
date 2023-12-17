
#include "BoundaryCollider.h"

void BoundaryCollider::Init(const Rectangle& boundaryRect) {
	mRectangle = boundaryRect;
	SetUpEdges();
}

bool BoundaryCollider::HasCollided(const Ball& ball, BoundaryEdge& edge) {
	for (int i = 0; i < NUM_EDGES; i++) {
		BoundaryEdge edg = mBoundaryEdges[i];

		if (CollidedWithEdge(ball, edg)) {
			edge = edg;
			return true;
		}
	}
	return false;
}

void BoundaryCollider::SetUpEdges() {
	mBoundaryEdges[TOP_EDGE].line = { mRectangle.GetTopLeftPoint(), Vector2D(mRectangle.GetBottomRightPoint().GetX(),  mRectangle.GetTopLeftPoint().GetY()) };
	mBoundaryEdges[TOP_EDGE].normal = DOWN_DIR;

	mBoundaryEdges[RIGHT_EDGE].line = { Vector2D(mRectangle.GetBottomRightPoint().GetX(),  mRectangle.GetTopLeftPoint().GetY()), mRectangle.GetBottomRightPoint() };
	mBoundaryEdges[RIGHT_EDGE].normal = LEFT_DIR;

	mBoundaryEdges[BOTTOM_EDGE].line = { mRectangle.GetBottomRightPoint(), Vector2D(mRectangle.GetTopLeftPoint().GetX(),  mRectangle.GetBottomRightPoint().GetY()) };
	mBoundaryEdges[BOTTOM_EDGE].normal = UP_DIR;

	mBoundaryEdges[LEFT_EDGE].line = { Vector2D(mRectangle.GetTopLeftPoint().GetX(),  mRectangle.GetBottomRightPoint().GetY()), mRectangle.GetTopLeftPoint() };
	mBoundaryEdges[LEFT_EDGE].normal = RIGHT_DIR;
}

bool BoundaryCollider::CollidedWithEdge(const Ball& ball, BoundaryEdge& edge) {
	return edge.line.MinDistanceFrom(ball.GetPosition()) <= ball.GetRadius();
}