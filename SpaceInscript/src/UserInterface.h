#pragma once
#include "Core.h"
#include "Singleton.h"

#include "Renderer.h"

#include "UI/Element/UIElement.h"
#include "UI/Element/UIVerticalLine.h"
#include "UI/Element/UIHorizontalLine.h"
#include "UI/Element/UIText.h"
#include "UI/Element/UIBox.h"
#include "UI/Element/UIOptionText.h"


class UI: public Viewport, public Singleton<UI>
{
public:
	void Initialise(int x, int y, int width, int height);
	void Render();

	void CreateLogoHeader();


	UIVerticalLine* CreateVerticalLine(int x, int y, int height);
	UIHorizontalLine* CreateHorizontalLine(int x, int y, int width);
	UIText* CreateText(int x, int y, std::string text);
	UIBox* CreateBox(int x, int y, int width, int height);
	UIOptionText* CreateOptionText(int x, int y, std::string label);

private:
	void AddElement(UIElement* element);
	bool DeleteElement(UIElement* element);

	void DrawElements();
	void DrawElement(UIElement* element);

	// Draw different types of elements
	void DrawVerticalLineElement(UIElement* element);
	void DrawHorizontalLineElement(UIElement* element);

	void DrawTextElement(UIElement* element);
	void DrawBoxElement(UIElement* element);


private:
	std::map<int, std::shared_ptr<UIElement>> m_elements;
};

