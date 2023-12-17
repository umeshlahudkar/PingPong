
#pragma once

#include <string>

static const float EPSILON = 0.0001f;
static const float pi = 3.14159f;

bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);
float GetInRadian(float value);
float GetInDegree(float value);

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c);
bool StringCompare(const std::string a, const std::string b);

float Clamp(float value, float min, float max);

struct Size
{
	unsigned int width = 0, height = 0;
};