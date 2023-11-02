#include "Application.h"


Application::Application()
{
	m_renderer = Renderer();
	m_inputManager = InputManager();
}

void Application::Run()
{
	m_running = true;

	while (m_running)
	{
		m_renderer.OnUpdate();
		m_inputManager.OnUpdate();
	}
}

