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
	Application(int width, int height);
	void Run();


private:
	GameState m_state = STATE_NONE;
	bool m_running = false;

	std::shared_ptr<Renderer> m_renderer = nullptr;
	std::shared_ptr<InputManager> m_inputManager = nullptr;
};

