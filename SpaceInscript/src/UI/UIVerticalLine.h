#pragma once
#include "UIElement.h"

class UIVerticalLine: public UIElement
{
public:
	UIVerticalLine(int x, int y, int height) : UIElement(x, y), m_height(height)
	{
		SetType(UIElementType::ELEMENT_VERTICAL_LINE);
	}

	int GetHeight() const
	{
		return m_height;
	}

	const std::string& GetSymbol() const
	{
		return symbol;
	}

private:
	std::string symbol = &WINDOW_FRAME_CHAR;

	int m_height = 0;
};

