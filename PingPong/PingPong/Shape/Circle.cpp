

#include "Circle.h"

Circle::Circle() : Circle(Vector2D::Zero(), 0) {

}

Circle::Circle(const Vector2D& centerPoint, float radius) {
	mPoints.push_back(centerPoint);
	mRadius = radius;
}


bool Circle::ContainPoint(const Vector2D& point) const {
	return Vector2D::Distance(GetCenterPoint(), point) <= mRadius;
}

bool Circle::Intersect(const Circle& otherCircle) const {
	return Vector2D::Distance(GetCenterPoint(), otherCircle.GetCenterPoint()) <= (mRadius + otherCircle.mRadius);
}

void Circle::MoveBy(const Vector2D& offset) {
	mPoints[0] += offset;
}

void Circle::MoveTo(const Vector2D& position) {
	mPoints[0] = position;
}