#pragma once
#include "Singleton.h"
#include "ActorManager.h"
#include "EventManager.h"

#include "Entity/Player.h"

#include "UI/UIMenuWindow.h"
#include "UI/UIGameWindow.h"

#include "Event/Event.h"

enum class GameState {
	STATE_MENU = 0,
	STATE_PLAYING,
	STATE_GAME_OVER
};


class GameCore: public Singleton<GameCore>
{
public:
	void Initialise();
	void Update();

	void InitUI();

	void StartGame();
	void GameOver();


	void SetState(GameState state);
	GameState GetState() const;

	EventManager* GetEventManager();
	ActorManager* GetActorManager();
	Player* GetPlayer();

	void SpawnRandomCoin();
	void SpawnRandomEnemy();

	int GetScore() const;
	void SetScore(int score);
	void IncrementScore();


	int GetDifficulty();
	void SetDifficulty(int difficulty);
	void IncrementDifficulty();


private:
	void ResetLevel();
	void CreateSpawnEvent();

	void SpawnCoin(int x, int y);
	void SpawnEnemy(int x, int y);
	bool SpawnPlayer(int x, int y);

private:
	GameState m_state = GameState::STATE_MENU;

	int m_gameScore = 0;
	int m_elapsedSeconds = 0;
	int m_gameDifficulty = 1;

	std::shared_ptr<Player> m_player;

	std::unique_ptr<UIGameWindow> m_gameWindow;
	std::unique_ptr<UIMenuWindow> m_menuWindow;

	std::shared_ptr<EventManager> m_eventManager;
	std::shared_ptr<ActorManager> m_actorManager;

	std::shared_ptr<LoopEvent> m_spawnEnemyEvent;


};

