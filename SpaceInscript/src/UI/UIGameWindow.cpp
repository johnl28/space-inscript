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

	auto lifesText = ui->CreateText(1, 4, "Lives: 5");
	m_window->AddChild(lifesText);
	lifesText->SetHorizontalAlignCentered(true);

	m_difficultyText = std::shared_ptr<UIText>(difficultyText);
	m_lifesText = std::shared_ptr<UIText>(lifesText);
	m_scoreText = std::shared_ptr<UIText>(scoreText);
}

void UIGameWindow::SetScore(int score)
{
	m_scoreText->SetText(std::format("Score: {}", score));
}

void UIGameWindow::SetDifficulty(int difficulty)
{
	m_difficultyText->SetText(std::format("Level: {}", difficulty));
}

