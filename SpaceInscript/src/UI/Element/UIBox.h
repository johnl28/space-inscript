#pragma once
#include "Core.h"
#include "UIElement.h"

class UIBox: public UIElement
{

public:
	UIBox(float x, float y, int width, int height) : UIElement(x, y), m_width(width), m_height(height)
	{
		SetType(UIElementType::ELEMENT_BOX);
	}

	int GetWidth() override
	{
		return m_width;
	}

	int GetHeight() override
	{
		int size = m_height;

		if (m_fitChildren) 
		{
			size = static_cast<int>(m_children.size());
		}

		return size;
	}

	bool IsFilled() const
	{
		return m_fill;
	}

	void SetFill(bool isFilled)
	{
		m_fill = isFilled;
	}

	const std::string &GetSymbol() const
	{
		return m_symbol;
	}

	void SetBorderd(bool bordered) 
	{
		m_bordered = bordered;
	}

	bool IsBordered() const
	{
		return m_bordered;
	}

	void SetFitChildren(bool fitChildren)
	{
		m_fitChildren = fitChildren;
	}

	bool FitChildren() const
	{
		return m_fitChildren;
	}


	bool AddChild(std::shared_ptr<UIElement> element)
	{
		auto it = m_children.find(element->GetID());
		if (it != m_children.end())
		{
			return false;
		}

		element->SetParent(this);
		m_children[element->GetID()] = element;
		return true;
	}

	bool RemoveChild(std::shared_ptr<UIElement> element)
	{
		auto it = m_children.find(element->GetID());
		if (it == m_children.end())
		{
			return false;
		}

		m_children.erase(it);
		return true;
	}

	void Destroy() override
	{
		for (auto it : m_children)
		{
			it.second->Destroy();
		}
		m_destroyed = true;
		
	}


private:
	std::map<int, std::shared_ptr<UIElement>> m_children;

	bool m_bordered = false;
	bool m_fill = false;
	bool m_fitChildren = false;

	std::string m_symbol = &WINDOW_FRAME_CHAR;


	int m_width = 0;
	int m_height = 0;
};

