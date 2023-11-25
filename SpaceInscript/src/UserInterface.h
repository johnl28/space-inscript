#pragma once
#include "Core.h"
#include "Singleton.h"
#include "Renderer.h"

#include "GameCore.h"


#include "UI/UIElement.h"
#include "UI/UIVerticalLine.h"
#include "UI/UIHorizontalLine.h"
#include "UI/UIText.h"
#include "UI/UIBox.h"


class UI: public Viewport, public Singleton<UI>
{
public:
	void Initialise(int x, int y, int width, int height);
	void Update();


	//void DrawVerticalLine(int x, int y, int height);

	UIVerticalLine* CreateVerticalLine(int x, int y, int height);
	UIHorizontalLine* CreateHorizontalLine(int x, int y, int width);
	UIText* CreateText(int x, int y, std::string text);
	UIBox* CreateBox(int x, int y, int width, int height);


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
	std::shared_ptr<GameCore> m_gameCore;
};

