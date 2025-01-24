#include "InGame.h"

#include <tge/Engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <CommonUtilities/InputHandler.h>
#include <tge/texture/TextureManager.h>
#include <tge/graphics/DX11.h>
#include <tge/model/ModelInstance.h>
#include <tge/model/ModelFactory.h>
#include <tge/scene/ScenePropertyTypes.h>
#include <tge/settings/settings.h>

InGame::InGame()
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { static_cast<float>(intResolution.x), static_cast<float>(intResolution.y) };

	mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/InGamePlaceHolder.png");
	mySpriteInstance.myPivot = { 0.5f, 0.5f };
	mySpriteInstance.myPosition = Tga::Vector2f{ 0.f, 0.f }*resolution;
	mySpriteInstance.mySize = {0.7f* resolution.x,0.7f* resolution.y };

	myState = StateStackEnumClass::InGame;

	Tga::Camera camera;
	camera.SetPerspectiveProjection(
		90,
		{
			(float)resolution.x,
			(float)resolution.y
		},
		0.1f,
		50000.0f
	);

	camera.GetTransform().SetPosition(Tga::Vector3f(0.0f, 0.0f, -550.0f));

	myCameraWrapper.Init(camera);
}

InGame::~InGame(){}

void InGame::ParseObjectsFromScene(const Tga::Scene& aScene, Tga::SceneObjectDefinitionManager& aObjectDefinitionManager)
{
	auto& engine = *Tga::Engine::GetInstance();
	auto& textureManager = engine.GetTextureManager();

	std::vector<Tga::ScenePropertyDefinition> sceneObjectProperties;

	Tga::StringId playerName = Tga::StringRegistry::RegisterOrGetString("player");

	for (auto& p : aScene.GetSceneObjects())
	{
		sceneObjectProperties.clear();
		p.second->CalculateCombinedPropertySet(aObjectDefinitionManager, sceneObjectProperties);

		Tga::StringId objectName = Tga::StringRegistry::RegisterOrGetString(p.second->GetName());

		// TODO: Parse the player model/sprite etc when available
		if (objectName == playerName)
		{
			std::cout << "Player found at " << p.second->GetPosition() << std::endl;
			PlayerData data;
			data.transform = p.second->GetTransform();

			for (Tga::ScenePropertyDefinition& property : sceneObjectProperties)
			{
				if (property.type == Tga::GetPropertyType<Tga::CopyOnWriteWrapper<Tga::SceneModel>>())
				{
					const Tga::SceneModel& value = property.value.Get<Tga::CopyOnWriteWrapper<Tga::SceneModel>>()->Get();

					std::wstring path = string_cast<std::wstring>(value.path.GetString());
					if (path.empty() || Tga::Settings::ResolveAssetPathW(path).empty())
						continue;

					if (Tga::ModelFactory::GetInstance().GetModel(path))
					{
						Tga::ModelInstance instance = Tga::ModelFactory::GetInstance().GetModelInstance(path);
						int meshCount = (int)instance.GetModel()->GetMeshCount();
						if (meshCount > MAX_MESHES_PER_MODEL)
							meshCount = MAX_MESHES_PER_MODEL;

						for (int i = 0; i < meshCount; i++)
						{
							if (!value.textures[i][0].IsEmpty())
							{
								std::wstring texturePath = string_cast<std::wstring>(value.textures[i][0].GetString());
								Tga::Texture* texture = textureManager.TryGetTexture(texturePath.c_str());

								if (texture != nullptr)
									instance.SetTexture(i, 0, texture);
							}
						}

						data.modelInstance = instance;
					}
				}
			}

			myPlayer.Init(data);
		}
	}
}



StateStackEnumClass InGame::Update(const float& aDeltaTime)
{
	myPlayer.Update(aDeltaTime);

	if (CommonUtilities::InputHandler::GetInstance().IsKeyPressed(VK_ESCAPE))
	{
		return StateStackEnumClass::Pop;
	}

	if (CommonUtilities::InputHandler::GetInstance().IsKeyPressed(CommonUtilities::VK_O))
	{
		return StateStackEnumClass::Options;
	}

	return StateStackEnumClass::Count;
}

void InGame::Render()
{
	Tga::DX11::BackBuffer->SetAsActiveTarget(Tga::DX11::DepthBuffer);

	auto& engine = *Tga::Engine::GetInstance();
	//auto& textureManager = engine.GetTextureManager();

	auto& graphicsStateStack = engine.GetGraphicsEngine().GetGraphicsStateStack();

	Tga::Vector2ui resolution = Tga::Engine::GetInstance()->GetRenderSize();
	
	graphicsStateStack.SetCamera(myCameraWrapper.GetCamera());

	graphicsStateStack.Push();
	graphicsStateStack.SetBlendState(Tga::BlendState::Disabled);

	myPlayer.Render();

	graphicsStateStack.Pop();
	graphicsStateStack.SetDefaultCamera();

	Tga::DX11::BackBuffer->SetAsActiveTarget(nullptr);
}