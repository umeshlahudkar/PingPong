#pragma once

#include <vector>
#include <cstdint>

#include "../Scene/Scene.h"
#include "../Input/InputController.h"
#include "../Graphics/Screen.h"
#include "../Graphics/BitmapFont.h"


class PingPong {

public:
	~PingPong();
	static PingPong& GetInstance();

	bool Init(uint32_t screenWidth, uint32_t screenHeight);
	void Run();

	inline uint32_t Width() const { return mScreen.GetWidth(); }
	inline uint32_t Height() const { return mScreen.GetHeight(); }

	inline void SetActiveSceneType(SceneType type) { mActiveSceneType = type; }
	inline SceneType GetActiveSceneType() const { return mActiveSceneType; }
	inline const BitmapFont& GetFont() const { return mFont; }

	inline void QuitGame() { mIsRunning = false; }

private:

	void PushScene(Scene* scene);
	Scene* GetActiveScene(SceneType scenetype);
	void ClearAllScene();

	bool mIsRunning;
	SceneType mActiveSceneType;
	Screen mScreen;
	std::vector<Scene*> mSceneStack;
	InputController mInputController;
	BitmapFont mFont;
};