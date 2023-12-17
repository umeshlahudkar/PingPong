#pragma once

#include <string>
#include <vector>
#include "Color.h"

class BMPImage {

public:
	BMPImage();
	bool Load(const std::string& path);

	inline const std::vector<Color>& GetPixel() const { return mPixels; }
	inline uint32_t GetWidth() const { return mWidth; }
	inline uint32_t GetHeight() const { return mHeight; }


private:

	std::vector<Color> mPixels;
	uint32_t mWidth;
	uint32_t mHeight;
};