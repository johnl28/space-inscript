#pragma once
#include "Core.h"
#include "UIWindow.h"

class UIGameWindow: public UIWindow
{
public:
	UIGameWindow(int x, int y, int width, int height) : UIWindow(x, y, width, height)
	{

	}

	void Initialise() override;
	void SetScore(int score);
	void SetDifficulty(int difficulty);

private:
	std::shared_ptr<UIText> m_scoreText;
	std::shared_ptr<UIText> m_difficultyText;
	std::shared_ptr<UIText> m_lifesText;
};

