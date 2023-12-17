#pragma once


#include "BMPImage.h"
#include<string>
#include <vector>

struct  Sprite
{
	uint32_t xPos;
	uint32_t yPos;
	uint32_t width;
	uint32_t height;
};

class SpriteSheet {
public:
	SpriteSheet();
	bool Load(const std::string& name);

	Sprite GetSprite(const std::string& name) const;

	std::vector<std::string> SpriteNames() const;

	inline const BMPImage& GetBMPImage() const { return mBMPImage; }
	inline uint32_t GetWidth() const { return mBMPImage.GetWidth(); }
	inline uint32_t GetHeight() const { return mBMPImage.GetHeight(); }

private:

	bool LoadSpriteSections(const std::string& name);

	struct BMPImageSection
	{
		std::string key = "";
		Sprite sprite;
	};

	BMPImage mBMPImage;
	std::vector<BMPImageSection> mSections;
};