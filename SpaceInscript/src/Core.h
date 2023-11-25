#pragma once

#include <Windows.h>
#include <vector>
#include <map>
#include <memory>
#include <string>



#define MAX_TPS 60 // Max Game Ticks/Loops per second


constexpr char DEFAULT_OBJECT_CHAR = char(32);
constexpr char WINDOW_FRAME_CHAR = char(219);


constexpr char PLAYER_CHAR = '@';
constexpr const char* ENEMY_CHAR = "<<<";


struct Position
{
	int x;
	int y;

	Position(int X = 0, int Y = 0): x(X), y(Y)
	{
	}

	Position(const Position& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	Position operator+(const Position& other) const
	{
		Position newPos;
		newPos.x = this->x + other.x;
		newPos.y = this->y + other.y;
		return newPos;
	}

	Position operator-(const Position& other) const
	{
		Position newPos;
		newPos.x = this->x - other.x;
		newPos.y = this->y - other.y;
		return newPos;
	}
};



