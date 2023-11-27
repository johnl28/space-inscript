#pragma once
#include "Core.h"
#include "Singleton.h"

//#define DOUBLE_BUFFER_RENDERING

inline void PrintString(int x, int y, const std::string* format);

inline void ClearScreen(int width, int height)
{
	static auto hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hout) {
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	COORD cursorPosition = { 0, 0 };
	DWORD charsWritten;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);

	FillConsoleOutputCharacter(hout, ' ', csbi.dwSize.X * csbi.dwSize.Y, cursorPosition, &charsWritten);

	SetConsoleCursorPosition(hout, cursorPosition);
}

typedef char ScreenPixel;

class Viewport
{
public:
	virtual void Render() = 0;

	virtual void Initialise(float x, float y, int width, int height)
	{
		m_position = { x, y };

		m_width = width;
		m_height = height;
	}

	void LocalPosToScreenPos(Position* pos) const
	{
		pos->x += m_position.x;
		pos->y += m_position.y;
	}

	int GetWidth() const
	{
		return m_width;
	}

	int GetHeight() const
	{
		return m_height;
	}

protected:
	Position m_position;
	int m_width = 0;
	int m_height = 0;
};


class Renderer: public Singleton<Renderer>
{
public:
	void Initialise(int width, int height);
	void Destroy();
	void Draw();

	void DrawPixel(float x, float y, ScreenPixel pixel);


private:
	void GenerateScreenOutline();
	void ClearBuffer();
	void InitBuffers();
	void RenderFrame();

#ifdef DOUBLE_BUFFER_RENDERING
	void SwapBuffer();
#endif

private:
	int m_width = 0;
	int m_height = 0;

	ScreenPixel* m_buffer;
#ifdef DOUBLE_BUFFER_RENDERING
	ScreenPixel* m_backBuffer;
	ScreenPixel* m_frontBuffer;
#endif

};


