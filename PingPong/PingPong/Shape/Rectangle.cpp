#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(Vector2D::Zero(), Vector2D::Zero()) {

}

Rectangle::Rectangle(const Vector2D& point, float width, float height) {
	mPoints.push_back(point);
	mPoints.push_back(Vector2D(point.GetX() + width, point.GetY() + height));
}

Rectangle::Rectangle(const Vector2D& topLeftPoint, const Vector2D& bottomRightPoint) {
	mPoints.push_back(topLeftPoint);
	mPoints.push_back(bottomRightPoint);
}


float Rectangle::GetWidth() const {
	return abs(GetTopLeftPoint().GetX() - GetBottomRightPoint().GetX());
}

float Rectangle::GetHeight() const {
	return abs(GetTopLeftPoint().GetY() - GetBottomRightPoint().GetY());
}

Vector2D Rectangle::GetCenterPoint() const {
	return Vector2D((GetTopLeftPoint().GetX() + GetWidth() / 2.0f), (GetTopLeftPoint().GetY() + GetHeight() / 2.0f));
}

bool Rectangle::ContainsPoint(const Vector2D& point) const {
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
	bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();

	return withinX && withinY;
}

bool Rectangle::Intersect(const Rectangle& otherRectangle) const {
	if (otherRectangle.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() ||
		otherRectangle.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX()) {
		return false;
	}

	if (otherRectangle.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() ||
		otherRectangle.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY()) {
		return false;
	}

	return true;
}

std::vector<Vector2D> Rectangle::GetPoints() const {
	std::vector<Vector2D> points;
	points.push_back(mPoints[0]);
	points.push_back(Vector2D(mPoints[1].GetX(), mPoints[0].GetY()));
	points.push_back(mPoints[1]);
	points.push_back(Vector2D(mPoints[0].GetX(), mPoints[1].GetY()));

	return points;
}

void Rectangle::MoveBy(const Vector2D& offset) {
	mPoints[0] += offset;
	mPoints[1] += offset;
}

void Rectangle::MoveTo(const Vector2D& position) {
	float width = GetWidth();
	float height = GetHeight();

	mPoints[0].SetX(position.GetX());
	mPoints[0].SetY(position.GetY());
	mPoints[1].SetX(mPoints[0].GetX() + width);
	mPoints[1].SetY(mPoints[0].GetY() + height);
}