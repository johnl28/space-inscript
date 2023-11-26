#include "Renderer.h"


void Renderer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	InitBuffers();
}

void Renderer::Destroy()
{
#ifdef DOUBLE_BUFFER_RENDERING
	delete m_backBuffer;
#endif

	delete m_buffer;
}

void Renderer::Draw()
{
#ifdef DOUBLE_BUFFER_RENDERING
	SwapBuffer();
#endif
	RenderFrame();
	ClearBuffer();
}

#ifdef DOUBLE_BUFFER_RENDERING
void Renderer::SwapBuffer()
{
	std::swap(m_frontBuffer, m_backBuffer);
}
#endif

void Renderer::InitBuffers()
{
	const size_t size = m_width * m_height;

#ifdef DOUBLE_BUFFER_RENDERING
	m_backBuffer = new ScreenPixel[size];
	m_frontBuffer = new ScreenPixel[size];

	memset(m_backBuffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * size);
	memset(m_frontBuffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * size);
	m_buffer = m_frontBuffer;
#else
	m_buffer = new ScreenPixel[size];
	memset(m_buffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * size);
#endif

}

void Renderer::GenerateScreenOutline()
{
#ifdef DOUBLE_BUFFER_RENDERING
	auto buffer = m_backBuffer;
#else
	auto buffer = m_buffer;
#endif


	// Horizontal lines
	memset(buffer, WINDOW_FRAME_CHAR, sizeof(ScreenPixel) * m_width);
	memset(&buffer[m_width * (m_height - 1)], WINDOW_FRAME_CHAR, sizeof(ScreenPixel) * m_width);


	// Vertical Lines
	for (int y = 1; y < m_height - 1; ++y)
	{
		buffer[y * m_width] = WINDOW_FRAME_CHAR;
	
		buffer[y * m_width + m_width - 1] = WINDOW_FRAME_CHAR;
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
#ifdef DOUBLE_BUFFER_RENDERING
	memset(m_backBuffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * m_width * m_height);
#else
	memset(m_buffer, DEFAULT_OBJECT_CHAR, sizeof(ScreenPixel) * m_width * m_height);
#endif

	GenerateScreenOutline();
}

void Renderer::DrawPixel(int x, int y, ScreenPixel pixel)
{
	int index = y * m_width + x;

	if (index < 0 || index >= m_width * m_height)
	{
		return;
	}

#ifdef DOUBLE_BUFFER_RENDERING
	m_backBuffer[index] = pixel;
#else
	m_buffer[index] = pixel;
#endif
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