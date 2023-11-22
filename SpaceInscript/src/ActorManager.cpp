#include "ActorManager.h"
#include "Enemy.h"


void ActorManager::Update()
{
	for (auto it : m_actors)
	{
		auto actor = it.second;

		if (actor->IsDestroyed()) 
		{
			DeleteActor(actor);
			continue;
		}
		else if (!actor->IsActive())
		{
			continue;
		}


		actor->Update();
	}
}


bool ActorManager::AddActor(std::shared_ptr<Actor> actor)
{
	auto it = m_actors.find(actor->GetID());

	if (it != m_actors.end())
	{
		return false;
	}

	m_actors.emplace(actor->GetID(), actor);

	Renderer::GetInstance()->AddGameObject(actor);

	return true;
}


bool ActorManager::DeleteActor(std::shared_ptr<Actor> actor)
{
	auto it = m_actors.find(actor->GetID());

	if (it == m_actors.end())
	{
		return false;
	}

	Renderer::GetInstance()->DeleteGameObject(actor);
	m_actors.erase(it);
	return true;
}
