#pragma once
#include "UIText.h"

class UIOptionText : public UIText
{
public:
	UIOptionText(int x, int y, std::string label) : UIText(x, y, label), m_label(label)
	{

	}

	void SetLabel(std::string label)
	{
		m_label = label;
		UpdateText();
	}

	void UpdateText()
	{
		if (m_selected) 
		{
			SetText(std::format(">> {} <<", m_label));
		}
		else
		{
			SetText(m_label);
		}
	}

	void Select()
	{
		m_selected = true;
		UpdateText();
	}

	void Deselect()
	{
		m_selected = false;
		UpdateText();
	}

	bool IsSelected() const
	{
		return m_selected;
	}

private:
	std::string m_label;
	bool m_selected = false;
};
