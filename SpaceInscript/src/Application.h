#pragma once
#include "Core.h"


class Application
{
public:
	Application(int width, int height);
	void Run();
	bool CanUpdate();

	void Destroy();

private:
	bool m_running = false;

	int m_width;
	int m_height;
};

