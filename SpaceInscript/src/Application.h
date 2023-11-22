#pragma once

#include "Core.h"


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
	inline void PrintDebugInfo();


private:
	GameState m_state = STATE_NONE;
	bool m_running = false;

	int m_width;
	int m_height;

};

