#pragma once
#include "Controller.h"
#include "Core.h"
#include "GameView.h"
#include "Entity/Actor.h"

class PlayerController: public Controller
{
public:
	PlayerController(std::shared_ptr<Actor> actor) : Controller(actor) {}

	void Update() override
	{
 
		int x = GameView::GetInstance()->GetWidth() - m_actor->GetX();
		int y = GameView::GetInstance()->GetHeight() - m_actor->GetY();


		if (GetAsyncKeyState('W') & 0x8000 && y != GameView::GetInstance()->GetHeight())
		{
			m_actor->MoveUp();
		}
		if (GetAsyncKeyState('S') & 0x8000 && y > 1)
		{
			m_actor->MoveDown();
		}
		if (GetAsyncKeyState('A') & 0x8000 && x != GameView::GetInstance()->GetWidth())
		{
			m_actor->MoveLeft();
		}
		if (GetAsyncKeyState('D') & 0x8000 && x > 1)
		{
			m_actor->MoveRight();
		}

#if _DEBUG
		if (GetAsyncKeyState('R') & 0x8000)
		{
			m_actor->SetXY(0, 0);
		}
#endif
	}
};

