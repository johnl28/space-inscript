#include "Core.h"
#include "LevelManager.h"

#include "GameView.h"

#include "Controller/EnemyController.h"
#include "Controller/PlayerController.h"
#include "Controller/CoinController.h"

#include "Entity/CoinActor.h"
#include "Entity/Enemy.h"



#include "Event/EnemySpawnEvent.h"
#include "Event/CoinSpawnEvent.h"
#include "Event/DifficultyTrackEvent.h"

void LevelManager::Initialise()
{
	m_actorManager = std::make_shared<ActorManager>();
	m_eventManager = std::make_shared<EventManager>();

	InitUI();
}

void LevelManager::InitUI()
{
	m_uiGameWindow = std::make_unique<UIGameWindow>(1.0f, 5.0f, 29, 5);
	m_uiGameWindow->Initialise();

	m_uiMenuWindow = std::make_unique<UIMenuWindow>(60.0f, 5.0f, 29, 9);
	m_uiMenuWindow->Initialise();

	m_uiPauseMenuWindow = std::make_unique<UIPauseMenu>(60.0f, 5.0f, 29, 7);
	m_uiPauseMenuWindow->Initialise();
	m_uiPauseMenuWindow->Hide();
}

void LevelManager::Update()
{
	m_uiMenuWindow->Update();
	m_uiPauseMenuWindow->Update();


	if (GetAsyncKeyState('R') & 0x8000 && m_state == GameState::STATE_GAME_OVER)
	{
		StartGame();
		Sleep(60); // use a different approach
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		TogglePauseGame();
		Sleep(60); // use a different approach
	}

	if (m_state != GameState::STATE_PLAYING)
	{
		return;
	}


	m_uiGameWindow->Update();
	m_actorManager->Update();
	m_eventManager->Update();
}

void LevelManager::ExitToMainMenu()
{
	SetGameState(GameState::STATE_MENU);
	ResetLevel();

	m_uiPauseMenuWindow->Hide();
	m_uiMenuWindow->Show();
}

void LevelManager::StartGame()
{
	ResetLevel();

	SpawnPlayer(5, GameView::GetInstance()->GetHeight() / 2.0f - 1.0f);
	CreateEvents();

	m_uiMenuWindow->Hide();

	m_uiGameWindow->Reset();


	SetGameState(GameState::STATE_PLAYING);
}

void LevelManager::ResetLevel()
{
	SetScore(0);
	SetDifficulty(0);

	m_player.reset();
	m_spawnEnemyEvent.reset();

	m_actorManager->Reset();
	m_eventManager->Reset();
}

void LevelManager::GameOver()
{
	SetGameState(GameState::STATE_GAME_OVER);

	m_uiGameWindow->ShowGameOver();
}

void LevelManager::TogglePauseGame()
{
	if (m_state == GameState::STATE_PLAYING)
	{
		SetGameState(GameState::STATE_PAUSE);
		m_uiPauseMenuWindow->Show();
	}
	else if(m_state == GameState::STATE_PAUSE)
	{
		SetGameState(GameState::STATE_PLAYING);
		m_uiPauseMenuWindow->Hide();
	}
}


void LevelManager::SetGameState(GameState state)
{
	m_state = state;
}

GameState LevelManager::GetGameState() const
{
	return m_state;
}


int LevelManager::GetScore() const
{
	return m_gameScore;
}

void LevelManager::SetScore(int score)
{
	m_gameScore = score;
	m_uiGameWindow->SetScore(m_gameScore);
}

void LevelManager::IncrementScore()
{
	SetScore(m_gameScore + 1);
}

void LevelManager::SetDifficulty(int difficulty)
{
	m_gameDifficulty = difficulty;
	m_uiGameWindow->SetDifficulty(m_gameDifficulty);

	if (difficulty > 2)
	{
		m_spawnEnemyEvent->SetLoopInterval(500 - difficulty * 50);
	}
}

int LevelManager::GetDifficulty()
{
	return m_gameDifficulty;
}


void LevelManager::IncrementDifficulty()
{
	SetDifficulty(m_gameDifficulty+1);
}

void LevelManager::CreateEvents()
{
	auto enemySpawnEvent = std::make_shared<EnemySpawnEvent>(500);
	m_eventManager->QueueEvent(enemySpawnEvent);

	m_spawnEnemyEvent = enemySpawnEvent;

	auto coinSpawnEvent = std::make_shared<CoinSpawnEvent>(500);
	m_eventManager->QueueEvent(coinSpawnEvent);

	auto difficultyEvent = std::make_shared<DifficultyEvent>(1000 * 30);
	m_eventManager->QueueEvent(difficultyEvent);
}


bool LevelManager::SpawnPlayer(float x, float y)
{
	if (m_player) {
		return false;
	}

	m_player = std::make_shared<Player>();
	m_player->SetXY(x, y);

	auto playerController = new PlayerController(m_player);
	m_player->SetController(playerController);

	m_actorManager->SetPlayer(m_player);
	return true;
}

Player* LevelManager::GetPlayer()
{
	return m_player.get();
}

EventManager* LevelManager::GetEventManager()
{
	return m_eventManager.get();
}

ActorManager* LevelManager::GetActorManager()
{
	return m_actorManager.get();
}

void LevelManager::SpawnRandomEnemy()
{

	auto worldWidth = GameView::GetInstance()->GetWidth();
	auto worldHeight = GameView::GetInstance()->GetHeight();

	int x = rand() % (worldWidth + 50) + worldWidth;
	int y = rand() % worldHeight;

	SpawnEnemy(to_float(x), to_float(y));
	
}

void LevelManager::SpawnEnemy(float x, float y)
{
	static int enemyId = 2;
	auto enemy = std::make_shared<Enemy>(enemyId++);


	enemy->SetXY(x, y);
	auto speed = 1.0f;


	if (m_gameDifficulty > 2)
	{
		float speed = 2.0f;
	}
	if (m_gameDifficulty > 3)
	{
		int n = rand() % 100;
		if (n > 90)
		{
			speed = 3.0f;
		}
	}
	if (m_gameDifficulty > 4)
	{
		speed = 2.5f;
		int n = rand() % 100;
		if (n > 90)
		{
			speed = 3.5f;
		}
	}

	enemy->SetSpeed(speed);
	auto enemyController = new EnemyController(enemy.get());
	enemy->SetController(enemyController);

	m_actorManager->AddActor(enemy);
}

void LevelManager::SpawnRandomCoin()
{
	auto worldWidth = GameView::GetInstance()->GetWidth();
	auto worldHeight = GameView::GetInstance()->GetHeight();

	int x = rand() % (worldWidth + 50) + worldWidth;
	int y = rand() % worldHeight;

	SpawnCoin(to_float(x), to_float(y));
}

void LevelManager::SpawnCoin(float x, float y)
{
	static int coinId = 10000;
	auto coin = std::make_shared<CoinActor>(coinId++);

	coin->SetXY(x, y);
	if (m_gameDifficulty > 1)
	{
		int speed = rand() % 3 + 1;
		coin->SetSpeed(to_float(speed));
	}

	auto coinController = new CoinController(coin.get());
	coin->SetController(coinController);

	m_actorManager->AddActor(coin);
}
