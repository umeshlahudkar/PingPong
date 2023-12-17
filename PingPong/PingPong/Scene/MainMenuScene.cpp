
#include "MainMenuScene.h"
#include "../Input/InputController.h"
#include "../Graphics/BMPImage.h"
#include "../Graphics/Screen.h"
#include "../Utils/Vector2D.h"
#include "../Game/PingPong.h"

void MainMenuScene::Init()
{
	const std::vector<std::string>& optionNames = { "PLAY", "QUIT"};
	const Color& textColor = Color::Cyan();
	const BitmapFont& font = PingPong::GetInstance().GetFont();

	mHighlightedOption = 0;

	for (size_t i = 0; i < optionNames.size(); ++i)
	{
		Button b = { font, textColor };
		mButtons.push_back(b);
		mButtons.back().SetButtonText(optionNames[i]);
	}

	if (optionNames.size() > 0)
	{
		mButtons[mHighlightedOption].SetHighlighted(true);
	}


	ButtonAction upAction;
	upAction.key = GameController::UpArrow();
	upAction.action = [this](SDL_KeyCode key)
	{
		if (GameController::IsPressed(key))
		{
			SetPreviousButtonHighlighted();
		}
	};

	GetGameController()->SetButtonActionForKey(upAction);


	ButtonAction downAction;
	downAction.key = GameController::DownArrow();
	downAction.action = [this](SDL_KeyCode key)
	{
		if (GameController::IsPressed(key))
		{
			SetNextButtonHighlighted();
		}
	};

	GetGameController()->SetButtonActionForKey(downAction);

	ButtonAction acceptAction;
	acceptAction.key = GameController::EnterKey();
	acceptAction.action = [this](SDL_KeyCode key)
	{
		if (GameController::IsPressed(key))
		{
			ExecuteCurrentButtonAction();
		}
	};

	GetGameController()->SetButtonActionForKey(acceptAction);

	uint32_t height = PingPong::GetInstance().Height();
	uint32_t width = PingPong::GetInstance().Width();

	Size fontSize = font.GetSizeOf(mButtons[0].GetButtonText());

	const int BUTTON_PAD = 10;

	unsigned int buttonHeight = fontSize.height + BUTTON_PAD * 2;

	uint32_t maxButtonWidth = fontSize.width;

	for (const auto& button : mButtons)
	{
		Size s = font.GetSizeOf(button.GetButtonText());

		if (s.width > maxButtonWidth)
		{
			maxButtonWidth = s.width;
		}
	}

	maxButtonWidth += BUTTON_PAD * 2;

	const uint32_t Y_PAD = 1;

	uint32_t yOffset = height / 2 - ((buttonHeight + Y_PAD) * static_cast<uint32_t>(mButtons.size())) / 2;

	for (auto& button : mButtons)
	{
		button.Init(Vector2D(width / 2 - maxButtonWidth / 2, yOffset), maxButtonWidth, buttonHeight);

		yOffset += buttonHeight + Y_PAD;
	}

	mButtons[mHighlightedOption].SetHighlighted(true);

	SetButtonActions();
}

void MainMenuScene::Update(uint32_t deltaTime) {
	
}

void MainMenuScene::Draw(Screen& screen) {
	for (auto& button : mButtons)
	{
		button.Draw(screen);
	}
}

void MainMenuScene::SetButtonActions()
{
	mButtons[0].SetButtonAction([] {
		PingPong::GetInstance().SetActiveSceneType(
			PingPong::GetInstance().GetActiveSceneType() == SceneType::MainMenu_Scene ? SceneType::Gameplay_Scene : SceneType::MainMenu_Scene);
		});

	mButtons[1].SetButtonAction([] {
		PingPong::GetInstance().QuitGame();
		});
}

void MainMenuScene::SetNextButtonHighlighted()
{
	mHighlightedOption = (mHighlightedOption + 1) % mButtons.size();

	HighlightCurrentButton();
}

void MainMenuScene::SetPreviousButtonHighlighted()
{
	--mHighlightedOption;

	if (mHighlightedOption < 0)
	{
		mHighlightedOption = static_cast<int>(mButtons.size()) - 1;
	}

	HighlightCurrentButton();
}

void MainMenuScene::ExecuteCurrentButtonAction()
{
	mButtons[mHighlightedOption].ExecuteAction();
}

void MainMenuScene::HighlightCurrentButton()
{
	for (auto& button : mButtons)
	{
		button.SetHighlighted(false);
	}

	mButtons[mHighlightedOption].SetHighlighted(true);
}