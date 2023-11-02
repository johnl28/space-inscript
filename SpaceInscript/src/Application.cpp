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
		m_renderer->OnUpdate();
		m_inputManager->OnUpdate();
	}
}

