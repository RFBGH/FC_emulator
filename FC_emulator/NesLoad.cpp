#include "stdafx.h"
#include "NesLoad.h"


NesLoad nesLoad;

NesLoad::NesLoad()
{
	
}

NesLoad::~NesLoad()
{
	
}

int NesLoad::LoadNesFile(char* pFileName, NesFile& nesFile, CPU6502* pCPU, PPU* pPPU){

	CString csFileBuf;
	UCHAR*	pucFileBuf;
	CFile	file;
	int iRomSize;
	int iVRomSize;
	int iImageType;
	int iRomType;

	file.Open(pFileName, CFile::modeReadWrite);
	csFileBuf.GetBuffer(file.GetLength()+5);
	pucFileBuf = (UCHAR*)csFileBuf.GetBuffer(0);
	file.Read(pucFileBuf, file.GetLength());

	iRomSize = pucFileBuf[4]*16*1024;

	iVRomSize = pucFileBuf[5]*8*1024;

	nesFile.setHead(pucFileBuf);

	nesFile.setRom(pucFileBuf+16, iRomSize);
	nesFile.setVRom(pucFileBuf+iRomSize+16, iVRomSize);

	if(iRomSize < 32*1024){

		UCHAR temp[32*1024];
		MemSet(temp, 0, sizeof(temp));
		MemCpy(temp+16*1024, nesFile.m_rom, 16*1024);
		pCPU->UpdateRom(temp, 32*1024, 0);
	}else{
		pCPU->UpdateRom(nesFile.m_rom+iRomSize-32*1024, 32*1024, 0);
	}
	
	if(iVRomSize != 0){
		pPPU->LoadPatten(nesFile.m_vrom, 8*1024);
	}

	if(pucFileBuf[6]&0x01)
	{
		iImageType = IMAGE_TYPE_V;
	}else if(pucFileBuf[6]&0x08)
	{
		iImageType = IMAGE_TYPE_F;
	}else
	{
		iImageType = IMAGE_TYPE_H;
	}

	pPPU->SetImageType(iImageType);

	return 0;
}

int NesLoad::LoadNesFile(char* pFileName, CPU6502* pCPU, PPU* pPPU)
{
	CString csFileBuf;
	UCHAR*	pucFileBuf;
	CFile	file;
	int iRomSize;
	int iRomType;
	int iPattenSize;
	int iImageType;
	
	if(!pFileName || !pCPU || !pPPU)
	{
		return 3;
	}
	
	csFileBuf.GetBuffer((32+8)*1024+32);
	pucFileBuf = (UCHAR*)csFileBuf.GetBuffer(0);
	
	file.Open(pFileName, CFile::modeReadWrite);
	file.Read(pucFileBuf, 16);
	
	//loadrom
	if(pucFileBuf[4] > 2)
	{
		return 1;
	}
	
	switch(pucFileBuf[4])
	{
		case 1:
			iRomType = ROM_TYPE_16K;
			break;
			
		case 2:
			iRomType = ROM_TYPE_32K;
			break;	
	}
	
	iRomSize = pucFileBuf[4]*(16*1024);
	file.Read(pucFileBuf+16, iRomSize);
	pCPU->UpdateRom(pucFileBuf+16, iRomSize, iRomType);
	
	if(pucFileBuf[5] > 1)
	{
		return 2;
	}
	
	iPattenSize = pucFileBuf[5]*8*1024;
	file.Read(pucFileBuf+16, iPattenSize);
	pPPU->LoadPatten(pucFileBuf+16, iPattenSize);
	
	if(pucFileBuf[6]&0x01)
	{
		iImageType = IMAGE_TYPE_V;
	}else if(pucFileBuf[6]&0x08)
	{
		iImageType = IMAGE_TYPE_F;
	}else
	{
		iImageType = IMAGE_TYPE_H;
	}

	pPPU->SetImageType(iImageType);
	
	return 0;
}
