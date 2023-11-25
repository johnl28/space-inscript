
#include "DebugMonitor.h"
#include "PerformanceMonitor.h"
#include "Renderer.h"
#include "UserInterface.h"
#include "GameView.h"

#include "Application.h"


Application::Application(int width, int height): m_width(width), m_height(height)
{
	Renderer::GetInstance()->Initialise(width, height);

	UI::GetInstance()->Initialise(width - 30 + 1, 1, 30, height - 2);
	GameView::GetInstance()->Initialise(1, 1,  width - 30, height - 2);

	PerformanceMonitor::GetInstance()->Initialise();

	this->InitGameCore();

	DebugMonitor::GetInstance()->Initialise(m_gameCore);
}

void Application::InitGameCore()
{
	m_gameCore = std::make_shared<GameCore>(m_width, m_height);
}

void Application::Run()
{
	m_running = true;

	while (m_running)
	{
		//if (m_state == STATE_PLAYING)
		{
			m_gameCore->Update();
		}


		UI::GetInstance()->Update();
		GameView::GetInstance()->Update();
		Renderer::GetInstance()->Draw();

		PerformanceMonitor::GetInstance()->Update();
		DebugMonitor::GetInstance()->Update();

		Sleep(1000 / MAX_TPS);

	}
}




