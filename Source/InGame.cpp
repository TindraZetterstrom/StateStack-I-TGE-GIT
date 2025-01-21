#include "InGame.h"

#include <tge/Engine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/input/InputManager.h>
#include <tge/texture/TextureManager.h>



InGame::InGame()
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { static_cast<float>(intResolution.x), static_cast<float>(intResolution.y) };

	mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/InGameFinal.png");
	mySpriteInstance.myPivot = { 0.5f, 0.5f };
	mySpriteInstance.myPosition = Tga::Vector2f{ 0.5f, 0.5f }*resolution;
	mySpriteInstance.mySize = {resolution.x, resolution.y };

	myState = SomethingWitty::InGame;
}

InGame::~InGame()
{}

SomethingWitty InGame::Update(Tga::InputManager* anInputManager)
{
	if (anInputManager->IsKeyPressed(VK_ESCAPE))
	{
		return SomethingWitty::Pop;
	}

	if (anInputManager->IsKeyPressed('O'))
	{
		return SomethingWitty::Options;
	}

	return SomethingWitty::Count;
}

void InGame::Render()
{
	auto& engine = *Tga::Engine::GetInstance();
	auto& spriteDrawer = engine.GetGraphicsEngine().GetSpriteDrawer();
	spriteDrawer.Draw(mySharedData, mySpriteInstance);
}