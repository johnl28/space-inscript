#pragma once
#include "Singleton.h"
#include "ActorManager.h"
#include "EventManager.h"

#include "Entity/Player.h"

#include "UI/UIPauseMenu.h"
#include "UI/UIMenuWindow.h"
#include "UI/UIGameWindow.h"

#include "Event/Event.h"

enum class GameState {
	STATE_MENU = 0,
	STATE_PLAYING,
	STATE_PAUSE,
	STATE_GAME_OVER
};


class LevelManager: public Singleton<LevelManager>
{
public:
	void Initialise();
	void Update();

	void StartGame();
	void GameOver();
	void ExitToMainMenu();

	void TogglePauseGame();

	void SetGameState(GameState state);
	GameState GetGameState() const;

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
	void InitUI();

	void ResetLevel();
	void CreateEvents();

	void SpawnCoin(float x, float y);
	void SpawnEnemy(float x, float y);
	bool SpawnPlayer(float x, float y);

private:
	GameState m_state = GameState::STATE_MENU;

	int m_gameScore = 0;
	int m_gameDifficulty = 1;

	std::shared_ptr<Player> m_player = nullptr;

	std::unique_ptr<UIGameWindow> m_uiGameWindow = nullptr;
	std::unique_ptr<UIMenuWindow> m_uiMenuWindow = nullptr;
	std::unique_ptr<UIPauseMenu> m_uiPauseMenuWindow = nullptr;


	std::shared_ptr<EventManager> m_eventManager = nullptr;
	std::shared_ptr<ActorManager> m_actorManager = nullptr;

	std::shared_ptr<LoopEvent> m_spawnEnemyEvent = nullptr;


};

