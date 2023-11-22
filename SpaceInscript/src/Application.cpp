
#include "PerformanceMonitor.h"

#include "ActorManager.h"
#include "Renderer.h"
#include "GameCore.h"

#include "Application.h"


Application::Application(int width, int height): m_width(width), m_height(height)
{
	PerformanceMonitor::GetInstance()->Initialise();

	Renderer::GetInstance()->Initialise(width, height);
	ActorManager::GetInstance()->Initialise();
	GameCore::GetInstance()->Initialise();
}

void Application::Run()
{
	m_running = true;

	while (m_running)
	{
		if (m_state == STATE_PLAYING)
		{
			ActorManager::GetInstance()->Update();
			GameCore::GetInstance()->Update();
		}

		Renderer::GetInstance()->Update();

#ifdef _DEBUG
		PrintDebugInfo();
#endif

		PerformanceMonitor::GetInstance()->ComputeFrameTime();

		Sleep(1000 / MAX_TPS);

	}
}


inline void Application::PrintDebugInfo()
{
	const int overflowY = m_height + 2;
	PrintToCoordinates(0, overflowY, "deltaTime %f", PerformanceMonitor::GetInstance()->GetDeltaTime());
	PrintToCoordinates(0, overflowY + 1, "FPS %.0f", PerformanceMonitor::GetInstance()->GetFPS());
}

