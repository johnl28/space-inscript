#pragma once
#include "Utils.h"
#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(float x, float y, std::string text) : UIElement(x, y), m_text(text)
	{
		SetType(UIElementType::ELEMENT_TEXT);
	}

	void SetText(std::string text)
	{
		m_text = text;

		if (m_alignHorizontalCentered)
		{
			AlignHorizontalCentered();
		}
	}

	const std::string& GetText() const
	{
		return m_text;
	}

	int GetWidth() override
	{
		return static_cast<int>(m_text.size());
	}

	int GetHeight() override
	{
		return 1;
	}

	void AlignHorizontalCentered()
	{
		auto parentWidth = m_parent ? m_parent->GetWidth() : 1;

		m_position.x = to_float(parentWidth / 2 - GetWidth() / 2);
	}

	void SetHorizontalAlignCentered(bool isCentered)
	{
		m_alignHorizontalCentered = isCentered;
		if (isCentered)
		{
			AlignHorizontalCentered();
		}
	}

private:
	std::string m_text = "";
	bool m_alignHorizontalCentered = false;
};

