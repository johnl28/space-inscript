#include "Core.h"
#include "GameCore.h"

#include "GameView.h"

#include "Controller/EnemyController.h"
#include "Controller/PlayerController.h"
#include "Controller/CoinController.h"

#include "Entity/CoinActor.h"
#include "Entity/Enemy.h"

#include "Event/EnemySpawnEvent.h"
#include "Event/CoinSpawnEvent.h"
#include "Event/DifficultyTrackEvent.h"

void GameCore::Initialise()
{
	m_actorManager = std::make_shared<ActorManager>();
	m_eventManager = std::make_shared<EventManager>();

	InitUI();
}

void GameCore::InitUI()
{
	m_gameWindow = std::make_unique<UIGameWindow>(1, 5, 29, 30);
	m_gameWindow->Initialise();
	m_gameWindow->SetVisible(false);

	m_menuWindow = std::make_unique<UIMenuWindow>(1, 5, 29, 30);
	m_menuWindow->Initialise();

}

void GameCore::Update()
{
	m_menuWindow->Update();

	if (m_state != GameState::STATE_PLAYING)
	{
		return;
	}

	m_actorManager->Update();
	m_eventManager->Update();
}

void GameCore::StartGame()
{
	ResetLevel();

	SpawnPlayer(5, 5);
	CreateSpawnEvent();

	m_menuWindow->SetVisible(false);
	m_gameWindow->SetVisible(true);
	SetState(GameState::STATE_PLAYING);
}

void GameCore::GameOver()
{
	SetState(GameState::STATE_GAME_OVER);
}

void GameCore::ResetLevel()
{
	SetScore(0);
	SetDifficulty(0);

	m_actorManager->Reset();
	m_eventManager->Reset();
}


void GameCore::SetState(GameState state)
{
	m_state = state;
}

GameState GameCore::GetState() const
{
	return m_state;
}


int GameCore::GetScore() const
{
	return m_gameScore;
}

void GameCore::SetScore(int score)
{
	m_gameScore = score;
	m_gameWindow->SetScore(m_gameScore);
}

void GameCore::IncrementScore()
{
	SetScore(m_gameScore + 1);
}

void GameCore::SetDifficulty(int difficulty)
{
	m_gameDifficulty = difficulty;
	m_gameWindow->SetDifficulty(m_gameDifficulty);
}

int GameCore::GetDifficulty()
{
	return m_gameDifficulty;
}


void GameCore::IncrementDifficulty()
{
	SetDifficulty(m_gameDifficulty+1);
}

void GameCore::CreateSpawnEvent()
{
	EnemySpawnEvent* enemySpawnEvent = new EnemySpawnEvent(500);
	m_eventManager->QueueEvent(enemySpawnEvent);

	m_spawnEnemyEvent = std::shared_ptr<EnemySpawnEvent>(enemySpawnEvent);

	Event* coinSpawnEvent = new CoinSpawnEvent(500);
	m_eventManager->QueueEvent(coinSpawnEvent);

	Event* difficultyEvent = new DifficultyEvent(1000 * 30);
	m_eventManager->QueueEvent(difficultyEvent);
}


bool GameCore::SpawnPlayer(int x, int y)
{
	if (m_player) {
		return false;
	}

	m_player = std::make_shared<Player>();
	m_player->SetXY(x, y);

	auto playerController = new PlayerController(m_player.get());
	m_player->SetController(playerController);

	m_actorManager->SetPlayer(m_player);
	return true;
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

void GameCore::SpawnRandomEnemy()
{

	auto worldWidth = GameView::GetInstance()->GetWidth();
	auto worldHeight = GameView::GetInstance()->GetHeight();

	int x = rand() % (worldWidth + 50) + worldWidth;
	int y = rand() % worldHeight;

	SpawnEnemy(x, y);
	
}

void GameCore::SpawnEnemy(int x, int y)
{
	static int enemyId = 2;
	auto enemy = std::make_shared<Enemy>(enemyId++);


	enemy->SetXY(x, y);

	auto enemyController = new EnemyController(enemy.get());
	enemy->SetController(enemyController);

	m_actorManager->AddActor(enemy);
}

void GameCore::SpawnRandomCoin()
{
	auto worldWidth = GameView::GetInstance()->GetWidth();
	auto worldHeight = GameView::GetInstance()->GetHeight();

	int x = rand() % (worldWidth + 50) + worldWidth;
	int y = rand() % worldHeight;

	SpawnCoin(x, y);
}

void GameCore::SpawnCoin(int x, int y)
{
	static int coinId = 10000;
	auto coin = std::make_shared<CoinActor>(coinId++);

	coin->SetXY(x, y);

	auto coinController = new CoinController(coin.get());
	coin->SetController(coinController);

	m_actorManager->AddActor(coin);
}
