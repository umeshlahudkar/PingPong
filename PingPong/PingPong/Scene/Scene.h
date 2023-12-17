#pragma once

#include <stdint.h>
#include <string>
#include "../Input/GameController.h"


class Screen;


enum SceneType
{
	MainMenu_Scene = 0,
	Gameplay_Scene
};

class Scene {

public :
	Scene(SceneType scene) : mScene(scene) {}
	virtual void Init() = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;

	inline SceneType GetSceneType() const { return mScene; }
	inline GameController* GetGameController() { return &mGameController; }

private :
	SceneType mScene;
	GameController mGameController;
};