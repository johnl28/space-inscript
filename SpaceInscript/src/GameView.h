#pragma once
#include "Core.h"
#include "Singleton.h"
#include "Renderer.h"
#include "Entity/GameObject.h"

class GameView: public Viewport, public Singleton<GameView>
{
public:
	void Update();
	void AddGameObject(std::shared_ptr<GameObject> object);
	bool DeleteGameObject(std::shared_ptr<GameObject> object);

	bool IsObjectClipped(const GameObject* object) const;


private:
	void RenderGameObject(const GameObject* object);
	void RenderGameObjects();

private:
	std::map<int, std::shared_ptr<GameObject>> m_objects;
};

