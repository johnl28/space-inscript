#pragma once
#include "Core.h"
#include "UIWindow.h"

class UIGameWindow: public UIWindow
{
public:
	UIGameWindow(float x, float y, int width, int height) : UIWindow(x, y, width, height)
	{

	}


	void Initialise() override;
	void CreateGameOverWindow();
	void Update();
	void Reset();
	void SetScore(int score);
	void SetDifficulty(int difficulty);

	void ShowGameOver();

private:
	std::shared_ptr<UIText> m_scoreText;
	std::shared_ptr<UIText> m_difficultyText;


	std::shared_ptr<UIBox> m_gameOverWindow;
};

