#pragma once
#include "UIWindow.h"

enum class MainMenuOption 
{
	START,
	EXIT,
	MAX_OPTION
};

class UIMenuWindow: public UIWindow
{
public:
	UIMenuWindow(float x, float y, int width, int height) : UIWindow(x, y, width, height)
	{

	}

	void Initialise() override;
	void InitialiseInstructions();
	void Update();

private:
	void ExecuteSelection();

private:

	MainMenuOption m_selectedOption = MainMenuOption::START;
	std::shared_ptr<UIOptionText> m_startText;
	std::shared_ptr<UIOptionText> m_exitText;
};

