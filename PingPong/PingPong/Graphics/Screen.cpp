
#include <SDL.h>
#include <algorithm>

#include "Color.h"
#include "Screen.h"
#include "../Utils/Utils.h"
#include "../Shape/Line.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Circle.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "BitmapFont.h"


Screen::~Screen() {
	if (mSdlWindow != nullptr) {
		SDL_FreeSurface(mBackWindowSurface);
		SDL_FreeSurface(mMainWindowSurface);
		SDL_DestroyWindow(mSdlWindow);
		mSdlWindow = nullptr;
	}
	SDL_Quit();
}

Screen::Screen() : mSdlWindow(nullptr), mMainWindowSurface(nullptr), mBackWindowSurface(nullptr), mWidth(0), mHeight(0), mScreenClearColor() {

}


bool Screen::Init(uint32_t screenWidth, uint32_t screenHeight) {

	mHeight = screenHeight;
	mWidth = screenWidth;

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		mSdlWindow = SDL_CreateWindow("Ping-Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * 3, mHeight * 3, 0);

		if (mSdlWindow != nullptr) {
			mMainWindowSurface = SDL_GetWindowSurface(mSdlWindow);
			SDL_PixelFormat* pixelFormat = mMainWindowSurface->format;

			Color::Init(pixelFormat);
			mScreenClearColor = Color::Black();

			mBackWindowSurface = SDL_CreateRGBSurfaceWithFormat(0, mWidth, mHeight, 0, pixelFormat->format);
		}
		return true;
	}
	return false;
}

void Screen::SwapScreen() {
	if (mSdlWindow) {
		ClearMainSurface();
		SDL_BlitScaled(mBackWindowSurface, nullptr, mMainWindowSurface, nullptr);
		//SDL_BlitSurface(mBackWindowSurface, nullptr, mMainWindowSurface, nullptr);
		SDL_UpdateWindowSurface(mSdlWindow);
		ClearBackSurface();
	}
}

void Screen::ClearMainSurface() {
	SDL_FillRect(mMainWindowSurface, nullptr, mScreenClearColor.GetPixelColor());
}

void Screen::ClearBackSurface() {
	SDL_FillRect(mBackWindowSurface, nullptr, mScreenClearColor.GetPixelColor());
}

void Screen::SetPixel(uint8_t x, uint8_t y, const Color& color) {
	if (mSdlWindow) {
		SDL_LockSurface(mBackWindowSurface);

		uint32_t* pixels = (uint32_t*)mBackWindowSurface->pixels;
		pixels[(y * mBackWindowSurface->w) + x] = color.GetPixelColor();

		SDL_UnlockSurface(mBackWindowSurface);
	}
}

// Bresenham's line algorithm
void Screen::Draw(int x1, int y1, int x2, int y2, const Color& color) {
	if (mSdlWindow) {

		int dx, dy;
		int x0 = x1;
		int y0 = y1;

		dx = abs(x2 - x1);
		dy = abs(y2 - y1);

		int ix = (x1 < x2) ? 1 : -1;
		int iy = (y1 < y2) ? 1 : -1;

		SetPixel(x0, y0, color);

		if (dx >= dy) {

			int d = 2 * dy - dx;

			while (x0 != x2) {
				if (d <= 0) {
					d = d + 2 * dy;
				}
				else {
					d = d + 2 * (dy - dx);
					y0 += iy;
				}

				x0 += ix;

				SetPixel(x0, y0, color);
			}
		}
		else {

			int d = 2 * dx - dy;

			while (y0 != y2) {
				if (d <= 0) {
					d = d + 2 * dx;
				}
				else {
					x0 += ix;
					d = d + 2 * (dx - dy);
				}

				y0 += iy;

				SetPixel(x0, y0, color);
			}
		}
	}
}

void Screen::Draw(const Line& line, const Color& color) {
	Draw(line.GetP0().GetX(), line.GetP0().GetY(), line.GetP1().GetX(), line.GetP1().GetY(), color);
}

void Screen::Draw(const Rectangle& rect, const Color& color, bool fillPolygon) {

	std::vector<Vector2D> points = rect.GetPoints();

	if (fillPolygon) {
		FillPolygon(points, color);
	}

	Line line1 = { points[0] , points[1] };
	Line line2 = { points[1] , points[2] };
	Line line3 = { points[2] , points[3] };
	Line line4 = { points[3] , points[0] };

	Draw(line1, color);
	Draw(line2, color);
	Draw(line3, color);
	Draw(line4, color);
}

void Screen::Draw(const Circle& circle, const Color& color, bool fillPolygon) {

	int iteration = 20;

	float anglePerIteration = (2 * pi) / iteration;
	float angle = 0;

	std::vector<Vector2D> pointsOnCircle;

	for (int i = 0; i < iteration; i++) {
		angle += anglePerIteration;

		Vector2D point = { Vector2D((circle.GetCenterPoint().GetX() + circle.GetRadius() * cosf(angle)),
							(circle.GetCenterPoint().GetY() + circle.GetRadius() * sinf(angle))) };
		pointsOnCircle.push_back(point);
	}

	if (fillPolygon) {
		FillPolygon(pointsOnCircle, color);
	}

	for (int i = 0; i < pointsOnCircle.size(); i++) {
		Line line = { pointsOnCircle[i], pointsOnCircle[(i + 1) % pointsOnCircle.size()] };
		Draw(line, color);
	}
}

// Function to fill a polygon using the scanline fill algorithm
void Screen::FillPolygon(const std::vector<Vector2D>& vertices, const Color& color) {
	// Find minimum and maximum y-coordinates to determine scanline range
	int minY = vertices[0].GetY(), maxY = vertices[0].GetY();
	int minX = vertices[0].GetX(), maxX = vertices[0].GetX();
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].GetY() < minY) {
			minY = vertices[i].GetY();
		}

		if (vertices[i].GetY() > maxY) {
			maxY = vertices[i].GetY();
		}

		if (vertices[i].GetX() < minX) {
			minX = vertices[i].GetX();
		}

		if (vertices[i].GetX() > maxX) {
			maxX = vertices[i].GetX();
		}
	}

	// Loop through scanlines from minY to maxY
	for (int y = minY; y <= maxY; ++y) {
		std::vector<int> intersections;

		// Find intersections of the scanline with polygon edges
		for (size_t i = 0; i < vertices.size(); ++i) {
			const Vector2D& p1 = vertices[i];
			const Vector2D& p2 = vertices[(i + 1) % vertices.size()];

			if ((p1.GetY() <= y && p2.GetY() > y) || (p2.GetY() <= y && p1.GetY() > y)) {
				// Calculate x-coordinate of intersection

				int x = p1.GetX() + (y - p1.GetY()) * (p2.GetX() - p1.GetX()) / (p2.GetY() - p1.GetY());
				intersections.push_back(x);
			}
		}

		// Sort intersection points by x-coordinate
		std::sort(intersections.begin(), intersections.end(), std::less<>());

		// Fill between pairs of intersections on the current scanline
		for (size_t i = 0; i < intersections.size(); i += 2) {
			for (int x = intersections[i]; x < intersections[i + 1]; ++x) {
				SetPixel(x, y, color);
			}
		}
	}
}

void Screen::Draw(BMPImage& image, const Vector2D& pos) {

	uint32_t height = image.GetHeight();
	uint32_t width = image.GetWidth();

	std::vector<Color> pixels = image.GetPixel();

	for (uint32_t h = 0; h < height; h++)
	{
		for (uint32_t w = 0; w < width; w++)
		{
			//Color color = pixels[((w + pos.GetX()) * width) + (h + pos.GetY())];
			Color color = pixels[((w ) * width) + (h)];
			SetPixel(h + pos.GetX(), w + pos.GetY(), color);
		}
	}
}

void Screen::Draw(const BMPImage& image, const Sprite& sprite, const Vector2D& pos, const Color& overlayColor) {

	float rValue = static_cast<float>(overlayColor.GetRed()) / 255.0f;
	float gValue = static_cast<float>(overlayColor.GetGreen()) / 255.0f;
	float bValue = static_cast<float>(overlayColor.GetBlue()) / 255.0f;
	float aValue = static_cast<float>(overlayColor.GetAlpha()) / 255.0f;

	uint32_t width = sprite.width;
	uint32_t height = sprite.height;

	// new
	/*const std::vector<Color> pixels = image.GetPixel();
	auto topLeft = pos;
	auto topRight = pos + Vector2D(width, 0);
	auto bottomLeft = pos + Vector2D(0, height);
	auto bottomRight = pos + Vector2D(width, height);

	std::vector<Vector2D> points = { topLeft, bottomLeft, bottomRight, topRight };

	Vector2D xAxis = topRight - topLeft;
	Vector2D yAxis = bottomLeft - topLeft;

	const float invXAxisLengthSq = 1.0f / xAxis.Mag2();
	const float invYAxisLengthSq = 1.0f / yAxis.Mag2();

	PolyFill(points, [&](uint32_t px, uint32_t py) {
		Vector2D p = { static_cast<float>(px), static_cast<float>(py) };
		Vector2D d = p - topLeft;

		float u = invXAxisLengthSq * d.Dot(xAxis);
		float v = invYAxisLengthSq * d.Dot(yAxis);

		u = Clamp(u, 0.0f, 1.0f);
		v = Clamp(v, 0.0f, 1.0f);

		float tx = roundf(u * static_cast<float>(sprite.width));
		float ty = roundf(v * static_cast<float>(sprite.height));

		Color imageColor = pixels[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];
		Color newColor = { static_cast<uint8_t>(imageColor.GetRed() * rValue), static_cast<uint8_t>(imageColor.GetGreen() * gValue) ,static_cast<uint8_t>(imageColor.GetBlue() * bValue) ,static_cast<uint8_t>(imageColor.GetAlpha() * aValue) };

		return newColor;
		});*/

	for (uint32_t h = 0; h < height; h++) {
		for (uint32_t w = 0; w < width; w++) {

			Color imageColor = image.GetPixel()[GetIndex(image.GetWidth(), h + sprite.yPos, w + sprite.xPos)];

			Color newColor = {static_cast<uint8_t>(imageColor.GetRed() * rValue), static_cast<uint8_t>(imageColor.GetGreen() * gValue) ,static_cast<uint8_t>(imageColor.GetBlue() * bValue) ,static_cast<uint8_t>(imageColor.GetAlpha() * aValue) };

			SetPixel(w + pos.GetX(), h + pos.GetY(), newColor);
		}
	}
}

void Screen::Draw(const SpriteSheet& ss, const std::string& spriteName, const Vector2D& pos, const Color& overlayColor) {
	Draw(ss.GetBMPImage(), ss.GetSprite(spriteName), pos, overlayColor);
}

void Screen::Draw(const BitmapFont& font, const std::string& textLine, const Vector2D& pos, const Color& overlayColor)
{
	uint32_t xPos = pos.GetX();

	const SpriteSheet& ss = font.GetSpriteSheet();

	for (char c : textLine)
	{
		if (c == ' ')
		{
			xPos += font.GetFontSpacingBetweenWords();
			continue;
		}

		Sprite sprite = ss.GetSprite(std::string("") + c);

		Draw(ss.GetBMPImage(), sprite, Vector2D(xPos, pos.GetY()), overlayColor);

		xPos += sprite.width;

		xPos += font.GetFontSpacingBetweenLetters();
	}
}