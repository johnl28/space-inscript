#pragma once
#include "UIWindow.h"

enum PauseMenuOption
{
	PAUSE_OPTION_RESUME = 0,
	PAUSE_OPTION_RESTART,
	PAUSE_OPTION_EXIT_MAIN_MENU,

	PAUSE_OPTION_MAX
};

class UIPauseMenu: public UIWindow
{
public:
	UIPauseMenu(float x, float y, int width, int height) : UIWindow(x, y, width, height)
	{

	}

	void Initialise() override;

	void ExecuteSelection();

	void Update();

private:
	int m_selectedOption = PAUSE_OPTION_RESUME;

	std::map<PauseMenuOption, std::shared_ptr<UIOptionText>> m_optionsMap;
};

