#pragma once



#include <stdint.h>
#include <SDL.h>

class Color {
public:
	static const SDL_PixelFormat* mPixelFormat;
	static void Init(const SDL_PixelFormat* pixelFormat);

	static Color Black() { return Color(0, 0, 0, 255); }
	static Color White() { return Color(255, 255, 255, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Magneta() { return Color(255, 0, 255, 255); }
	static Color Cyan() { return Color(37, 240, 217, 255); }
	static Color Pink() { return Color(252, 197, 224, 255); }
	static Color Orange() { return Color(245, 190, 100, 255); }

	Color() : Color(0, 0, 0, 0) {}
	Color(uint32_t color) : mColor(color) {}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	inline uint32_t GetPixelColor() const { return mColor; }

	void SetRed(uint8_t red);
	void SetGreen(uint8_t green);
	void SetBlue(uint8_t blue);
	void SetAlpha(uint8_t alpha);

	uint8_t GetRed() const;
	uint8_t GetGreen() const;
	uint8_t GetBlue() const;
	uint8_t GetAlpha() const;

private:
	uint32_t mColor;
};