#ifndef __PPU_H__
#define __PPU_H__

#include "Public.h"

#define PPU_PATTEN_TABLE0_ADDR 0x0000
#define PPU_PATTEN_TABLE0_SIZE 0x1000

#define PPU_PATTEN_TABLE1_ADDR 0x1000
#define PPU_PATTEN_TABLE1_SIZE 0x1000

#define PPU_NAME_TABLE0_ADDR   0x2000
#define PPU_NAME_TABLE0_SIZE   0x3C0

#define PPU_ATTRI_TABLE0_ADDR  0x23C0
#define PPU_ATTRI_TABLE0_SIZE  0x40

#define PPU_NAME_TABLE1_ADDR   0x2400
#define PPU_NAME_TABLE1_SIZE   0x3C0

#define PPU_ATTRI_TABLE1_ADDR  0x27C0
#define PPU_ATTRI_TABLE1_SIZE  0x40

#define PPU_NAME_TABLE2_ADDR   0x2800
#define PPU_NAME_TABLE2_SIZE   0x3C0

#define PPU_ATTRI_TABLE2_ADDR  0x2BC0
#define PPU_ATTRI_TABLE2_SIZE  0x40

#define PPU_NAME_TABLE3_ADDR   0x2C00
#define PPU_NAME_TABLE3_SIZE   0x3C0

#define PPU_ATTRI_TABLE3_ADDR  0x2FC0
#define PPU_ATTRI_TABLE3_SIZE  0x40

#define PPU_IMAGE_PALETTE_ADDR 0x3F00
#define PPU_IMAGE_PALETTE_SIZE 0x10

#define PPU_SPRITE_PALETTE_ADDR 0x3F00
#define PPU_SPRITE_PALETTE_SIZE 0x10

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#define IMAGE_TYPE_H 0
#define IMAGE_TYPE_V 1
#define IMAGE_TYPE_S 2
#define IMAGE_TYPE_F 3

class PPU
{
	
public:


	UCHAR m_screen[256*256+5];
	UCHAR m_spriteScreen[256*256+5];
	UCHAR m_ram[0x3000];
	UCHAR m_spritePallet[16];
	UCHAR m_backgPallet[16];
	UCHAR m_spriteRam[256];
	UCHAR m_rCtrl[8];
	
	USHORT m_currRamIndex;
	UCHAR  m_currSprRamIndex;
	
	USHORT m_currVRollPosion;
	USHORT m_currHRollPosion;
	UCHAR  m_VRollOffset;
	UCHAR  m_HRollOffset;
	BOOL   m_bFirstSetRamAddr;
	BOOL   m_bFirstSetRollOffset;
	BOOL   m_bFirstRead;
	BOOL   m_hitSprite0;

	UINT   m_imageType;
	
	void WriteRam(UCHAR ucData);
	UCHAR ReadRam();
	
	void WriteSpriteRam(UCHAR ucData);
	UCHAR ReadSpriteRam();
	
	PPU();
	~PPU();
	void Reset();
	void SetImageType(UINT imageType);
	
	void SetCurrRamIndex(UCHAR ucAddr);
	void SetCurrSpriteRamIndex(UCHAR ucIndex);
	void SetRollOffset(UCHAR ucData);
	
	void UpdateBkg0(UCHAR screen[], UINT type);
	void LoadPatten(UCHAR* pbData, UINT uSize);
	void PrintPatten(int iIndex);
	void UpdateScreen();
	void UpdateSprite();
	void UpdateBkg();
	void UpdateLine(int iRow);
	
	void PrintSprite8x8(UCHAR ucX, UCHAR ucY, UCHAR ucTitle, UCHAR ucFlag, int iIndex);
	void PrintSprite8x16(UCHAR ucX, UCHAR ucY, UCHAR ucTitle, UCHAR ucFlag, int iIndex);
	
	void WriteRegister(int iType, UCHAR ucValue);
	UCHAR ReadRegister(int iType);
};

#endif