#pragma once


#include <string>
#include <functional>

#include "../Shape/Rectangle.h"
#include "../Graphics/Color.h"
#include "../Graphics/BitmapFont.h"

class Screen;

class Button {

public:
	using ButtonAction = std::function<void(void)>;

	Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highletedColor = Color::White());
	void Init(const Vector2D& topLeft, unsigned int width, unsigned int height);
	void Draw(Screen& screen);
	void ExecuteAction();

	inline void SetButtonText(const std::string& text) { mTitle = text; }
	inline const std::string& GetButtonText() const { return mTitle; }
	inline void SetHighlighted(bool highleted) { mHighleted = highleted; }
	inline bool IsHighleted() { return mHighleted; }
	inline void SetButtonAction(Button::ButtonAction action) { mButtonAction = action; }

private:

	const BitmapFont& mBitmapFont;
	std::string mTitle;
	Rectangle mBBox;
	ButtonAction mButtonAction;

	bool mHighleted;
	Color mHighletedColor;
	Color mTextColor;
};