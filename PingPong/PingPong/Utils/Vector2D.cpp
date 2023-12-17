

#include "Vector2D.h"
#include "Utils.h"
#include <cmath>

Vector2D::Vector2D() : Vector2D(0, 0) {

}

Vector2D::Vector2D(float x, float y) : mX(x), mY(y) {

}

Vector2D::Vector2D(const Vector2D& otherVec) {
	mX = otherVec.GetX();
	mY = otherVec.GetY();
}

bool Vector2D::operator== (const Vector2D& otherVec) const {
	return IsEqual(mX, otherVec.GetX()) && IsEqual(mY, otherVec.GetY());
}

bool Vector2D::operator!= (const Vector2D& otherVec) const {
	return !(*this == otherVec);
}

Vector2D operator*(float value, const Vector2D& otherVect) {
	return otherVect * value;
}

Vector2D Vector2D::operator-() const {
	return Vector2D(-mX, -mY);
}

Vector2D Vector2D::operator*(float scale) const {
	return Vector2D(scale * mX, scale * mY);
}

Vector2D Vector2D::operator/(float scale) const {
	if (abs(scale) > EPSILON) {
		return Vector2D(mX / scale, mY / scale);
	}
}

Vector2D& Vector2D::operator*=(float scale) {
	*this = *this * scale;
	return *this;
}

Vector2D& Vector2D::operator/=(float scale) {
	if (abs(scale) > EPSILON) {
		*this = *this / scale;
		return *this;
	}
}

Vector2D Vector2D::operator+(const Vector2D& vec) const {
	return Vector2D(mX + vec.GetX(), mY + vec.GetY());
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
	return Vector2D(mX - vec.GetX(), mY - vec.GetY());
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	*this = *this + vec;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	*this = *this - vec;
	return *this;
}

float Vector2D::Magnitude2() const {
	return (mX * mX + mY * mY);
}

float Vector2D::Magnitude() const {
	return sqrtf(Magnitude2());
}

Vector2D& Vector2D::Normalize() {
	float mag = Magnitude();

	if (mag > EPSILON) {
		*this = *this / mag;
	}

	return *this;
}

Vector2D Vector2D::ProjectionOnto(const Vector2D& otherVect) const {
	return Dot(*this, otherVect) * otherVect / (otherVect.Magnitude() * otherVect.Magnitude());
}

Vector2D Vector2D::Reflect(const Vector2D& otherVect) const {
	return *this - 2 * ProjectionOnto(otherVect);
}

float Vector2D::Dot(const Vector2D& vect1, const Vector2D& vect2) {
	return vect1.GetX() * vect2.GetX() + vect1.GetY() * vect2.GetY();
}

float Vector2D::Distance(const Vector2D& vect1, const Vector2D& vect2) {
	return (vect2 - vect1).Magnitude();
}

float Vector2D::Angle(const Vector2D& vect1, const Vector2D& vect2) {
	float angle = acos((Dot(vect1, vect2)) / (vect1.Magnitude() * vect2.Magnitude()));
	return GetInDegree(angle);
}

void Vector2D::Rotate(float angle) {

	angle = GetInRadian(angle);

	float x = cosf(angle) * mX - sinf(angle) * mY;
	float y = sinf(angle) * mX + cosf(angle) * mY;

	mX = x;
	mY = y;
}