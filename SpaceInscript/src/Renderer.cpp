#include "Renderer.h"

Renderer::Renderer(int width, int height) : 
	m_width(width),
	m_height(height)
{

}

void Renderer::OnUpdate()
{
	DrawWindow();

	Entity entity('@');
	entity.SetXY(2, 3);

	RenderEntity(&entity);
}

void Renderer::RenderEntity(Entity* entity)
{
	Position pos = entity->GetPosition();
	PrintToCoordinates(pos.x, pos.y, entity->GetSymbol());
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

	PrintToCoordinates(20, 5, "@");
}
