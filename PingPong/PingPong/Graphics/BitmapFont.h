#pragma once


#include "SpriteSheet.h"
#include "/PingPong/PingPong/Utils/Utils.h"
#include <stdint.h>

class Vector2D;
class Rectangle;

enum BitmapFontXAlignment
{
	BFXA_LEFT = 0,
	BFXA_CENTER,
	BFXA_RIGHT
};

enum BitmapFontYAlignment
{
	BFYA_TOP = 0,
	BFYA_CENTER,
	BFYA_BOTTOM
};

class BitmapFont
{
public:

	BitmapFont() {}
	bool Load(const std::string& name);
	Size GetSizeOf(const std::string& str) const;
	Vector2D GetDrawPosition(const std::string& str, const Rectangle& box, BitmapFontXAlignment xAlign = BFXA_LEFT, BitmapFontYAlignment yAlign = BFYA_TOP) const;

	inline const SpriteSheet& GetSpriteSheet() const { return mFontSheet; }
	inline const uint32_t GetFontSpacingBetweenLetters() const { return 2; }
	inline const uint32_t GetFontSpacingBetweenWords() const { return 5; }

private:
	SpriteSheet mFontSheet;
};
