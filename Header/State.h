#pragma once

#include <tge/sprite/sprite.h>

namespace Tga
{
	class InputManager;
}

enum class SomethingWitty
{
	MainMenu,
	Options,
	InGame,
	Pop,
	Count
};

class State
{
public:
	State() = default;
	~State() = default;

	virtual SomethingWitty Update(Tga::InputManager* anInputManager) = 0;
	virtual void Render() = 0;

	SomethingWitty GetState()
	{
		return myState;
	}

protected:
	Tga::Sprite2DInstanceData mySpriteInstance = {};
	Tga::SpriteSharedData mySharedData = {};
	SomethingWitty myState;
};

