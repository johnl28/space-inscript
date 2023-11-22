#pragma once

#include <Windows.h>
#include <vector>
#include <map>
#include <memory>
#include <string>


#define MAX_TPS 60 // Max Game Ticks/Loops per second

#define SAFE_PTR(CLASS_NAME) std::shared_ptr<CLASS_NAME>

constexpr char DEFAULT_OBJECT_CHAR = ' ';
constexpr char PLAYER_CHAR = '@';
constexpr char WINDOW_FRAME_CHAR = '#';
constexpr const char* ENEMY_CHAR = "****";
constexpr char EMPTY_CELL_CHAR = ' ';


struct Position
{
	int x;
	int y;

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



