#pragma once

#include "Scene.h"
#include "/PingPong/PingPong/Game/Button.h"

class MainMenuScene : public Scene {

public :
	MainMenuScene() : Scene(SceneType::MainMenu_Scene) {}
	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;

private:
	void SetButtonActions();
	void SetNextButtonHighlighted();
	void SetPreviousButtonHighlighted();
	void ExecuteCurrentButtonAction();
	void HighlightCurrentButton();

	std::vector<Button> mButtons;
	int mHighlightedOption;
};