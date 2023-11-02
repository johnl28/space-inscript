#pragma once
#include "Core.h"

inline void PrintToCoordinates(int x, int y, const char* format, ...)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwWritten = 0;
	COORD cursor = { x, y };
	WriteConsoleOutputCharacter(hout, format, strlen(format), cursor, &dwWritten);
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
};


