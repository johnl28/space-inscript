#include "ActorManager.h"
#include "GameView.h"


void ActorManager::Update()
{
	for (auto it = m_actors.begin(); it != m_actors.end();)
	{
		auto actor = it->second;
		it++;

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

	CheckPlayerCollision();
}

void ActorManager::Reset()
{
	for (auto it = m_actors.begin(); it != m_actors.end();)
	{
		auto actor = it->second;
		it++;
		DeleteActor(actor);
	}
}

void ActorManager::CheckPlayerCollision()
{

	if (!m_player)
	{
		return;
	}
	// todo: Use a better algorithm
	// Now is checking collision with all existing Actors
	for (auto it : m_actors)
	{
		auto otherActor = it.second.get();
		if (m_player->GetID() == otherActor->GetID())
		{
			continue;
		}

		if (m_player->IsColliding(otherActor))
		{
			break;
		}
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

	GameView::GetInstance()->AddGameObject(actor);

	return true;
}

void ActorManager::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;

	if(player)
	{
		AddActor(m_player);
	}
}


bool ActorManager::DeleteActor(std::shared_ptr<Actor> actor)
{

	auto it = m_actors.find(actor->GetID());

	if (it == m_actors.end())
	{
		return false;
	}

	GameView::GetInstance()->DeleteGameObject(actor);
	m_actors.erase(it);
	return true;
}

int ActorManager::GetActorCount() const
{
	return static_cast<int>(m_actors.size());
}
