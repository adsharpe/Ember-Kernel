#include "console.h"

static Console s_cConsole = nullptr;

Console Console::GetConsole()
{
    if (s_cConsole == nullptr) {
        s_cConsole = new Console();
    }

    return s_cConsole;
}

void Console::PutChar(char character)
{
}

void Console::PutChar(char character, int x, int y)
{
}

void Console::WriteString(const char* data)
{
}

void Console::SetCursor(int location)
{
    int buffer_size = m_cFramebuffer.Size();

    if (location < 0) { location = 0; }
    if (location >= buffer_size) { location = buffer_size - 1; }

    m_nCursor = location;
}

void Console::SetCursor(int x, int y)
{
    int nWidth = m_cFramebuffer.GetWidth();
    int nHeight = m_cFramebuffer.GetHeight();

    if (x < 0) { x = 0; }
    if (x >= nWidth) { x = (nWidth - 1); }
    if (y < 0) { y = 0; }
    if (y >= nHeight) { y = (nHeight - 1); }

    m_nCursor = _2d_to_linear(x, y, nHeight);
}

void Console::SetColorFG(char color)
{
    char nColor = (m_nColor & 0xF0);
    m_nColor = ((nColor) | (color & 0x0F));
}

char Console::GetColorFG(void)
{
    return (m_nColor & 0x0F);
}

void Console::SetColorBG(char color)
{
    char nColor = (m_nColor & 0x0F);
    m_nColor = ((nColor) | ((color & 0x0F) << 4));
}

char Console::GetColorBG(void)
{
    return ((m_nColor & 0xF0) >> 4);
}

int Console::_2d_to_linear(int x, int y, int height)
{
    return (height * y) + x;
}

