#pragma once

const unsigned int FRAMEBUFFER_ADDR    0xb8000
const unsigned int FRAMEBUFFER_WIDTH   80
const unsigned int FRAMEBUFFER_HEIGHT  25

const unsigned int BLACK           0
const unsigned int BLUE            1
const unsigned int GREEN           2
const unsigned int CYAN            3
const unsigned int RED             4
const unsigned int PURPLE          5
const unsigned int BROWN           6
const unsigned int GRAY            7
const unsigned int DARK_GRAY       8
const unsigned int LIGHT_BLUE      9
const unsigned int LIGHT_GREEN     10
const unsigned int LIGHT_CYAN      11
const unsigned int LIGHT_RED       12
const unsigned int LIGHT_PURPLE    13
const unsigned int YELLOW          14
const unsigned int WHITE           15


class Framebuffer
{
public:
    static Framebuffer* GetFramebuffer();
    ~Framebuffer() {}

    void Clear();
    void Clear(unsigned char nColor);
    void SetColor(unsigned char nColor);
    void SetFgColor(unsigned char nColor);
    void SetBgColor(unsigned char nColor);
    void PutCharacter(unsigned char nValue, unsigned short nLocation);
    void PutCharacter(unsigned char nValue, unsigned short nLocationX, unsigned short nLocationY);
    void Blit(void* pDest, void* pSrc, unsigned int nLength);
    unsigned int GetSize() { return (FRAMEBUFFER_HEIGHT * FRAMEBUFFER_WIDTH); }
    unsigned int GetWidth() { return FRAMEBUFFER_WIDTH; }
    unsigned int GetHeight() { return FRAMEBUFFER_HEIGHT; }

private:
    typedef union Color_u {
        struct {
            char nBgValue:4;
            char nFgValue:4;
        } U;
        unsigned char nValue;
    } Color_t;

    typedef struct Character_s {
        unsigned char nValue;
        Color_t uColor;
    } Character_t;

    Framebuffer() { m_psBuffer = FRAMEBUFFER_ADDR; }

    Framebuffer *s_pcInstance;
    unsigned Character_t *m_psBuffer;
    unsigned char m_nColor;
};
