#pragma once
#include "../Shape/Rectangle.h"
#include "BoundaryEdge.h"

#include <iostream>


class BoxCollider {

public:
	void Init(const Rectangle& rect);

	void SetUpEdges();
	bool HasCollided(const Rectangle& rect, BoundaryEdge& edge);

	inline Rectangle& GetRectangle() { return mRectangle; }

	inline Vector2D GetCenterPoint() const { return mRectangle.GetCenterPoint(); }
		

private:
	Rectangle mRectangle;
	BoundaryEdge mBoundaryEdges[NUM_EDGES];
};