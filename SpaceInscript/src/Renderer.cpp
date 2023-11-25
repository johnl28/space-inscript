#include "Renderer.h"


void Renderer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	InitBuffers();
}

void Renderer::Draw()
{
	RenderFrame();
	ClearBuffer();
}

void Renderer::InitBuffers()
{
	const size_t size = m_width * m_height;

	m_buffer = new ScreenPixel[size];

	memset(m_buffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * size);
}

void Renderer::GenerateScreenOutline()
{
	// Horizontal lines
	memset(m_buffer, WINDOW_FRAME_CHAR, sizeof(ScreenPixel) * m_width);
	memset(&m_buffer[m_width * (m_height - 1)], WINDOW_FRAME_CHAR, sizeof(ScreenPixel) * m_width);


	// Vertical Lines
	for (int y = 1; y < m_height - 1; ++y)
	{
		m_buffer[y * m_width] = WINDOW_FRAME_CHAR;
	
		m_buffer[y * m_width + m_width - 1] = WINDOW_FRAME_CHAR;
	}
}

void Renderer::RenderFrame()
{
	auto firstPixelRow = m_buffer;
	auto nextPixelRow = m_buffer + m_width;

	// todo: test parallel loop execution
	// #pragma omp for
	for (int y = 0; y < m_height; ++y)
	{
		std::string pixelsString(firstPixelRow, nextPixelRow);

		PrintString(0, y, &pixelsString);

		// Move the pointer 
		firstPixelRow += m_width;
		nextPixelRow += m_width;
	}
}


void Renderer::ClearBuffer()
{
	memset(m_buffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * m_width * m_height);

	GenerateScreenOutline();
}

void Renderer::DrawPixel(int x, int y, ScreenPixel pixel)
{
	int index = y * m_width + x;

	if (index < 0 || index >= m_width * m_height)
	{
		return;
	}

	m_buffer[index] = pixel;
}


inline void PrintString(int x, int y, const std::string* format)
{

	static HANDLE hout = nullptr;
	if (!hout) {
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	DWORD dwWritten = 0;
	const DWORD size = static_cast<DWORD>(format->size());

	const COORD cursor = { 
		static_cast<short>(x), 
		static_cast<short>(y) 
	};


	WriteConsoleOutputCharacterA(hout, format->c_str(), size, cursor, &dwWritten);
}


#if 0
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

inline void ClearScreen(int width, int height)
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
#endif