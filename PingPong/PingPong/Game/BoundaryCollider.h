#pragma once
#include "../Shape/Rectangle.h"
#include "BoundaryEdge.h"
#include "Ball.h"


class BoundaryCollider {

public:

	void Init(const Rectangle& boundaryRect);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge);

private:
	void SetUpEdges();
	bool CollidedWithEdge(const Ball& ball, BoundaryEdge& edge);

	Rectangle mRectangle;
	BoundaryEdge mBoundaryEdges[NUM_EDGES];
};