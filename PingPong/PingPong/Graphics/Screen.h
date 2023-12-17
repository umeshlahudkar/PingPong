#pragma once

#include <cstdint>
#include <vector>
#include "Color.h"
#include <string>

class Line;
class Rectangle;
class Circle;
class Vector2D;
struct SDL_Window;
struct SDL_Surface;
class BMPImage;
struct Sprite;
class SpriteSheet;
class BitmapFont;

class Screen {

public:

	~Screen();
	Screen();

	bool Init(uint32_t screenWidth, uint32_t screenHeight);

	void SwapScreen();
	inline float GetWidth() const { return mWidth; }
	inline float GetHeight() const { return mHeight; }

	void Draw(int x1, int y1, int x2, int y2, const Color& color);
	void Draw(const Line& line, const Color& color);
	void Draw(const Rectangle& rect, const Color& color, bool fillPolygon);
	void Draw(const Circle& circle, const Color& color, bool fillPolygon);
	void Draw(BMPImage& image, const Vector2D& pos);

	void Draw(const BMPImage& image, const Sprite& sprite, const Vector2D& pos, const Color& overlayColor = Color::White());
	void Draw(const SpriteSheet& ss, const std::string& spriteName, const Vector2D& pos, const Color& overlayColor = Color::White());
	void Draw(const BitmapFont& font, const std::string& textLine, const Vector2D& pos, const Color& overlayColor = Color::White());


private:

	void SetPixel(uint8_t x, uint8_t y, const Color& color);
	void FillPolygon(const std::vector<Vector2D>& vertices, const Color& color);

	void ClearMainSurface();
	void ClearBackSurface();

	uint32_t mWidth;
	uint32_t mHeight;

	SDL_Window* mSdlWindow;
	SDL_Surface* mMainWindowSurface;
	SDL_Surface* mBackWindowSurface;

	Color mScreenClearColor;
};