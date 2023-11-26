#pragma once
#include "UIWindow.h"

enum class MenuOption 
{
	START,
	EXIT,
	MAX_OPTION
};

class UIMenuWindow: public UIWindow
{
public:
	UIMenuWindow(int x, int y, int width, int height) : UIWindow(x, y, width, height)
	{

	}

	void Initialise() override;
	void InitialiseInstructions();
	void Update();

private:
	void ExecuteSelection();

private:

	MenuOption m_selectedOption = MenuOption::START;
	std::shared_ptr<UIOptionText> m_startText;
	std::shared_ptr<UIOptionText> m_exitText;
};

