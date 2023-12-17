#pragma once

#include <vector>
#include "../Utils/Vector2D.h"

class Shape {

public:
	virtual ~Shape() { }
	virtual Vector2D GetCenterPoint() const = 0;
	virtual std::vector<Vector2D> GetPoints() const { return mPoints; };

protected:
	std::vector<Vector2D> mPoints;
};
