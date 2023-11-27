#include "Core.h"
#include "UIMenuWindow.h"
#include "LevelManager.h"

void UIMenuWindow::Initialise()
{
	auto ui = UI::GetInstance();

	m_window->SetFill(true);

	auto menuText = ui->CreateText(0, 1, "   Main Menu  ");
	m_window->AddChild(menuText);
	menuText->SetHorizontalAlignCentered(true);

	auto startText = ui->CreateOptionText(0, 3, " Start ");
	m_window->AddChild(startText);
	startText->SetHorizontalAlignCentered(true);
	startText->Select();

	auto exitText = ui->CreateOptionText(0, 4, " Exit ");
	m_window->AddChild(exitText);
	exitText->SetHorizontalAlignCentered(true);

	m_exitText = std::shared_ptr<UIOptionText>(exitText);
	m_startText = std::shared_ptr<UIOptionText>(startText);

	InitialiseInstructions();
}

void UIMenuWindow::InitialiseInstructions()
{
	auto ui = UI::GetInstance();

	auto instructionsWindow = ui->CreateBox(1.0f, 6.0f, m_window->GetWidth(), 5);
	//instructionsWindow->SetFill(true);
	m_window->AddChild(instructionsWindow);

	auto coinText = ui->CreateOptionText(0, 0, std::format("   Collect the coins: {}   ", COIN_CHAR));
	instructionsWindow->AddChild(coinText);
	coinText->SetHorizontalAlignCentered(true);

	auto enemyText = ui->CreateOptionText(0, 1, std::format("  Avoid the asteroids: {}  ", ENEMY_CHAR));
	instructionsWindow->AddChild(enemyText);
	enemyText->SetHorizontalAlignCentered(true);
}

void UIMenuWindow::Update()
{
	if (!IsVisible())
	{
		return;
	}

	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_selectedOption = MainMenuOption::START;
		m_startText->Select();
		m_exitText->Deselect();
	}
	else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_selectedOption = MainMenuOption::EXIT;
		m_exitText->Select();
		m_startText->Deselect();
	}
	else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		ExecuteSelection();
		Sleep(60); // use a different approach
	}
}

void UIMenuWindow::ExecuteSelection()
{
	switch (m_selectedOption)
	{
	case MainMenuOption::START:
		LevelManager::GetInstance()->StartGame();
		break;

	case MainMenuOption::EXIT:
		exit(0);
		break;
	}
}

