#pragma once
#include "Core.h"
#include "Renderer.h"
#include "InputManager.h"


enum GameState {
	STATE_NONE = 0,

	STATE_MAIN_NENU,
	STATE_PAUSE,
	STATE_PLAYING
};


class Application
{
public:
	Application();
	void Run();


private:
	GameState m_state = STATE_NONE;
	bool m_running = false;

	Renderer m_renderer;
	InputManager m_inputManager;
};

