#include "Application.h"


#include "Renderer.h"
#include "UserInterface.h"
#include "GameView.h"

#include "DebugMonitor.h"
#include "PerformanceMonitor.h"


Application::Application(int width, int height): m_width(width), m_height(height)
{
	Renderer::GetInstance()->Initialise(width, height);

	GameView::GetInstance()->Initialise(1.0f, 1.0f,  width - 30, height - 2);
	UI::GetInstance()->Initialise(to_float(width - 30 + 1), 1.0f, 30, height - 2);

	//GameView::GetInstance()->Initialise(1.0f, 1.0f,  width, height - 2);
	//UI::GetInstance()->Initialise(1.0f, 1.0f, width, height - 2);

	PerformanceMonitor::GetInstance()->Initialise();
	DebugMonitor::GetInstance()->Initialise();

	LevelManager::GetInstance()->Initialise();

}

void Application::Destroy()
{
	Renderer::GetInstance()->Destroy();
}


void Application::Run()
{
	m_running = true;


	while (m_running)
	{
		if (CanUpdate())
		{
			// Update Game Logic
			LevelManager::GetInstance()->Update();
		}
		
		GameView::GetInstance()->Render();
		UI::GetInstance()->Render();
		
		DebugMonitor::GetInstance()->Update();
		Renderer::GetInstance()->Draw();
		
		
		PerformanceMonitor::GetInstance()->Update();

		Sleep(1000 / MAX_FPS);
	}
}

bool Application::CanUpdate()
{
	using Clock = std::chrono::high_resolution_clock;
	static auto lastDrawTime = Clock::now();

	std::chrono::milliseconds drawInterval(1000 / MAX_TPS);

	auto currentTime = Clock::now();
	if (currentTime - lastDrawTime >= drawInterval) 
	{
		lastDrawTime = currentTime;
		return true;
	}

	return false;
}



