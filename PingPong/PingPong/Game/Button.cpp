

#include "Button.h"
#include "../Graphics/Screen.h"


Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highletedColor) :
    mBitmapFont(bitmapFont), mTextColor(textColor), mHighletedColor(highletedColor), mTitle(""), mHighleted(false), mButtonAction(nullptr)
{

}

void Button::Init(const Vector2D& topLeft, unsigned int width, unsigned int height) {
    mBBox = { topLeft, static_cast<float>(width), static_cast<float>(height) };
}

void Button::Draw(Screen& screen) {
    screen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

    if (mHighleted) {
        screen.Draw(mBBox, mHighletedColor, false);
    }
}

void Button::ExecuteAction() {
    mButtonAction();
}