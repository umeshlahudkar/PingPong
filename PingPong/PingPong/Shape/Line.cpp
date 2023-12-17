
#include "Line.h"
#include "../Utils/Utils.h"
#include <cstdlib>


Line::Line() : Line(Vector2D::Zero(), Vector2D::Zero()) {

}

Line::Line(const Vector2D& p0, const Vector2D& p1) : mP0(p0), mP1(p1) {

}

Vector2D Line::MidPoint() const {
	return (mP0 + mP1) / 2;
}

float Line::Length() const {
	return Vector2D::Distance(mP0, mP1);
}

float Line::Slope() const {
	float dx = mP1.GetX() - mP0.GetX();

	if (abs(dx) > EPSILON) {
		float dy = mP1.GetY() - mP0.GetY();

		return dy / dx;
	}
	return 0;
}

float Line::MinDistanceFrom(const Vector2D& point) {
	Vector2D closePoint = ClosestPoint(point);
	return Vector2D::Distance(point, closePoint);
}

Vector2D Line::ClosestPoint(const Vector2D& point) {
	Vector2D p0toPoint = point - mP0;
	Vector2D p0ToP1 = mP1 - mP0;

	return mP0 + p0toPoint.ProjectionOnto(p0ToP1);
}