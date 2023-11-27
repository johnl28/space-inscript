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
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;

	UIElement() {}

	UIElement(float x = 0, float y = 0, UIElement* parent = nullptr)
	{
		m_position = { x, y };
		m_parent = parent;
	}


	void SetID(int id)
	{
		m_id = id;
	}

	int GetID() const
	{
		return m_id;
	}

	void SetYX(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void SetX(float x)
	{
		m_position.x = x;
	}

	void SetY(float y)
	{
		m_position.y = y;
	}

	const Position& GetPosition() const
	{
		return m_position;
	}


	void SetParent(UIElement* parent)
	{
		m_parent = parent;
	}

	UIElement* GetParent()
	{
		return m_parent;
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
		if (m_parent && !m_parent->IsVisible()) 
		{
			return false;
		}

		return m_visible;
	}

	void SetVisible(bool visible)
	{
		m_visible = visible;
	}


	// When called, it will be marked as destroyed and deleted in the next frame
	virtual void Destroy()
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

protected:
	int m_id = 0;

	bool m_visible = true;
	bool m_destroyed = false;

	int m_width = 0;
	int m_height = 0;

	UIElement *m_parent = nullptr;
	UIElementType m_type = UIElementType::ELEMENT_BASE;

	Position m_position = { 0, 0 };
};

