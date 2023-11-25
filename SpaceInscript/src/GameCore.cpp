#include "Core.h"
#include "GameCore.h"
#include "ActorManager.h"
#include "EventManager.h"

#include "Entity/Enemy.h"
#include "Event/EnemySpawnEvent.h"

GameCore::GameCore(int worldWidth, int worldHeight): m_worldWidth(worldWidth), m_worldHeight(worldHeight)
{
	Initialise();
}


void GameCore::Initialise()
{
	m_actorManager = std::make_shared<ActorManager>();
	m_eventManager = std::make_shared<EventManager>();

	StartGame();
}


void GameCore::Update()
{
	m_actorManager->Update();
	m_eventManager->Update();
}

void GameCore::StartGame()
{
	SpawnPlayer(5, 5);
	CreateSpawnEvent();
}

void GameCore::CreateSpawnEvent()
{
	Event* spawnEvent = new EnemySpawnEvent(500, std::shared_ptr<GameCore>(this));
	m_eventManager->QueueEvent(spawnEvent);
}


bool GameCore::SpawnPlayer(int x, int y)
{
	if (m_player) {
		return false;
	}

	m_player = std::make_shared<Player>();
	m_player->SetXY(x, y);

	return m_actorManager->AddActor(m_player);
}

Player* GameCore::GetPlayer()
{
	return m_player.get();
}

EventManager* GameCore::GetEventManager()
{
	return m_eventManager.get();
}

ActorManager* GameCore::GetActorManager()
{
	return m_actorManager.get();
}

void GameCore::SpawnEnemy(int x, int y)
{
	static int enemyId = 2;
	auto enemy = std::make_shared<Enemy>(enemyId++);
	enemy->SetXY(x, y);

	m_actorManager->AddActor(enemy);
}

void GameCore::SpawnRandomEnemy()
{
	int x = rand() % (m_worldWidth + 50) + m_worldWidth;
	int y = rand() % m_worldHeight;

	SpawnEnemy(x, y);
}