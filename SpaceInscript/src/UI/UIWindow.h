#pragma once
#include "UserInterface.h"


class UIWindow
{
public:
	virtual void Initialise() = 0;

	UIWindow(float x, float y, int width, int height)
	{
		auto window = UI::GetInstance()->CreateBox(x, y, width, height);
		m_window = std::shared_ptr<UIBox>(window);
	}

	void SetVisible(bool isVisible)
	{
		m_window->SetVisible(isVisible);
	}

	bool IsVisible()
	{
		return m_window->IsVisible();
	}

protected:
	std::shared_ptr<UIBox> m_window;
};

