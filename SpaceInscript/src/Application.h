#pragma once
#include <memory>

#include "Renderer.h"
#include "Input.h"


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

	std::shared_ptr<Renderer> m_renderer = nullptr;
};

