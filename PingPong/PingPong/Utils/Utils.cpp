

#include "Utils.h"
#include <cmath>
#include <algorithm>
#include <cctype>

bool IsEqual(float x, float y) {
	return (abs(x - y) < EPSILON);
}

bool IsGreaterThanOrEqual(float x, float y) {
	return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y) {
	return x < y || IsEqual(x, y);
}

float GetInRadian(float value) {
	return (value * pi) / 180;
}

float GetInDegree(float value) {
	return (value * 180) / pi;
}

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c) {
	return r * width + c;
}

bool StringCompare(const std::string a, const std::string b) {
	if (a.length() == b.length())
	{
		return std::equal(b.begin(), b.end(), a.begin(), [](unsigned char a, unsigned char b) {
			return std::tolower(a) == std::tolower(b);
			});
	}
	return false;
}

float Clamp(float value, float min, float max) {
	if (value > max) {
		return max;
	}
	else if (value < min) {
		return min;
	}
	return value;
}