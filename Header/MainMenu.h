#pragma once
#include <tge/sprite/sprite.h> //idk why this is here
#include "State.h"

class MainMenu : public State
{
public:
	MainMenu();
	~MainMenu();

	SomethingWitty Update(Tga::InputManager* anInputManager) override;
	void Render() override;
};

