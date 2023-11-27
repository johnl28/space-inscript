#include "UIPauseMenu.h"

#include "UserInterface.h"
#include "LevelManager.h"


void UIPauseMenu::Initialise()
{
	auto ui = UI::GetInstance();
	m_window->SetFill(true);

	auto titleText = ui->CreateText(1.0f, 1.0f, "   PAUSE   ");
	m_window->AddChild(titleText);
	titleText->SetHorizontalAlignCentered(true);


	auto resumeOption = ui->CreateOptionText(1.0f, 3.0f, "Resume");
	m_window->AddChild(resumeOption);
	resumeOption->SetHorizontalAlignCentered(true);
	resumeOption->Select();

	auto restartOption = ui->CreateOptionText(1.0f, 4.0f, "Restart");
	m_window->AddChild(restartOption);
	restartOption->SetHorizontalAlignCentered(true);

	auto mainMenuOption = ui->CreateOptionText(1.0f, 5.0f, "Main Menu");
	m_window->AddChild(mainMenuOption);
	mainMenuOption->SetHorizontalAlignCentered(true);


	m_optionsMap[PAUSE_OPTION_RESUME] = resumeOption;
	m_optionsMap[PAUSE_OPTION_RESTART] = restartOption;
	m_optionsMap[PAUSE_OPTION_EXIT_MAIN_MENU] = mainMenuOption;

}

void UIPauseMenu::Update()
{
	if (!IsVisible())
	{
		return;
	}

	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_optionsMap[static_cast<PauseMenuOption>(m_selectedOption)]->Deselect();

		--m_selectedOption;

		if (m_selectedOption < 0)
		{
			m_selectedOption = PAUSE_OPTION_MAX - 1;
		}

		m_optionsMap[static_cast<PauseMenuOption>(m_selectedOption)]->Select();
		Sleep(60); // use a different approach
	}
	else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_optionsMap[static_cast<PauseMenuOption>(m_selectedOption)]->Deselect();

		++m_selectedOption;

		if (m_selectedOption >= PAUSE_OPTION_MAX)
		{
			m_selectedOption = 0;
		}

		m_optionsMap[static_cast<PauseMenuOption>(m_selectedOption)]->Select();
		Sleep(60); // use a different approach
	}
	else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		ExecuteSelection();
		Sleep(60); // use a different approach
	}
}

void UIPauseMenu::ExecuteSelection()
{
	switch (m_selectedOption)
	{
	case PAUSE_OPTION_RESUME:
	{
		LevelManager::GetInstance()->TogglePauseGame();
		break;
	}

	case PAUSE_OPTION_RESTART:
	{
		Hide();
		LevelManager::GetInstance()->StartGame();
		break;
	}


	case PAUSE_OPTION_EXIT_MAIN_MENU:
	{
		LevelManager::GetInstance()->ExitToMainMenu();
		break;
	}

	default:
		break;
	}
}
