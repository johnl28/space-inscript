#include "GameView.h"



void GameView::Update()
{
	RenderGameObjects();
}

void GameView::AddGameObject(std::shared_ptr<GameObject> object)
{
	m_objects[object->GetID()] = object;
}

bool GameView::DeleteGameObject(std::shared_ptr<GameObject> object)
{
	auto it = m_objects.find(object->GetID());
	if (it == m_objects.end()) 
	{
		return false;
	}

	m_objects.erase(it);

	return true;
}

void GameView::RenderGameObjects()
{
	for (auto &it : m_objects)
	{
		auto object = it.second;
		RenderGameObject(object.get());
	}
}

void GameView::RenderGameObject(const GameObject* object)
{
	if (!object->IsVisible() || IsObjectClipped(object))
	{
		return;
	}

	Position pos = object->GetPosition();
	LocalPosToScreenPos(&pos);

	auto objectSymbol = object->GetSymbol();

	for (int i = 0; i < objectSymbol->size(); ++i)
	{
		Renderer::GetInstance()->DrawPixel(pos.x + i, pos.y, objectSymbol->at(i));
	}

}



bool GameView::IsObjectClipped(const GameObject* object) const
{
	Position pos = object->GetPosition();

	if (pos.x + (object->GetWidth() - 1) >= m_width || pos.x < 0 || pos.y >= m_height || pos.y < 0)
	{
		return true;
	}

	return false;
}