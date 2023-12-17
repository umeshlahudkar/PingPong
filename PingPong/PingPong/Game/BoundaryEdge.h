#pragma once
#include "../Utils/Vector2D.h"
#include "../Shape/Line.h"



enum EdgeType
{
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

static const Vector2D UP_DIR = { 0, -1 };
static const Vector2D DOWN_DIR = { 0, 1 };
static const Vector2D LEFT_DIR = { -1, 0 };
static const Vector2D RIGHT_DIR = { 1, 0 };

struct  BoundaryEdge
{
	Line line;
	Vector2D normal;
};