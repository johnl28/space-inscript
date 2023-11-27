#include "UserInterface.h"

void UI::Initialise(float x, float y, int width, int height)
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
	for (auto it = m_elements.begin(); it != m_elements.end();)
	{
		it++;

		auto element = it->second;
		if (element->IsDestroyed())
		{
			DeleteElement(element);
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


bool UI::DeleteElement(std::shared_ptr<UIElement> element)
{
	auto it = m_elements.find(element->GetID());
	if (it == m_elements.end())
	{
		return false;
	}

	m_elements.erase(it);
	return true;
}



UIVerticalLine* UI::CreateVerticalLine(float x, float y, int height)
{
	auto verLineElement = std::make_shared<UIVerticalLine>(x, y, height);
	AddElement(verLineElement);

	return verLineElement.get();
}

UIHorizontalLine* UI::CreateHorizontalLine(float x, float y, int width)
{
	auto horLineElement = std::make_shared<UIHorizontalLine>(x, y, width);
	AddElement(horLineElement);

	return horLineElement.get();
}


UIText* UI::CreateText(float x, float y, std::string text)
{
	auto textElement = std::make_shared<UIText>(x, y, text);
	AddElement(textElement);

	return textElement.get();
}

UIOptionText* UI::CreateOptionText(float x, float y, std::string label)
{
	auto textElement = std::make_shared<UIOptionText>(x, y, label);
	AddElement(textElement);

	return textElement.get();
}

UIBox* UI::CreateBox(float x, float y, int width, int height)
{
	auto boxElement = std::make_shared<UIBox>(x, y, width, height);
	AddElement(boxElement);

	return boxElement.get();
}

void UI::AddElement(std::shared_ptr<UIElement> element)
{
	static int id = 0;
	++id;

	element->SetID(id);
	m_elements[id] = element;
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
