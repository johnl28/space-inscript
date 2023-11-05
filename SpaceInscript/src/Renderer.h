#pragma once
#include <iostream>

#include "Core.h"
#include "Entity.h"


inline void PrintToCoordinates(int x, int y, const char* format, ...)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwWritten = 0;
	COORD cursor = { static_cast<short>(x), static_cast<short>(y) };
	WriteConsoleOutputCharacterA(hout, static_cast<LPCSTR>(format), strlen(format), cursor, &dwWritten);
}

class Renderer
{
public:
	Renderer(int width, int height);

	void OnUpdate();

private:
	void DrawWindow();

private:
	int m_width;
	int m_height;

	std::vector<char> m_buffer;
};


