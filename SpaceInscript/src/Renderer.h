#pragma once
#include "Singleton.h"
#include "Core.h"
#include "Entity/GameObject.h"


inline void PrintString(int x, int y, const std::string* format);

typedef char ScreenPixel;

class Viewport
{
public:
	virtual void Update() = 0;

	virtual void Initialise(int x, int y, int width, int height)
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
	void Draw();

	void DrawPixel(int x, int y, ScreenPixel pixel);


private:
	void GenerateScreenOutline();
	void ClearBuffer();
	void InitBuffers();
	void RenderFrame();

private:
	int m_width = 0;
	int m_height = 0;

	ScreenPixel* m_buffer;
};


