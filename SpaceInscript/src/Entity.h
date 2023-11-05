#pragma once

struct Position
{

	int x;
	int y;


	Position operator+(Position& other)
	{
		Position newPos;
		newPos.x = this->x + other.x;
		newPos.y = this->y + other.y;
	}

	Position operator-(Position& other)
	{
		Position newPos;
		newPos.x = this->x - other.x;
		newPos.y = this->y - other.y;
	}
};


class Entity
{

public:
	Entity(char symbol): m_symbol(symbol)
	{

	}

	const Position &GetPosition()
	{
		return m_position;
	}

	void SetPosition(const Position &newPosition)
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

private:
	Position m_position = {0, 0};
	char m_symbol;
};



