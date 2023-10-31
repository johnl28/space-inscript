#include "Application.h"


Application::Application()
{
	m_renderer = std::make_shared<Renderer>();
}

void Application::Run()
{
	m_running = true;

	while (m_running)
	{
		m_renderer->OnUpdate();
	}
}

