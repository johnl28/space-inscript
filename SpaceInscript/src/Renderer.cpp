#include "Renderer.h"

Renderer::Renderer(int width, int height) : 
	m_width(width),
	m_height(height)
{

}

void Renderer::OnUpdate()
{
	DrawWindow();
}

void Renderer::DrawWindow()
{

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			PrintToCoordinates(x, y, "#");
		}
	}
}
