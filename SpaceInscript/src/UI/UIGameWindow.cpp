#include "UIGameWindow.h"
#include "UserInterface.h"

void UIGameWindow::Initialise()
{
	auto ui = UI::GetInstance();

	auto headLine = ui->CreateHorizontalLine(0, 0, m_window->GetWidth());
	m_window->AddChild(headLine);

	auto scoreText = ui->CreateText(1, 2, "Score: 0");
	m_window->AddChild(scoreText);
	scoreText->SetHorizontalAlignCentered(true);

	auto difficultyText = ui->CreateText(1, 3, "Level: 1");
	m_window->AddChild(difficultyText);
	difficultyText->SetHorizontalAlignCentered(true);


	m_difficultyText = std::shared_ptr<UIText>(difficultyText);
	m_scoreText = std::shared_ptr<UIText>(scoreText);

	CreateGameOverWindow();
}

void UIGameWindow::CreateGameOverWindow()
{
	auto ui = UI::GetInstance();


	auto gameOverWindow = ui->CreateBox(50.0f, 5.0f, 50, 4);
	gameOverWindow->SetFill(true);
	m_window->AddChild(gameOverWindow);

	auto gameOverText = ui->CreateText(0.0f, 1.0f, "   GAME OVER!   ");
	gameOverWindow->AddChild(gameOverText);
	gameOverText->SetHorizontalAlignCentered(true);

	auto restartInfo = ui->CreateText(0.0f, 2.0f, "   PRESS R TO RESTART   ");
	gameOverWindow->AddChild(restartInfo);
	restartInfo->SetHorizontalAlignCentered(true);

	gameOverWindow->SetVisible(false);
	m_gameOverWindow = std::shared_ptr<UIBox>(gameOverWindow);
}

void UIGameWindow::Update()
{
	if (!IsVisible())
	{
		return;
	}
}

void UIGameWindow::SetScore(int score)
{
	m_scoreText->SetText(std::format("Score: {}", score));
}

void UIGameWindow::SetDifficulty(int difficulty)
{
	m_difficultyText->SetText(std::format("Level: {}", difficulty));
}

void UIGameWindow::Reset()
{
	m_gameOverWindow->SetVisible(false);
}


void UIGameWindow::ShowGameOver()
{
	m_gameOverWindow->SetVisible(true);
}