#include <stdint.h>
#include "console.h"
#include "framebuffer.h"


Framebuffer g_cFramebuffer;
const unsigned int g_nBufferWindowSize = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * 3;
Character_t g_aBufferWindow[g_nBufferWindowSize];
unsigned int g_nCursor;
char g_nColor;

Console::Console()
{
    char nColor = (BLACK << 4) | WHITE;
    SetCursor(0);

    SetColor(nColor);
}

void Console::PutChar(char nCharacter)
{
    g_aBufferWindow[g_nCursor].uColor.nValue = g_nColor;
    g_aBufferWindow[g_nCursor].nValue = nCharacter;
    SetCursor(++g_nCursor);
}

void Console::PutChar(char nCharacter, unsigned int nX, unsigned int nY)
{
    unsigned int nLocation = _2d_to_linear(nX, nY, g_cFramebuffer.GetHeight());

    g_aBufferWindow[nLocation].uColor.nValue = g_nColor;
    g_aBufferWindow[nLocation].nValue = nCharacter;
    SetCursor(++nLocation);
}

void Console::WriteString(const char* pString)
{
}

unsigned int Console::GetCursor(void)
{
    return g_nCursor;
}

void Console::SetCursor(unsigned int nLocation)
{
    unsigned int nBufferSize = g_cFramebuffer.GetSize();

    if (nLocation < 0) { nLocation = 0; }
    if (nLocation >= nBufferSize) { nLocation = nBufferSize - 1; }

    g_nCursor = nLocation;
}

void Console::SetCursor(unsigned int nX, unsigned int nY)
{
    unsigned int nWidth = g_cFramebuffer.GetWidth();
    unsigned int nHeight = g_cFramebuffer.GetHeight();

    if (nX < 0) { nX = 0; }
    if (nX >= nWidth) {nX = (nWidth - 1); }
    if (nY < 0) { nY = 0; }
    if (nY >= nHeight) { nY = (nHeight - 1); }

    g_nCursor = _2d_to_linear(nX, nY, nHeight);
}

void Console::Clear()
{
    Clear(g_nColor);
}

void Console::Clear(unsigned char nColor)
{
    unsigned short nClearValue = ((' ' << 8) | nColor);

    if(g_nBufferWindowSize % sizeof(uint64_t) == 0) {
        uint64_t* pTempBuffer = (uint64_t*)g_aBufferWindow;
        unsigned int nEnd = g_nBufferWindowSize / sizeof(uint64_t);
        uint64_t nClearQword =
            ((uint64_t)nClearValue << 48) |
            ((uint64_t)nClearValue << 32) |
            ((uint64_t)nClearValue << 16) |
            ((uint64_t)nClearValue);

        for(unsigned int nIndex = 0; nIndex < nEnd; nIndex++) {
            pTempBuffer[nIndex] = nClearQword;
        }
        SetCursor(0);
        return;
    }

    if(g_nBufferWindowSize % sizeof(uint32_t) == 0) {
        uint32_t* pTempBuffer = (uint32_t*)g_aBufferWindow;
        unsigned int nEnd = g_nBufferWindowSize / sizeof(uint32_t);
        uint32_t nClearDword =
            ((uint32_t)nClearValue << 16) |
            ((uint32_t)nClearValue);

        for(unsigned int nIndex = 0; nIndex < nEnd; nIndex++) {
            pTempBuffer[nIndex] = nClearDword;
        }
        SetCursor(0);
        return;
    }

    if(g_nBufferWindowSize % sizeof(uint16_t) == 0) {
        uint16_t* pTempBuffer = (uint16_t*)g_aBufferWindow;
        unsigned int nEnd = g_nBufferWindowSize / sizeof(uint16_t);

        for(unsigned int nIndex = 0; nIndex < nEnd; nIndex++) {
            pTempBuffer[nIndex] = nClearValue;
        }
        SetCursor(0);
        return;
    }
}

void Console::SetColor(unsigned char nNewColor)
{
    g_nColor = nNewColor;
}

void Console::SetColorFg(unsigned char nNewColor)
{
    char nColor = (g_nColor & 0xF0);
    g_nColor = ((nColor) | (nNewColor & 0x0F));
}

unsigned char Console::GetColorFg(void)
{
    return (g_nColor & 0x0F);
}

void Console::SetColorBg(unsigned char nNewColor)
{
    char nColor = (g_nColor & 0x0F);
    g_nColor = ((nColor) | ((nNewColor & 0x0F) << 4));
}

unsigned char Console::GetColorBg(void)
{
    return ((g_nColor & 0xF0) >> 4);
}

int Console::_2d_to_linear(unsigned int nX, unsigned int nY, unsigned int nHeight)
{
    return (nHeight *nY) + nX;
}
