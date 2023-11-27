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
	void Initialise(float x, float y, int width, int height);
	void Render();

	void CreateLogoHeader();


	UIVerticalLine* CreateVerticalLine(float x, float y, int height);
	UIHorizontalLine* CreateHorizontalLine(float x, float y, int width);
	UIText* CreateText(float x, float y, std::string text);
	UIBox* CreateBox(float x, float y, int width, int height);
	UIOptionText* CreateOptionText(float x, float y, std::string label);

private:
	void AddElement(std::shared_ptr<UIElement> element);
	bool DeleteElement(std::shared_ptr<UIElement> element);

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

