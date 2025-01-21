#pragma once

class MainMenu;
class Options;
class InGame;
class StateStack;

namespace Tga
{
	class InputManager;
}


class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta, Tga::InputManager* anInputManager); //remember this and in the cpp file
	void Render();
private:
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};



	StateStack* myStateStack;
	MainMenu* myMainMenu;
	Options* myOptions;
	InGame* myInGame;
};