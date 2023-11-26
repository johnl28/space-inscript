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

	int GetWidth() override
	{
		return m_width;
	}

	int GetHeight() override
	{
		return 1;
	}

	const std::string& GetSymbol() const
	{
		return symbol;
	}


private:
	std::string symbol = &WINDOW_FRAME_CHAR;

	int m_width = 0;
};

