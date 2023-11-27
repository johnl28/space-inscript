#pragma once
#include "Core.h"
#include "Singleton.h"
#include "PerformanceMonitor.h"
#include "Renderer.h"
#include "LevelManager.h"
#include "GameView.h"
#include "UserInterface.h"

class DebugMonitor : public Singleton<DebugMonitor>
{
public:
	void Initialise()
	{
		InitialiseDebugWindow();
	}

	void InitialiseDebugWindow()
	{

		int debugWindowHeight = 9;

		m_debugWindow = UI::GetInstance()->CreateBox(1, 0, 29, 5);
		m_debugWindow->SetFitChildren(true);

		auto horLine = UI::GetInstance()->CreateHorizontalLine(0, 0, 0);
		horLine->SetWidth(m_debugWindow->GetWidth());
		m_debugWindow->AddChild(horLine);

		m_textPlayerPos = UI::GetInstance()->CreateText(1, 2, "PlayerPosition");
		m_debugWindow->AddChild(m_textPlayerPos);

		m_textFPS = UI::GetInstance()->CreateText(1, 3, "FPS");
		m_debugWindow->AddChild(m_textFPS);

		m_textTickRate = UI::GetInstance()->CreateText(1, 4, "TickRate");
		m_debugWindow->AddChild(m_textTickRate);

		m_textEventCount = UI::GetInstance()->CreateText(1, 5, "EventCount");
		m_debugWindow->AddChild(m_textEventCount);

		m_textActorCount = UI::GetInstance()->CreateText(1, 6, "ActorCount");
		m_debugWindow->AddChild(m_textActorCount);

		m_textObjectCount = UI::GetInstance()->CreateText(1, 7, "ObjectCount");
		m_debugWindow->AddChild(m_textObjectCount);

		m_debugWindow->SetY(to_float(UI::GetInstance()->GetHeight() - m_debugWindow->GetHeight() - 2));
	}

	void Update()
	{
		if (!m_enabled)
		{
			return;
		}

		auto performance = PerformanceMonitor::GetInstance();

		auto player = LevelManager::GetInstance()->GetPlayer();
		auto eventManager = LevelManager::GetInstance()->GetEventManager();
		auto actorManager = LevelManager::GetInstance()->GetActorManager();
		auto gameView = GameView::GetInstance();

		if (player)
		{
			m_textPlayerPos->SetText(std::format("Player Position {:.1f}x{:.1f}", player->GetX(), player->GetY()));
		}

		if (eventManager)
		{
			m_textEventCount->SetText(std::format("Total Events {}", eventManager->GetEventsCount()));
		}

		if (actorManager)
		{
			m_textActorCount->SetText(std::format("Total Actors {}", actorManager->GetActorCount()));
		}
		m_textObjectCount->SetText(std::format("Total Objects: {}", gameView->GetObjectsCount()));

		m_textFPS->SetText(std::format("FPS: {}", performance->GetFPS()));
		m_textTickRate->SetText(std::format("DeltaTime: {:.3f}", performance->GetDeltaTime()));
	}


	void ToggleDebug()
	{
		m_enabled = !m_enabled;
	}

private:

	std::shared_ptr<UIBox> m_debugWindow;

	std::shared_ptr<UIText> m_textPlayerPos;
	std::shared_ptr<UIText> m_textFPS;
	std::shared_ptr<UIText> m_textTickRate;
	std::shared_ptr<UIText> m_textEventCount;
	std::shared_ptr<UIText> m_textActorCount;
	std::shared_ptr<UIText> m_textObjectCount;

	bool m_enabled = true;
};

