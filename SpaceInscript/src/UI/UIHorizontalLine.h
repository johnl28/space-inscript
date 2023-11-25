#pragma once
#include "UIElement.h"

class UIHorizontalLine : public UIElement
{
public:
	UIHorizontalLine(int x, int y, int width) : UIElement(x, y), m_width(width)
	{
		SetType(UIElementType::ELEMENT_HORIZONTAL_LINE);
	}


	void SetWidth(int width)
	{
		m_width = width;
	}

	int GetWidth() const
	{
		return m_width;
	}

	const std::string& GetSymbol() const
	{
		return symbol;
	}


private:
	std::string symbol = &WINDOW_FRAME_CHAR;

	int m_width = 0;
};

