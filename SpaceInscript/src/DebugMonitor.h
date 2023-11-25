#pragma once
#include "Core.h"
#include "Singleton.h"
#include "PerformanceMonitor.h"
#include "Renderer.h"
#include "GameCore.h"
#include "UserInterface.h"

class DebugMonitor : public Singleton<DebugMonitor>
{
public:
	void Initialise(std::shared_ptr<GameCore> gameCore)
	{
		m_gameCore = gameCore;

		InitialiseDebugWindow();
	}

	void InitialiseDebugWindow()
	{

		int debugWindowHeight = 8;

		m_debugWindow = UI::GetInstance()->CreateBox(50, UI::GetInstance()->GetHeight() - debugWindowHeight, 29, 5);

		auto horLine = UI::GetInstance()->CreateHorizontalLine(0, 0, 0);
		horLine->SetParent(m_debugWindow);
		horLine->SetWidth(m_debugWindow->GetWidth());

		m_textPlayerPos = UI::GetInstance()->CreateText(1, 2, "PlayerPosition");
		m_textPlayerPos->SetParent(m_debugWindow);

		m_textFPS = UI::GetInstance()->CreateText(1, 3, "FPS");
		m_textFPS->SetParent(m_debugWindow);

		m_textTickRate = UI::GetInstance()->CreateText(1, 4, "TickRate");
		m_textTickRate->SetParent(m_debugWindow);

		m_textEventCount = UI::GetInstance()->CreateText(1, 5, "EventCount");
		m_textEventCount->SetParent(m_debugWindow);

		m_textActorCount = UI::GetInstance()->CreateText(1, 6, "ActorCount");
		m_textActorCount->SetParent(m_debugWindow);
	}

	void Update()
	{
		if (!m_enabled)
		{
			return;
		}

		auto performance = PerformanceMonitor::GetInstance();

		auto player = m_gameCore->GetPlayer();
		auto eventManager = m_gameCore->GetEventManager();
		auto actorManager = m_gameCore->GetActorManager();

		if (player)
		{
			m_textPlayerPos->SetText(std::format("Player Position {}x{}", player->GetX(), player->GetY()));
		}

		if (eventManager)
		{
			m_textEventCount->SetText(std::format("Total Events {}", eventManager->GetEventsCount()));
		}

		if (actorManager)
		{
			m_textActorCount->SetText(std::format("Total Actors {}", actorManager->GetActorCount()));
		}

		m_textFPS->SetText(std::format("FPS: {}", performance->GetFPS()));
		m_textTickRate->SetText(std::format("DeltaTime: {:.3f}", performance->GetDeltaTime()));

	}


	void ToggleDebug()
	{
		m_enabled = !m_enabled;
	}

private:

	UIBox* m_debugWindow;

	UIText* m_textPlayerPos;
	UIText* m_textFPS;
	UIText* m_textTickRate;
	UIText* m_textEventCount;
	UIText* m_textActorCount;

	std::shared_ptr<GameCore> m_gameCore;
	bool m_enabled = true;
};

