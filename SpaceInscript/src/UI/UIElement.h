#pragma once
#include "Core.h"

enum class UIElementType
{
	ELEMENT_BASE,
	ELEMENT_BOX,
	ELEMENT_TEXT,
	ELEMENT_VERTICAL_LINE,
	ELEMENT_HORIZONTAL_LINE
};


class UIElement
{
public:
	UIElement() {}

	UIElement(int x = 0, int y = 0, std::shared_ptr<UIElement> parent = nullptr)
	{
		m_parent = parent;
		m_position.x = x;
		m_position.y = y;
	}


	void SetID(int id)
	{
		m_id = id;
	}

	int GetID() const
	{
		return m_id;
	}

	void SetYX(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void SetX(int x)
	{
		m_position.x = x;
	}

	void SetY(int y)
	{
		m_position.y = y;
	}

	const Position& GetPosition() const
	{
		return m_position;
	}


	void SetParent(UIElement* parent)
	{
		m_parent = std::shared_ptr<UIElement>(parent);
	}

	UIElement* GetParent()
	{
		return m_parent.get();
	}

	virtual Position GetGlobalPos() const
	{
		if (!m_parent)
		{
			return m_position;
		}

		Position globalPosition = {
			m_parent->GetGlobalPos().x + m_position.x,
			m_parent->GetGlobalPos().y + m_position.y
		};

		return globalPosition;
	}

	bool IsType(UIElementType type) const
	{
		return m_type == type;
	}

	UIElementType GetType() const
	{
		return m_type;
	}

	bool IsVisible() const
	{
		return m_visible;
	}

	void SetVisible(bool visible)
	{
		m_visible = visible;
	}

	// When called, it will be marked as destroyed and deleted in the next frame
	void Destroy()
	{
		m_destroyed = true;
	}

	bool IsDestroyed() const
	{
		return m_destroyed;
	}


protected:
	void SetType(UIElementType type)
	{
		m_type = type;
	}

private:
	int m_id = 0;

	bool m_visible = true;
	bool m_destroyed = false;

	std::shared_ptr<UIElement> m_parent = nullptr;
	UIElementType m_type = UIElementType::ELEMENT_BASE;

	Position m_position = { 0, 0 };
};

