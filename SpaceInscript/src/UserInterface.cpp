#include "UserInterface.h"

void UI::Initialise(int x, int y, int width, int height)
{
	m_position = Position(x, y);

	m_width = width;
	m_height = height;

	CreateVerticalLine(0, 0, m_height);

	CreateLogoHeader();
}

void UI::CreateLogoHeader()
{
	auto window = CreateBox(1, 0, m_width - 1, 5);
	//window->SetFill(true);

	auto text = CreateText(0, 2, "Space Inscript v1.0");
	window->AddChild(text);
	text->SetHorizontalAlignCentered(true);
}

void UI::Render()
{
	DrawElements();
}

void UI::DrawElements()
{
	for (auto& it : m_elements)
	{
		auto element = it.second;
		if (element->IsDestroyed())
		{
			DeleteElement(element.get());
			continue;
		}


		DrawElement(element.get());
	}
}

void UI::DrawElement(UIElement* element)
{
	if (!element->IsVisible())
	{
		return;
	}

	switch (element->GetType())
	{
	case UIElementType::ELEMENT_VERTICAL_LINE:
		DrawVerticalLineElement(element);
		break;

	case UIElementType::ELEMENT_HORIZONTAL_LINE:
		DrawHorizontalLineElement(element);
		break;

	case UIElementType::ELEMENT_TEXT:
		DrawTextElement(element);
		break;

	case UIElementType::ELEMENT_BOX:
		DrawBoxElement(element);
		break;

	default:
		break;
	}
}


bool UI::DeleteElement(UIElement* element)
{
	auto it = m_elements.find(element->GetID());
	if (it == m_elements.end())
	{
		return false;
	}

	m_elements.erase(it);
	return true;
}



UIVerticalLine* UI::CreateVerticalLine(int x, int y, int height)
{
	UIVerticalLine* verLineElement = new UIVerticalLine(x, y, height);
	AddElement(verLineElement);

	return verLineElement;
}

UIHorizontalLine* UI::CreateHorizontalLine(int x, int y, int width)
{
	UIHorizontalLine* horLineElement = new UIHorizontalLine(x, y, width);
	AddElement(horLineElement);

	return horLineElement;
}


UIText* UI::CreateText(int x, int y, std::string text)
{
	UIText* textElement = new UIText(x, y, text);
	AddElement(textElement);

	return textElement;
}

UIOptionText* UI::CreateOptionText(int x, int y, std::string label)
{
	UIOptionText* textElement = new UIOptionText(x, y, label);
	AddElement(textElement);

	return textElement;
}

UIBox* UI::CreateBox(int x, int y, int width, int height)
{
	UIBox* boxElement = new UIBox(x, y, width, height);
	AddElement(boxElement);

	return boxElement;
}

void UI::AddElement(UIElement *element)
{
	static int id = 0;
	++id;

	element->SetID(id);
	m_elements[id] = std::shared_ptr<UIElement>(element);
}


void UI::DrawVerticalLineElement(UIElement *element)
{
	UIVerticalLine* verLine = dynamic_cast<UIVerticalLine*>(element);
	if (!verLine)
	{
		return;
	}

	Position screenPos = verLine->GetGlobalPos();
	LocalPosToScreenPos(&screenPos);

	for (int y = 0; y < verLine->GetHeight(); ++y)
	{
		Renderer::GetInstance()->DrawPixel(screenPos.x, y + screenPos.y, *verLine->GetSymbol().c_str());
	}
}

void UI::DrawHorizontalLineElement(UIElement* element)
{
	UIHorizontalLine* horLine = dynamic_cast<UIHorizontalLine*>(element);
	if (!horLine)
	{
		return;
	}

	Position screenPos = horLine->GetGlobalPos();
	LocalPosToScreenPos(&screenPos);

	for (int x = 0; x < horLine->GetWidth(); ++x)
	{
		Renderer::GetInstance()->DrawPixel(screenPos.x + x, screenPos.y, *horLine->GetSymbol().c_str());
	}
}


void UI::DrawTextElement(UIElement* element)
{
	UIText* textElement = dynamic_cast<UIText*>(element);
	if (!textElement)
	{
		return;
	}

	Position screenPos = textElement->GetGlobalPos();
	LocalPosToScreenPos(&screenPos);

	const auto text = textElement->GetText();

	for (int x = 0; x < text.size(); ++x)
	{
		Renderer::GetInstance()->DrawPixel(screenPos.x + x, screenPos.y, text[x]);
	}
}


void UI::DrawBoxElement(UIElement* element)
{
	UIBox* boxElement = dynamic_cast<UIBox*>(element);
	if (!boxElement)
	{
		return;
	}

	if (!boxElement->IsFilled())
	{
		return;
	}

	Position screenPos = boxElement->GetGlobalPos();
	LocalPosToScreenPos(&screenPos);

	for (int y = 0; y < boxElement->GetHeight(); ++y)
	{
		for (int x = 0; x < boxElement->GetWidth(); ++x)
		{
			Renderer::GetInstance()->DrawPixel(screenPos.x + x, screenPos.y + y, *boxElement->GetSymbol().c_str());
		}
	}
}
