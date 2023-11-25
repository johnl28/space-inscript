#pragma once
#include "Core.h"
#include "UIElement.h"

class UIBox: public UIElement
{
public:
	UIBox(int x, int y, int width, int height) : UIElement(x, y), m_width(width), m_height(height)
	{

	}

	int GetWidth() const
	{
		int size = m_width;

		if (m_bordered)
		{
			size += 2;
		}

		return size;
	}

	int GetHeight() const
	{
		int size = m_height;

		if (m_fitChildren) 
		{
			size = static_cast<int>(m_children.size());
		}

		if (m_bordered)
		{
			size += 2;
		}

		return m_height;
	}

	void SetBorderd(bool bordered) 
	{
		m_bordered = bordered;
	}

	bool IsBordered() const
	{
		return m_bordered;
	}

	bool AddChild(std::shared_ptr<UIElement> element)
	{
		auto it = m_children.find(element->GetID());
		if (it == m_children.end())
		{
			return false;
		}

		m_children[element->GetID()] = element;
	}

	bool RemoveChild(UIElement* element)
	{
		auto it = m_children.find(element->GetID());
		if (it == m_children.end())
		{
			return false;
		}

		m_children.erase(it);
		return true;
	}


private:
	std::map<int, std::shared_ptr<UIElement>> m_children;

	bool m_bordered = false;
	bool m_fitChildren = false;

	std::string m_borderSymbol = &WINDOW_FRAME_CHAR;

	int m_width = 0;
	int m_height = 0;
};

