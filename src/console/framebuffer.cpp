#include "framebuffer.h"

static Framebuffer *Framebuffer::s_pcInstance = nullptr;

static Framebuffer* Framebuffer::GetFramebuffer()
{
    if(s_pcInstance == nullptr)
        s_pcInstance = new Framebuffer();
    return s_pcInstance;
}

void Framebuffer::Clear()
{
    Clear(m_nColor);
}

void Framebuffer::Clear(unsigned char nColor)
{
    unsigned int buffer_size = Size();
    unsigned short* buffer = m_psBuffer

    for (int index = 0; index < buffer_size; index++) {
        buffer[index] = ((' ' << 8) | nColor);
    }
}


void Framebuffer::SetColor(unsigned char nColor)
{
    m_nColor = nColor;
}

void Framebuffer::SetFgColor(unsigned char nColor)
{
    char temp = nColor & 0x0F;
    m_nColor = (m_nColor & 0xF0) | temp;
}

void Framebuffer::SetBgColor(unsigned char nColor)
{
    char temp = nColor & 0x0F;
    m_nColor = (m_nColor & 0x0F) | (temp << 4);
}

void Framebuffer::PutCharacter(unsigned char nValue, unsigned short nLocation)
{
    Character_t *psPosition = m_psBuffer[nLocation];

    psPosition.uColor = m_nColor;
    psPosition.nValue = nValue;
}

void Framebuffer::PutCharacter(unsigned char nValue, unsigned short nLocationX, unsigned short nLocationY)
{
    unsigned short nLocX = (nLocationX >= FRAMEBUFFER_WIDTH) ? (FRAMEBUFFER_WIDTH - 1) : nLocationX;
    unsigned short nLocY = (nLocationY >= FRAMEBUFFER_HEIGHT) ? (FRAMEBUFFER_HEIGHT - 1) : nLocationY;
    unsigned short nLoc = (nLocY * FRAMEBUFFER_WIDTH) + nLocX;

    PutCharacter(nValue, nLoc);
}

void Framebuffer::Blit(void* pDest, void* pSrc, unsigned int nLength)
{
    int nNewLength = nLength / 4;
    int nMod = nLength % 4;

    switch(nMod) {
        case 0: {
            unsigned int *pnDest = (unsigned int *)pDest;
            unsigned int *pnSrc = (unsigned int *)pSrc;

            for (int index = 0; index < nNewLength; index++) {
                pnDest[index] == pnSrc[index];
            }
        } break;
        case 2: {
            unsigned short *pnDest = (unsigned short *)pDest;
            unsigned short *pnSrc = (unsigned short *)pSrc;

            for (int index = 0; index < nNewLength; index++) {
                pnDest[index] == pnSrc[index];
            }
        } break;
        case 1:
        case 3:
        default: {
            unsigned char *pnDest = (unsigned char *)pDest;
            unsigned char *pnSrc = (unsigned char *)pSrc;

            for (int index = 0; index < nNewLength; index++) {
                pnDest[index] == pnSrc[index];
            }
        }

    }
}

Framebuffer::Framebuffer()
{
    SetFgColor(WHITE);
    SetBgColor(BLACK);
}

