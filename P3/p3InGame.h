#pragma once
#include "State.h"
#include <tge/scene/Scene.h>
#include "Player.h"
#include <tge/scene/SceneObjectDefinitionManager.h>
#include "Camera.h"

class InGame : public State
{
public:
	InGame();
	~InGame();

	void ParseObjectsFromScene(const Tga::Scene& aScene, Tga::SceneObjectDefinitionManager& aObjectDefinitionManager);

	StateStackEnumClass Update(const float& aDeltaTime) override;
	void Render() override;

private:
	Player myPlayer;
	CameraWrapper myCameraWrapper;
};

