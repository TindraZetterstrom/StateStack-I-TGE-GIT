#include "GameWorld.h"

#include <tge/scene/Scene.h>
#include <tge/settings/settings.h>

#include "InGame.h"
#include "StateStack.h"


using namespace Tga;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Init(Tga::Scene& aScene)
{
	mySceneObjectDefinitionManager.Init(Settings::GameAssetRoot().string().c_str());

	myInGame.ParseObjectsFromScene(aScene, mySceneObjectDefinitionManager);

	myStateStack.PushState(&myMainMenu);
}

void GameWorld::Update(float aTimeDelta)
{
	// State Stack
	switch (myStateStack.GetTopState()->Update(aTimeDelta))
	{
		case StateStackEnumClass::MainMenu:
		{
			break;
		}
		case StateStackEnumClass::Options:
		{
			myStateStack.SetPreviousState(myStateStack.GetTopState());
			myStateStack.PushState(&myOptions);
			break;
		}
		case StateStackEnumClass::InGame:
		{
			myStateStack.PushState(&myInGame);
			break;
		}
		case StateStackEnumClass::Pop:
		{
			myStateStack.PopState();
			break;
		}
		case StateStackEnumClass::Count:
		{
			break;
		}
		default:
			break;
	}

	if (myStateStack.GetStack().empty())
	{
		PostQuitMessage(0);
	}
}

void GameWorld::Render()
{
	// State Stack Render
	if (myStateStack.GetTopState() == nullptr)
	{
		return;
	}
	if (myStateStack.GetTopState()->GetState() == StateStackEnumClass::Options)
	{
		myStateStack.GetPreviousState()->Render();
	}

	myStateStack.GetTopState()->Render();
}