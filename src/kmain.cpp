

extern "C" int kmain()
{
	const unsigned int VID_MEM_START = 0xB8000;
	volatile unsigned char *pScreen = (volatile unsigned char *)VID_MEM_START;
	char nColor = 0xF0;
	char *pMsg = (char *)"Hello from the Ember Kernel!!!";

	for(int nIndex = 0; pMsg[nIndex] != '\0'; nIndex++) {
        pScreen[nIndex * 2]     = pMsg[nIndex];
        pScreen[nIndex * 2 + 1] = nColor;
	}

	return 0;
}
