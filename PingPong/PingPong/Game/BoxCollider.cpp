

#include "BoxCollider.h"

void BoxCollider::Init(const Rectangle& rect) {
	mRectangle = rect;
	SetUpEdges();
}


bool BoxCollider::HasCollided(const Rectangle& rect, BoundaryEdge& edge) {
	if (mRectangle.Intersect(rect)) {
		float minY = mRectangle.GetTopLeftPoint().GetY() >= rect.GetTopLeftPoint().GetY() ? mRectangle.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float maxY = mRectangle.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? mRectangle.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = maxY - minY;

		float minX = mRectangle.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? mRectangle.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float maxX = mRectangle.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? mRectangle.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = maxX - minX;

		if (xSize > ySize) {
			if (rect.GetCenterPoint().GetY() > mRectangle.GetCenterPoint().GetY()) {
				edge = mBoundaryEdges[BOTTOM_EDGE];
			}
			else
			{
				edge = mBoundaryEdges[TOP_EDGE];
			}
		}
		else {
			if (rect.GetCenterPoint().GetX() > mRectangle.GetCenterPoint().GetX()) {
				edge = mBoundaryEdges[RIGHT_EDGE];
			}
			else
			{
				edge = mBoundaryEdges[LEFT_EDGE];
			}
		}

		return true;
	}
	return false;
}

void BoxCollider::SetUpEdges() {
	mBoundaryEdges[TOP_EDGE].line = { mRectangle.GetTopLeftPoint(), Vector2D(mRectangle.GetBottomRightPoint().GetX(),  mRectangle.GetTopLeftPoint().GetY()) };
	mBoundaryEdges[TOP_EDGE].normal = UP_DIR;

	mBoundaryEdges[RIGHT_EDGE].line = { Vector2D(mRectangle.GetBottomRightPoint().GetX(),  mRectangle.GetTopLeftPoint().GetY()), mRectangle.GetBottomRightPoint() };
	mBoundaryEdges[RIGHT_EDGE].normal = RIGHT_DIR;

	mBoundaryEdges[BOTTOM_EDGE].line = { mRectangle.GetBottomRightPoint(), Vector2D(mRectangle.GetTopLeftPoint().GetX(),  mRectangle.GetBottomRightPoint().GetY()) };
	mBoundaryEdges[BOTTOM_EDGE].normal = DOWN_DIR;

	mBoundaryEdges[LEFT_EDGE].line = { Vector2D(mRectangle.GetTopLeftPoint().GetX(),  mRectangle.GetBottomRightPoint().GetY()), mRectangle.GetTopLeftPoint() };
	mBoundaryEdges[LEFT_EDGE].normal = LEFT_DIR;
}