#pragma once

#include <Windows.h>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <format>

#include "Utils.h"

#define MAX_TPS 60 // Max Game Ticks/Loops per second
#define MAX_FPS 60


constexpr const char DEFAULT_OBJECT_CHAR = char(32);
constexpr char WINDOW_FRAME_CHAR = char(219);

constexpr const char* COIN_CHAR = "*";
constexpr const char* PLAYER_CHAR = "}=>";
constexpr const char* ENEMY_CHAR = "@";


struct Position
{
	float x;
	float y;

	Position(float X = 0, float Y = 0): x(X), y(Y)
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



