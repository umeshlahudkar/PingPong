#pragma once


class Vector2D {

public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& otherVec);

	inline void SetX(float x) { mX = x; }
	inline void SetY(float y) { mY = y; }
	inline float GetX() const { return mX; }
	inline float GetY() const { return mY; }

	bool operator== (const Vector2D& otherVec) const;
	bool operator!= (const Vector2D& otherVec) const;

	Vector2D operator-() const;
	Vector2D operator*(float scale) const;
	Vector2D operator/(float scale) const;
	Vector2D& operator*=(float scale);
	Vector2D& operator/=(float scale);


	Vector2D operator+(const Vector2D& vec) const;
	Vector2D operator-(const Vector2D& vec) const;
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);

	float Magnitude2() const;
	float Magnitude() const;

	Vector2D& Normalize();

	Vector2D ProjectionOnto(const Vector2D& otherVect) const;
	Vector2D Reflect(const Vector2D& otherVect) const;
	void Rotate(float angle);

	static float Distance(const Vector2D& vect1, const Vector2D& vect2);
	static float Dot(const Vector2D& vect1, const Vector2D& vect2);
	static float Angle(const Vector2D& vect1, const Vector2D& vect2);

	static Vector2D Zero() { return Vector2D(); }
	static Vector2D Up() { return Vector2D(0, -1); }
	static Vector2D Down() { return Vector2D(0, 1); }
	static Vector2D Left() { return Vector2D(-1, 0); }
	static Vector2D Right() { return Vector2D(1, 0); }

	friend Vector2D operator*(float value, const Vector2D& otherVect);

private:
	float mX;
	float mY;
};