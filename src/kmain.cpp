extern "C" {



int kmain()
{
	const unsigned int VID_MEM_START = 0xB800;
	unsigned char *pScreen = (unsigned char *)VID_MEM_START;
	char nColor = 0xF0;
	char *pMsg = (char *)"Hello from the Ember Kernel!!!";

	while(pMsg != 0) {
		*pScreen++ = *pMsg++;
		*pScreen++ = nColor;
	}

	return 0;
}

}
