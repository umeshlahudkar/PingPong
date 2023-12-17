
#include <iostream>
#include <SDL.h>

#include "PingPong.h"
#include "../Graphics/Color.h"
#include "../Scene/MainMenuScene.h"
#include "../Scene/GameScene.h"
#include "../Input/InputAction.h"


PingPong& PingPong::GetInstance() {
	static PingPong instance;
	return instance;
}

PingPong::~PingPong() {
	ClearAllScene();
}


bool PingPong::Init(uint32_t screenWidth, uint32_t screenHeight) {

	if (!mFont.Load("D:\\PingPong\\PingPong\\Asset\\ArcadeFont")) {
		return false;
	}

	if (mScreen.Init(screenWidth, screenHeight)) {

		MainMenuScene* mainMenuScene = new MainMenuScene();
		PushScene(mainMenuScene);

		GameScene* gameScene = new GameScene();
		gameScene->SetInputController(&mInputController);
		PushScene(gameScene);

		return true;
	}
	return false;
}

void PingPong::Run() {

	mIsRunning = true;

	mInputController.Init([this](SDL_Keycode key) {
		mIsRunning = false;
	});

	const int targetFrameTime = 1000 / 60; 
	Uint32 previousTime = SDL_GetTicks(); 
	Uint32 currentTime = 0;
	Uint32 elapsedTime = 0;

	while (mIsRunning)
	{

		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - previousTime;



		if (elapsedTime >= targetFrameTime) {
			previousTime = currentTime;

			mInputController.Update(elapsedTime);

			Scene* activeScene = GetActiveScene(mActiveSceneType);

			activeScene->Update(elapsedTime);
			activeScene->Draw(mScreen);

			mScreen.SwapScreen();

			/*mInputController.Update(sdlEvent, isRunning);
			Update(elapsedTime);
			Render();*/
		}
	}
}

void PingPong::PushScene(Scene* scene) {
	scene->Init();
	mSceneStack.push_back(scene);
}

Scene* PingPong::GetActiveScene(SceneType scenetype) {

	for (int i = 0; i < mSceneStack.size(); i++) {
		if (mSceneStack[i]->GetSceneType() == scenetype) {
			mActiveSceneType = mSceneStack[i]->GetSceneType();
			mInputController.SetInputController(mSceneStack[i]->GetGameController());

			return mSceneStack[i];
		}
	}

	return nullptr;
}

void PingPong::ClearAllScene() {

	for (int i = 0; i < mSceneStack.size(); i++)
	{
		delete mSceneStack[i];
	}

	mSceneStack.clear();
}