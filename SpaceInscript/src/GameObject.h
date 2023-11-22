#pragma once
#include "Core.h"


/* Base abstract class for entities that can be placed in the 2D world
* with basic functionalities for rendering.
*/
class GameObject
{
public:
	GameObject(int id, std::string symbol) : m_id(id), m_symbol(symbol) {}

	virtual void Update() = 0;

	const int& GetID() const
	{
		return m_id;
	}

	const Position& GetPosition() const
	{
		return m_position;
	}

	void SetPosition(const Position& newPosition)
	{
		m_position = newPosition;
	}

	void SetX(int x)
	{
		m_position.x = x;
	}

	void SetY(int y)
	{
		m_position.y = y;
	}

	void SetXY(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	const int& GetX() const
	{
		return m_position.x;
	}

	const int& GetY() const
	{
		return m_position.y;
	}

	const std::string* GetSymbol() const
	{
		return &m_symbol;
	}

	bool IsVisible() const
	{
		return m_visible;
	}

	void SetVisibility(bool isVisible)
	{
		m_visible = isVisible;
	}

protected:
	int m_id = 0;
	std::string m_symbol = std::string(&DEFAULT_OBJECT_CHAR);

	bool m_visible = true;

	Position m_position = { 0, 0 };
};

