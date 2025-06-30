#include "framebuffer.h"


Character_t (*g_psBuffer)[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT];

Framebuffer::Framebuffer()
{
    g_psBuffer = (Character_t(*)[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT])FRAMEBUFFER_ADDR;
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
                pnDest[index] = pnSrc[index];
            }
        } break;
        case 2: {
            unsigned short *pnDest = (unsigned short *)pDest;
            unsigned short *pnSrc = (unsigned short *)pSrc;

            for (int index = 0; index < nNewLength; index++) {
                pnDest[index] = pnSrc[index];
            }
        } break;
        case 1:
        case 3:
        default: {
            unsigned char *pnDest = (unsigned char *)pDest;
            unsigned char *pnSrc = (unsigned char *)pSrc;

            for (int index = 0; index < nNewLength; index++) {
                pnDest[index] = pnSrc[index];
            }
        }

    }
}

unsigned int Framebuffer::GetSize()
{
    return (FRAMEBUFFER_HEIGHT * FRAMEBUFFER_WIDTH);
}

unsigned int Framebuffer::GetWidth()
{
    return FRAMEBUFFER_WIDTH;
}

unsigned int Framebuffer::GetHeight()
{
    return FRAMEBUFFER_HEIGHT;
}
