#ifndef __NES_LOAD_H__
#define __NES_LOAD_H__

#include "PPU.h"
#include "6502CPU.h"

class NesLoad
{

public:
	NesLoad();
	~NesLoad();
	
	int LoadNesFile(char* pFileName, CPU6502* pCPU, PPU* pPPU);

	int LoadNesFile(char* pFileName, NesFile& nesFile, CPU6502* pCPU, PPU* pPPU);
};

extern NesLoad nesLoad;

#endif