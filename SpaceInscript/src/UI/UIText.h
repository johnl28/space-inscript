#pragma once
#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(int x, int y, std::string text) : UIElement(x, y), m_text(text)
	{
		SetType(UIElementType::ELEMENT_TEXT);
	}

	void SetText(std::string text)
	{
		m_text = text;
	}

	const std::string& GetText() const
	{
		return m_text;
	}

private:
	std::string m_text = "";
};

