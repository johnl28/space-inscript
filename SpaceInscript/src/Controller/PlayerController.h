#pragma once
#include "Core.h"
#include "Controller.h"
#include "GameView.h"
#include "Entity/Player.h"


class PlayerController: public Controller
{
public:
	PlayerController(std::shared_ptr<Player> player)
	{
		m_player = player;
	}

	void Update() override
	{
		if (m_player->IsDead())
		{
			return;
		}
		
		int x = GameView::GetInstance()->GetWidth() - to_int(m_player->GetX());
		int y = GameView::GetInstance()->GetHeight() - to_int(m_player->GetY());


		if (GetAsyncKeyState('W') & 0x8000 && y != GameView::GetInstance()->GetHeight())
		{
			m_player->MoveUp();
		}
		if (GetAsyncKeyState('S') & 0x8000 && y > 1)
		{
			m_player->MoveDown();
		}
		if (GetAsyncKeyState('A') & 0x8000 && x != GameView::GetInstance()->GetWidth())
		{
			m_player->MoveLeft();
		}
		if (GetAsyncKeyState('D') & 0x8000 && x > 1)
		{
			m_player->MoveRight();
		}

#if _DEBUG
		if (GetAsyncKeyState('E') & 0x8000)
		{
			m_player->SetXY(0, 0);
		}
#endif
	}

private:
	std::shared_ptr<Player> m_player;
};

