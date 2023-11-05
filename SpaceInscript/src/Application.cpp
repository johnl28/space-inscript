#include "Application.h"


Application::Application(int width, int height)
{
	m_renderer = std::make_shared<Renderer>(width, height);
	m_inputManager = std::make_shared<InputManager>();
}

void Application::Run()
{
	m_running = true;

	while (m_running)
	{
		m_inputManager->OnUpdate();
		m_renderer->OnUpdate();

		Sleep(1000 / MAX_TPS);
	}
}

