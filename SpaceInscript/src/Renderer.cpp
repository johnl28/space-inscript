#include "Renderer.h"
#include "Player.h"



void Renderer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Renderer::Update()
{
	ClearConsole();
	this->DrawWindowFrame();
	this->RenderGameObjects();
}

bool Renderer::AddGameObject(std::shared_ptr<GameObject> object)
{
	if (m_objects.find(object->GetID()) != m_objects.end()) {
		return false;
	}

	m_objects.emplace(object->GetID(), object);
	return true;
}

bool Renderer::DeleteGameObject(std::shared_ptr<GameObject> object)
{
	auto it = m_objects.find(object->GetID());
	if (it == m_objects.end()) {
		return false;
	}

	m_objects.erase(it);
	return true;
}

void Renderer::RenderGameObjects()
{
	for (auto pair : m_objects)
	{
		auto object = pair.second;
		this->RenderGameObject(object.get());
	}
}

void Renderer::RenderGameObject(const GameObject* object)
{
	if (!object->IsVisible() || IsObjectClipped(object))
	{
		return;
	}

	const Position pos = object->GetPosition();
	PrintToCoordinates(pos.x, pos.y, object->GetSymbol()->c_str());
}

bool Renderer::IsObjectClipped(const GameObject* object)
{
	const Position pos = object->GetPosition();
	if (pos.x >= m_width || pos.x <= 0 || pos.y >= m_height || pos.y <= 0)
	{
		return true;
	}

	return false;
}

void Renderer::DrawWindowFrame()
{

	for (int y = 1; y < m_height; ++y)
	{
		PrintToCoordinates(0, y, &WINDOW_FRAME_CHAR);
		PrintToCoordinates(m_width, y, &WINDOW_FRAME_CHAR);
	}

	for (int x = 0; x < m_width + 1; ++x)
	{
		PrintToCoordinates(x, 0, &WINDOW_FRAME_CHAR);
		PrintToCoordinates(x, m_height, &WINDOW_FRAME_CHAR);
	}
}


inline void PrintToCoordinates(int x, int y, const char* format, ...)
{
	if (!hout) {
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	char buffer[1024];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DWORD dwWritten = 0;
	COORD cursor = { static_cast<short>(x), static_cast<short>(y) };
	WriteConsoleOutputCharacterA(hout, buffer, static_cast<DWORD>(strlen(buffer)), cursor, &dwWritten);
}

inline void ClearConsole()
{
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
