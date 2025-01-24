#pragma once

#include <tge/scene/SceneObjectDefinitionManager.h>
#include "StateStack.h"
#include "MainMenu.h"
#include "Options.h"
#include "InGame.h"

namespace Tga 
{
	class Scene;
}

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();
		
	void Init(Tga::Scene& aScene);
	void Update(float aTimeDelta);
	void Render();

private:
	Tga::SceneObjectDefinitionManager mySceneObjectDefinitionManager;

	// For State Stack
	StateStack myStateStack;
	MainMenu myMainMenu;
	Options myOptions;
	InGame myInGame;
};