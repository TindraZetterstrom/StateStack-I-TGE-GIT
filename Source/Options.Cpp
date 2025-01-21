#include "Options.h"

#include <tge/Engine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/input/InputManager.h>
#include <tge/texture/TextureManager.h>

Options::Options()
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { static_cast<float>(intResolution.x), static_cast<float>(intResolution.y) };

	mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/OptionsFinal.png");
	mySpriteInstance.myPivot = { 0.5f, 0.5f };
	mySpriteInstance.myPosition = Tga::Vector2f{ 0.5f, 0.5f }*resolution;
	mySpriteInstance.mySize = { 0.8f * resolution.x, 0.8f * resolution.y };

	myState = SomethingWitty::Options;
}

Options::~Options()
{}

SomethingWitty Options::Update(Tga::InputManager* anInputManager)
{
	if (anInputManager->IsKeyPressed(VK_ESCAPE))
	{
		return SomethingWitty::Pop;
	}

	return SomethingWitty::Count;
}

void Options::Render()
{
	auto& engine = *Tga::Engine::GetInstance();
	auto& spriteDrawer = engine.GetGraphicsEngine().GetSpriteDrawer();
	spriteDrawer.Draw(mySharedData, mySpriteInstance);
}