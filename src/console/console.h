#pragma once

#include "framebuffer.h"

class Console
{
public:
    ~Console() {}

static Console GetConsole();

    void PutChar(char character);
    void PutChar(char character, int x, int y);
    void WriteString(const char* data);
    int GetCursor() { return m_nCursor; }
    void SetCursor(int location);
    void SetCursor(int x, int y);
    void SetColorFG(char color);
    char GetColorFG(void);
    void SetColorBG(char color);
    char GetColorBG(void);


private:
    Console() { m_nCursor = m_nColor = 0; }

    int _2d_to_linear(int x, int y, int height);

    Framebuffer m_cFramebuffer;
    int m_nCursor;
    char m_nColor;
};
