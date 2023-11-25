#pragma once
#include "Core.h"
#include "GameCore.h"

enum GameState {
	STATE_NONE = 0,
	STATE_PLAYING
};


class Application
{
public:
	Application(int width, int height);
	void Run();

private:
	void InitGameCore();


private:
	GameState m_state = STATE_NONE;

	std::shared_ptr<GameCore> m_gameCore;

	bool m_running = false;

	int m_width;
	int m_height;

};

