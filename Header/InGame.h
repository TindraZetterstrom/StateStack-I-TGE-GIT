#pragma once

#include "State.h"

class InGame : public State
{
public:
	InGame();
	~InGame();

	SomethingWitty Update(Tga::InputManager* anInputManager) override;
	void Render() override;
};

