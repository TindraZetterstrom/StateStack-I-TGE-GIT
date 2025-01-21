#pragma once
#include "State.h"

class Options : public State
{
public:
	Options();
	~Options();

	SomethingWitty Update(Tga::InputManager* anInputManager) override;
	void Render() override;
};

