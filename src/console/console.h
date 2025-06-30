#pragma once

class Console
{
public:
    Console();
    ~Console() {}

    void PutChar(char nCharacter);
    void PutChar(char nCharacter, unsigned int nX, unsigned int nY);
    void WriteString(const char* pString);
    unsigned int GetCursor(void);
    void SetCursor(unsigned int nLocation);
    void SetCursor(unsigned int nX, unsigned int nY);
    void Clear();
    void Clear(unsigned char nColor);
    void SetColor(unsigned char nNewColor);
    void SetColorFg(unsigned char nNewColor);
    unsigned char GetColorFg(void);
    void SetColorBg(unsigned char nNewColor);
    unsigned char GetColorBg(void);


private:
    int _2d_to_linear(unsigned int nX, unsigned int nY, unsigned int nHeight);
};
