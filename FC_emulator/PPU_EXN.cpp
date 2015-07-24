#include "PPU.h"

void PPU::Reset()
{
	
	m_bFirstSetRamAddr = TRUE;
	m_bFirstSetRollOffset = TRUE;
	m_bFirstRead = TRUE;
	
	MemSet(m_ram, 0, sizeof(m_ram));
	MemSet(m_spritePallet, 0, sizeof(m_spritePallet));
	MemSet(m_backgPallet, 0, sizeof(m_backgPallet));
	MemSet(m_rCtrl, 0, sizeof(m_rCtrl));
	
	m_currVRollPosion = 0;
	m_currHRollPosion = 0;
	m_VRollOffset = 0;
	m_HRollOffset = 0;

	//ˮƽ����
	m_imageType = IMAGE_TYPE_H;	
}


void PPU::LoadPatten(UCHAR* pbData, UINT uSize)
{
	if(pbData == NULL)
	{
		return;
	}
	if(uSize > 0x1000*2)
	{
		uSize = 0x1000*2;
	}
	
	MemCpy(m_ram, pbData, uSize);
}

void PPU::PrintPatten(int iIndex)
{
	if(iIndex > 1)
	{
		iIndex = 1;
	}
	
	int i;
	int iBit;
	int iBlock;
	MemSet(m_screen, 0, sizeof(m_screen));
	for(i = 0; i < 0x1000; i++)
	{
		UCHAR ucTmp1 = m_ram[iIndex*0x1000+i];
		iBlock = i>>4;
		
		int iOffset =  ((iBlock>>5)<<11)+((iBlock&0x1F)<<3)+((i&0x7)<<8);
		
		for(iBit = 0; iBit < 8; iBit++)
		{
			if((ucTmp1>>iBit) & 0x01)
			{
				
				if(i&0x08)
				{	//bit1
					m_screen[iOffset+(7-iBit)] |= 0x02;
				}else
				{	//bit0
					m_screen[iOffset+(7-iBit)] |= 0x01;
				}
			}else
			{
				if(i&0x08)
				{	//bit1
					m_screen[iOffset+(7-iBit)] &= 0xFD;
				}else
				{	//bit0
					m_screen[iOffset+(7-iBit)] &= 0xFE;
				}
			}
			
		}
	}
	
	for(i = 0; i < 65537; i++)
	{
		gScreenBuf[i] = tFcColorTable[m_screen[i]];
	}
	
	for(i = 0; i < 64; i++)
	{
		gScreenBuf[130*256+(i&0x7)+((i>>3)<<8)] = 0xFFFFFFFF;
	}
}

void PPU::UpdateScreen()
{
		
	//��ʼ����Ļ
	MemSet(m_screen, 0, sizeof(m_screen));
	
	//��Ļʹ��
	if(!(m_rCtrl[1]&0x08))
	{	
		return;
	}

	//���Ʊ���
	UpdateBkg();
	
	//���ƾ���
	m_hitSprite0 = FALSE;
	UpdateSprite();
}

void PPU::UpdateLine(int iRow)
{

	//����״̬λ
	//���б�־
	//vBlanck��־
	if(iRow == 0)
	{
		m_rCtrl[2] &= 0x3F;	
	}
	
	int i;
	for(i = 0; i < 256; i++)
	{	//���Ƶ���
		
		if(m_spriteScreen[iRow*256+i])
		{
			gScreenBuf[iRow*256+i] = tFcColorTable[m_spritePallet[m_spriteScreen[iRow*256+i]]];
		}else
		{
			gScreenBuf[iRow*256+i] = tFcColorTable[m_backgPallet[m_screen[iRow*256+i]]];
		}
		
		if(m_hitSprite0)
		{	//�ж��Ƿ�ײ��������0
			if(m_rCtrl[0]&0x20)
			{
				if(iRow >= m_spriteRam[0] && iRow <= m_spriteRam[0]+16
					&& i >= m_spriteRam[3] && i <= m_spriteRam[3]+8)
				{
					m_rCtrl[2] |= 0x40;
				}				
			}else
			{
				if(iRow >= m_spriteRam[0] && iRow <= m_spriteRam[0]+8
					&& i >= m_spriteRam[3] && i <= m_spriteRam[3]+8)
				{
					m_rCtrl[2] |= 0x40;
				}
			}
		}
	}
	
	if(iRow == 239)
	{
		//m_currVRollPosion += m_VRollOffset;
		//m_currHRollPosion += m_HRollOffset;
	
		//����VBLOCKΪ1
		m_rCtrl[2] |= 0x80;
	}
}

/*
void PPU::UpdateBkg()
{
	int iIndexNameTable;
	int iIndexPattenTable;
	int iIndexAttriTable; 
	int iNameTable;
	int iPattenTable;
	int iAttriTable;
	int iBlock;
	int iBit;
	int iName;
	int i;
	
	//����
	iIndexNameTable = 0;
	iIndexPattenTable = 0;
	iIndexAttriTable = 0;
	
	//ѡ����Ƶ�name��
	if(m_rCtrl[0]&0x01)
	{
		iIndexNameTable = 1;
		iIndexAttriTable = 1;
	}else
	{
		iIndexNameTable = 0;
		iIndexAttriTable = 0;		
	}
	
	//ѡ��patten��
	if(m_rCtrl[0]&0x10)
	{
		iIndexPattenTable = 1;
	}else
	{
		iIndexPattenTable = 0;
	}
	
	MemSet(m_screen, 0, sizeof(m_screen));
	iNameTable = 0x2000+(iIndexNameTable<<10);
	iPattenTable = iIndexPattenTable << 12;
	
	//���Ʊ���ͼƬ�У���2��bit������
	for(iBlock = 0; iBlock < 0x3C0; iBlock++)
	{
		iName = m_ram[iNameTable+iBlock];
		iName <<= 4;
		int iOffset = ((iBlock>>5)<<11)+((iBlock&0x1F)<<3);
		for(i = 0; i < 0x0F; i++)
		{
			UCHAR ucTmp1 = m_ram[iPattenTable+iName+i];
			for(iBit = 0; iBit < 8; iBit++)
			{
				if((ucTmp1>>iBit) & 0x01)
				{
					
					if(i&0x08)
					{	//bit1
						m_screen[iOffset+((i&0x7)<<8)+(7-iBit)] |= 0x02;
					}else
					{	//bit0
						m_screen[iOffset+((i&0x7)<<8)+(7-iBit)] |= 0x01;
					}
				}else
				{
					if(i&0x08)
					{	//bit1
						m_screen[iOffset+((i&0x7)<<8)+(7-iBit)] &= 0xFD;
					}else
					{	//bit0
						m_screen[iOffset+((i&0x7)<<8)+(7-iBit)] &= 0xFE;
					}
				}	
			}
		}
	}
	
	//���Ʊ���ͼƬ�и�2bit������
	iAttriTable = iNameTable+0x3C0;
	for(iBlock = 0; iBlock < 0x40; iBlock++)
	{
		UCHAR ucTmp1 = m_ram[iAttriTable+iBlock];
		 
		for(i = 0; i < 1024; i++)
		{
			UINT u = ((i>>9)<<1) + ((i&0x1F)>>4);
			u <<= 1;
			
			m_screen[((iBlock>>3)<<13) + ((iBlock&0x7)<<5) + (i&0x1F) + ((i>>5)<<8)] |= (((ucTmp1>>u)<<2) & 0x0C);
		}
	}
	
	//��ӡ����Ļ��
	for(i = 0; i < 65537; i++)
	{
		gScreenBuf[i] = tFcColorTable[m_backgPallet[m_screen[i]]];
		//gScreenBuf[i] = tFcColorTable[m_screen[i]];
	}	
}
*/

void PPU::UpdateBkg0(UCHAR screen[], UINT type)
{
	int iIndexNameTable;
	int iIndexPattenTable;
	int iIndexAttriTable; 
	int iNameTable;
	int iPattenTable;
	int iAttriTable;
	int iBlock;
	int iBit;
	int iName;
	int i;
	
	if(type == 0)
	{
		iIndexNameTable = 0;
		iIndexAttriTable = 0;		
	}else
	{
		iIndexNameTable = 1;
		iIndexAttriTable = 1;		
	}
	
	//ѡ��patten��
	if(m_rCtrl[0]&0x10)
	{
		iIndexPattenTable = 1;
	}else
	{
		iIndexPattenTable = 0;
	}
	
	MemSet(screen, 0, 256*256);
	iNameTable = 0x2000+(iIndexNameTable<<10);
	iPattenTable = iIndexPattenTable << 12;
	
	//���Ʊ���ͼƬ�У���2��bit������
	for(iBlock = 0; iBlock < 0x3C0; iBlock++)
	{
		iName = m_ram[iNameTable+iBlock];
		iName <<= 4;
		int iOffset = ((iBlock>>5)<<11)+((iBlock&0x1F)<<3);
		for(i = 0; i < 0x10; i++)
		{
			UCHAR ucTmp1 = m_ram[iPattenTable+iName+i];
			for(iBit = 0; iBit < 8; iBit++)
			{
				if((ucTmp1>>iBit) & 0x01)
				{
					
					if(i&0x08)
					{	//bit1
						screen[iOffset+((i&0x7)<<8)+(7-iBit)] |= 0x02;
					}else
					{	//bit0
						screen[iOffset+((i&0x7)<<8)+(7-iBit)] |= 0x01;
					}
				}else
				{
					if(i&0x08)
					{	//bit1
						screen[iOffset+((i&0x7)<<8)+(7-iBit)] &= 0xFD;
					}else
					{	//bit0
						screen[iOffset+((i&0x7)<<8)+(7-iBit)] &= 0xFE;
					}
				}	
			}
		}
	}
	
	//���Ʊ���ͼƬ�и�2bit������
	iAttriTable = iNameTable+0x3C0;
	for(iBlock = 0; iBlock < 0x40; iBlock++)
	{
		UCHAR ucTmp1 = m_ram[iAttriTable+iBlock];
		 
		for(i = 0; i < 1024; i++)
		{
			UINT u = ((i>>9)<<1) + ((i&0x1F)>>4);
			u <<= 1;
			
			screen[((iBlock>>3)<<13) + ((iBlock&0x7)<<5) + (i&0x1F) + ((i>>5)<<8)] |= (((ucTmp1>>u)<<2) & 0x0C);
		}
	}
}

void PPU::UpdateBkg()
{

	UCHAR screenA[256*256+5];
	UCHAR screenB[256*256+5];
	int i = 0;

	if(m_currVRollPosion && m_currHRollPosion)
	{
		return;
	}
	
	//ѡ����Ƶ�name��
	switch(m_imageType)
	{
	case IMAGE_TYPE_H:
		if(m_rCtrl[0]&0x02)
		{
			UpdateBkg0(screenA, 1);
			UpdateBkg0(screenB, 0);
		}else
		{
			UpdateBkg0(screenA, 0);
			UpdateBkg0(screenB, 1);
		}
		break;
	case IMAGE_TYPE_V:
		if(m_rCtrl[0]&0x01)
		{
			UpdateBkg0(screenA, 1);
			UpdateBkg0(screenB, 0);
		}else
		{
			UpdateBkg0(screenA, 0);
			UpdateBkg0(screenB, 1);
		}
		break;
	case IMAGE_TYPE_S:
		UpdateBkg0(screenA, 0);
		UpdateBkg0(screenB, 0);

		break;
	case IMAGE_TYPE_F:
		break;
	}

	
#ifdef _DEBUG
	if(m_currVRollPosion >= 239)
	{
		int iDebug;
		iDebug = 1;
	}
#endif

	if(m_currVRollPosion)
	{
		int iRow;
		for(i = m_currVRollPosion; i < 240; i++)
		{
			for(iRow = 0; iRow < 256; iRow++)
			{
				m_screen[((i-m_currVRollPosion)<<8)+iRow] = screenA[(i<<8)+iRow];
			}
		}
		for(i = 0; i < m_currVRollPosion; i++)
		{
			for(iRow = 0; iRow < 256; iRow++)
			{
				m_screen[((i+240-m_currVRollPosion)<<8)+iRow] = screenB[(i<<8)+iRow];
			}		
		}
	}else
	{
		
		int iColmn;
		for(i = 0; i < 240; i++)
		{
			for(iColmn = 0; iColmn < 256; iColmn++)
			{
				if(iColmn < (256-m_currHRollPosion))
				{
					m_screen[(i<<8)+iColmn] = screenA[(i<<8)+iColmn+m_currHRollPosion];
				}else
				{
					m_screen[(i<<8)+iColmn] = screenB[(i<<8)+iColmn+m_currHRollPosion-256];
				}
			}
		}
	}
	
	//��ӡ����Ļ��
	/*
	for(i = 0; i < 65537; i++)
	{
		gScreenBuf[i] = tFcColorTable[m_backgPallet[m_screen[i]]];
	}
	*/
}

void PPU::PrintSprite8x8(UCHAR ucX, UCHAR ucY, UCHAR ucTitle, UCHAR ucFlag, int iIndex)
{
	int iRamOffset;
	int iTitle;
	int iRam;
	int iBit;
	int i;
	UCHAR sprite[64+5];
	
	MemSet(sprite, 0, sizeof(sprite));
	
	iTitle = ucTitle<<4;
	iRamOffset = ((ucY-1)<<8)+ucX;
	
	//����title���ڵ�patten 0:0x000; 1:0x1000
	if(m_rCtrl[0]&0x08)
	{
		iTitle |= 0x1000;
	}
	
	//��������ʾ�ڴ�
	for(i = 0; i < 0x10; i++)
	{
		UCHAR ucTmp = m_ram[iTitle+i];
		for(iBit = 0; iBit < 8; iBit++)
		{
			if(ucFlag & 0x40)
			{	//ˮƽ��ת
				iRam = iBit;
			}else
			{
				iRam = (7-iBit);
			}
			
			if(ucFlag & 0x80)
			{	//��ֱ��ת
				iRam += ((7-(i&0x7))<<3);
			}else
			{
				iRam += ((i&0x7)<<3);
			}
			
			if((ucTmp>>iBit)&0x01)
			{
				if(i&0x08)
				{
					sprite[iRam] |= 2;
				}else
				{
					sprite[iRam] |= 1;
				}
				
			}else
			{
				if(i&0x08)
				{
					sprite[iRam] &= 0xFD;
				}else
				{
					sprite[iRam] &= 0xFE;
				}
			}
		}
	}
	
	//��������ʾ�ڴ��ӡ����Ļ�ϡ�
	for(i = 0; i < 64; i++)
	{
		if(sprite[i])
		{
			int iOffset = iRamOffset + ((i>>3)<<8) + (i&0x07);
			
			if(iIndex == 0 && !(m_rCtrl[2]&0x40)/*&&(m_screen[iOffset])*/)
			{
				m_hitSprite0 = TRUE;
			}
			
			m_spriteScreen[iOffset] = sprite[i]|((ucFlag&0x03) << 2);
			//gScreenBuf[iOffset] = tFcColorTable[m_spritePallet[sprite[i]|((ucFlag&0x03) << 2)]];
			//gScreenBuf[iOffset] = tFcColorTable[sprite[i]|((ucFlag&0x03) << 2)];
		}
	}
}

void PPU::PrintSprite8x16(UCHAR ucX, UCHAR ucY, UCHAR ucTitle, UCHAR ucFlag, int iIndex)
{
	int iRamOffset;
	int iTitle;
	int iBit;
	int iRam;
	int i;
	UCHAR sprite[64+5];
	
	MemSet(sprite, 0, sizeof(sprite));
	
	//���Ƶ�һ�� bit0 = 0;
	iTitle = (ucTitle&0xFE)<<4;
	if(ucTitle & 0x01)
	{
		iTitle |= 0x1000;
	}
	
	
	if(ucFlag & 0x80)
	{
		//��ֱ��ת
		iRamOffset = ((ucY-1+8)<<8)+ucX;
	}else
	{
		//�޴�ֱ��ת
		iRamOffset = ((ucY-1)<<8)+ucX;
	}
	
	//��������ʾ�ڴ�
	for(i = 0; i < 0x10; i++)
	{
		UCHAR ucTmp = m_ram[iTitle+i];
		for(iBit = 0; iBit < 8; iBit++)
		{
			if(ucFlag & 0x40)
			{	//ˮƽ��ת
				iRam = iBit;
			}else
			{
				iRam = (7-iBit);
			}
			
			if(ucFlag & 0x80)
			{	//��ֱ��ת
				iRam += ((7-(i&0x7))<<3);
			}else
			{
				iRam +=  ((i&0x7)<<3);
			}
			
			if((ucTmp>>iBit)&0x01)
			{
				if(i&0x08)
				{
					sprite[iRam] |= 2;
				}else
				{
					sprite[iRam] |= 1;
				}
				
			}else
			{
				if(i&0x08)
				{
					sprite[iRam] &= 0xFD;
				}else
				{
					sprite[iRam] &= 0xFE;
				}
			}
		}
	}	
	//��������ʾ�ڴ��ӡ����Ļ�ϡ�
	for(i = 0; i < 64; i++)
	{
		if(sprite[i])
		{
			int iOffset = iRamOffset + ((i>>3)<<8) + (i&0x07);
			
			if(iIndex == 0 && !(m_rCtrl[2]&0x40)&&(m_screen[iOffset]))
			{
				m_hitSprite0 = TRUE;
			}
			
			m_spriteScreen[iOffset] = sprite[i]|((ucFlag&0x03) << 2);
			//gScreenBuf[iOffset] = tFcColorTable[m_spritePallet[sprite[i]|((ucFlag&0x03) << 2)]];
		}
	}
	
	MemSet(sprite, 0, sizeof(sprite));
	//���Ƶڶ��� bit0 = 0;
	iTitle = (ucTitle|0x01)<<4;
	if(ucTitle & 0x01)
	{
		iTitle |= 0x1000;
	}
	
	if(ucFlag & 0x80)
	{
		//��ֱ��ת
		iRamOffset = ((ucY-1)<<8)+ucX;
	}else
	{
		//�޴�ֱ��ת
		iRamOffset = ((ucY-1+8)<<8)+ucX;
	}
	
	//��������ʾ�ڴ�
	for(i = 0; i < 0x10; i++)
	{
		UCHAR ucTmp = m_ram[iTitle+i];
		for(iBit = 0; iBit < 8; iBit++)
		{
			if(ucFlag & 0x40)
			{	//ˮƽ��ת
				iRam = iBit;
			}else
			{
				iRam = (7-iBit);
			}
			
			if(ucFlag & 0x80)
			{	//��ֱ��ת
				iRam += ((7-(i&0x7))<<3);
			}else
			{
				iRam +=  ((i&0x7)<<3);
			}
			
			if((ucTmp>>iBit)&0x01)
			{
				if(i&0x08)
				{
					sprite[iRam] |= 2;
				}else
				{
					sprite[iRam] |= 1;
				}
				
			}else
			{
				if(i&0x08)
				{
					sprite[iRam] &= 0xFD;
				}else
				{
					sprite[iRam] &= 0xFE;
				}
			}
		}
	}
	//��������ʾ�ڴ��ӡ����Ļ�ϡ�
	for(i = 0; i < 64; i++)
	{
		if(sprite[i])
		{
			int iOffset = iRamOffset + ((i>>3)<<8) + (i&0x07);
			
			
			if(!(m_rCtrl[2]&0x40)&&(m_screen[iOffset]))
			{
				m_hitSprite0 = TRUE;
			}
			
			m_spriteScreen[iOffset] = sprite[i]|((ucFlag&0x03) << 2);
			//gScreenBuf[iOffset] = tFcColorTable[m_spritePallet[sprite[i]|((ucFlag&0x03) << 2)]];
		}
	}
}

//TODO...
void PPU::UpdateSprite()
{
	if(!(m_rCtrl[1]&0x10))
	{
		return;
	}

	int iSprite;
	BOOL bTaller;

	
	//��������0:8x8; 1:8*16
	bTaller = FALSE;
	if(m_rCtrl[0]&0x20)
	{
		bTaller = TRUE;
	}
	
	MemSet(m_spriteScreen, 0, sizeof(m_spriteScreen));
	
	for(iSprite = 0; iSprite < 256; iSprite += 4)
	{
		UCHAR ucX = m_spriteRam[255-iSprite];
		UCHAR ucY = m_spriteRam[255-iSprite-3];
		UCHAR ucFlag = m_spriteRam[255-iSprite-1];
		UCHAR ucTitle = m_spriteRam[255-iSprite-2];
		
		if(bTaller)
		{	//8x16���ؾ���
			PrintSprite8x16(ucX, ucY, ucTitle, ucFlag, (255-iSprite)/4);

		}else
		{	//8x8 ���ؾ���
			PrintSprite8x8(ucX, ucY, ucTitle, ucFlag, (255-iSprite)/4);
		}
	}
}

void PPU::WriteRam(UCHAR ucData)
{
	/*
	//д����
	if(!(m_rCtrl[2]&0x10))	
	{
		return;
	}
	
	if(!(m_rCtrl[2]&0x80))
	{
		return;
	}
	*/

	if(m_currRamIndex < 0x2000)
	{	//�������⣬��Ҫע��Ŷ...
		
		
	}else if((m_currRamIndex >= 0x2000 && m_currRamIndex < 0x3000))
	{
#ifdef _DEBUG
		if(ucData != 0x00)
		{
			int i;
			i = 1;
		}
#endif
		if(m_imageType == IMAGE_TYPE_H)
		{	//ˮƽ����
			if(m_currRamIndex >= 0x2000 && m_currRamIndex < 0x2800)
			{
				m_ram[m_currRamIndex&0x23FF] = ucData;
			}else
			{
				m_ram[(m_currRamIndex&0x23FF)+0x400] = ucData;
			}
			
		}else if(m_imageType == IMAGE_TYPE_V)
		{	//��ֱ����
			if(m_currRamIndex&0x400)
			{
				m_ram[(m_currRamIndex&0x23FF)+0x400] = ucData;
			}else
			{
				m_ram[m_currRamIndex&0x23FF] = ucData;
			}
			
		}else if(m_imageType == IMAGE_TYPE_S)
		{	//����
			m_ram[m_currRamIndex&0x23FF] = ucData;
		}else if(m_imageType == IMAGE_TYPE_F)
		{	//����
			m_ram[m_currRamIndex] = ucData;
		}
		//TODO...
		//�������⡣
		//m_ram[m_currRamIndex&0x37FF] = ucData;
	}else if(m_currRamIndex >= 0x3000 && m_currRamIndex < 0x3F00)
	{
		m_ram[m_currRamIndex&0x2EFF] = ucData;
	}else if(m_currRamIndex >= 0x3F00 && m_currRamIndex < 0x3F10)
	{
		m_backgPallet[m_currRamIndex&0xF] = ucData&0x3F;
	}else if(m_currRamIndex >= 0x3F10 && m_currRamIndex < 0x3F20)
	{ 
		if(m_currRamIndex == 0x3F10)
		{
			m_backgPallet[0] = ucData&0x3F;
			m_backgPallet[4] = ucData&0x3F;
			m_backgPallet[8] = ucData&0x3F;
			m_backgPallet[12] = ucData&0x3F;
			
			m_spritePallet[0] = ucData&0x3F;
			m_spritePallet[4] = ucData&0x3F;
			m_spritePallet[8] = ucData&0x3F;
			m_spritePallet[12] = ucData&0x3F;
		}
		
		m_spritePallet[m_currRamIndex&0xF] = ucData&0x3F;
	}else if(m_currRamIndex >= 0x3F20 && m_currRamIndex < 0x4000)
	{	//do what?
		if(m_currRamIndex&0x0010)
		{
			m_spritePallet[m_currRamIndex&0xF] = ucData&0x3F;
		}else
		{
			m_backgPallet[m_currRamIndex&0xF] = ucData&0x3F;
		}
	}else if(m_currRamIndex >= 0x4000 && m_currRamIndex < 0xC000)
	{
		UINT currRamIndex = m_currRamIndex;
		m_currRamIndex = m_currRamIndex&0x3FFF;
		WriteRam(ucData);
		m_currRamIndex = currRamIndex;
	}else
	{
		//....
	}
	
	//���µ�ǰPPU�ڴ�����
	//bit2:0 ������
	//bit2:1 ������
	if(m_rCtrl[0]&0x04)
	{
		m_currRamIndex += 32;
	}else
	{
		m_currRamIndex++;
	}
}

UCHAR PPU::ReadRam()
{
	UCHAR ucRet;
	
	if(m_bFirstRead)
	{
		m_bFirstRead = FALSE;
		return 0xFF;
	}
	
	if(m_currRamIndex < 0x3000)
	{	//�������⣬��Ҫע��Ŷ...
		
		ucRet = m_ram[m_currRamIndex];
	}else if(m_currRamIndex >= 0x3000 && m_currRamIndex < 0x3F00)
	{
		//ucRet = m_ram[m_currRamIndex&0x2EFF];
		if(m_imageType == IMAGE_TYPE_H)
		{	//ˮƽ����
			if(m_currRamIndex >= 0x2000 && m_currRamIndex < 0x2800)
			{
				ucRet = m_ram[m_currRamIndex&0x23FF];
			}else
			{
				ucRet = m_ram[(m_currRamIndex&0x23FF)+0x400];
			}

		}else if(m_imageType == IMAGE_TYPE_V)
		{	//��ֱ����
			if(m_currRamIndex&0x400)
			{
				ucRet = m_ram[(m_currRamIndex&0x23FF)+0x400];
			}else
			{
				ucRet = m_ram[m_currRamIndex&0x23FF];
			}

		}else if(m_imageType == IMAGE_TYPE_S)
		{	//����
			ucRet = m_ram[m_currRamIndex&0x23FF];
		}else if(m_imageType == IMAGE_TYPE_F)
		{	//����
			ucRet = m_ram[m_currRamIndex];
		}
	}else if(m_currRamIndex >= 0x3F00 && m_currRamIndex < 0x3F10)
	{
		ucRet = m_backgPallet[m_currRamIndex&0xF];
	}else if(m_currRamIndex >= 0x3F10 && m_currRamIndex < 0x3F20)
	{
		ucRet = m_spritePallet[m_currRamIndex&0xF];
	}else if(m_currRamIndex >= 0x3F20 && m_currRamIndex < 0x4000)
	{	//do what?
		UINT currRamIndex = m_currRamIndex;
		m_currRamIndex = m_currRamIndex&0x3F1F;
		ucRet = ReadRam(); 
		m_currRamIndex = currRamIndex;
	}else if(m_currRamIndex >= 0x4000 && m_currRamIndex < 0xC000)
	{
		UINT currRamIndex = m_currRamIndex;
		m_currRamIndex = m_currRamIndex&0x3FFF;
		ucRet = ReadRam();
		m_currRamIndex = currRamIndex;
	}else
	{
		//....
	}
	
	//���µ�ǰPPU�ڴ�����
	//bit2:0 ������
	//bit2:1 ������
	if(m_rCtrl[0]&0x04)
	{
		m_currRamIndex += 32;
	}else
	{
		m_currRamIndex++;
	}
	
	return ucRet;
}
	
void PPU::SetCurrSpriteRamIndex(UCHAR ucIndex)
{
	m_currSprRamIndex = ucIndex;
}
	
void PPU::WriteSpriteRam(UCHAR ucData)
{
	m_spriteRam[m_currSprRamIndex] = ucData;
	m_currSprRamIndex = (m_currSprRamIndex+1)%256;
}

UCHAR PPU::ReadSpriteRam()
{
	UCHAR ucRet;
	
	ucRet = m_spriteRam[m_currSprRamIndex];
	m_currSprRamIndex = (m_currSprRamIndex+1)%256;
	
	return ucRet;
}

void PPU::SetCurrRamIndex(UCHAR ucAddr)
{
	if(m_bFirstSetRamAddr)
	{	//д���ַ��ǰ6λ
		
		m_currRamIndex = 0x00;
		m_currRamIndex = (ucAddr&0x3F)<<8;
		m_bFirstSetRamAddr = FALSE;
	}else
	{	//д���ַ�ĺ�8λ
		
		m_currRamIndex |= ucAddr;
		m_bFirstSetRamAddr = TRUE;
		m_bFirstRead = TRUE;
	}
}

void PPU::SetRollOffset(UCHAR ucData)
{

#ifdef _DEBUG
	if(ucData)
	{
		int iDebug;
		iDebug = 1;
	}
#endif

	if(m_bFirstSetRollOffset)
	{
		if(ucData <= 240)
		{
			//m_VRollOffset = ucData;
			m_HRollOffset = ucData;
			m_currHRollPosion = ucData;
		}
		m_bFirstSetRollOffset = FALSE;
	}else
	{
		//m_HRollOffset = ucData;
		m_VRollOffset = ucData;
		m_currVRollPosion = ucData;
		m_bFirstSetRollOffset = TRUE;
	}
}

PPU::PPU()
{
	Reset();
}

PPU::~PPU()
{
	Reset();
}

void PPU::SetImageType(UINT imageType)
{
	if(imageType > IMAGE_TYPE_F)
	{
		return;
	}
	m_imageType = imageType;
}

void PPU::WriteRegister(int iType, UCHAR ucValue)
{
	switch(iType)
	{
		case 0:
		case 1:
			m_rCtrl[iType] = ucValue;
			break;
		
		case 3:
			m_rCtrl[iType] = ucValue;
			SetCurrSpriteRamIndex(ucValue);
			break;

		case 4:
			m_rCtrl[iType] = ucValue;
			WriteSpriteRam(ucValue);
			break;

		case 5:
			m_rCtrl[iType] = ucValue;
			SetRollOffset(ucValue);		
			break;
			
		case 6:
			m_rCtrl[iType] = ucValue;
			SetCurrRamIndex(ucValue);
			break;
			
		case 7:
			WriteRam(ucValue);
			m_rCtrl[iType] = ucValue;
			break;
	}
}

UCHAR PPU::ReadRegister(int iType)
{
	UCHAR ucRet;
	
	ucRet = 0;
	switch(iType)
	{
		case 2:
		case 0:
		case 1:
		case 3:
		case 5:
		case 6:
			ucRet = m_rCtrl[iType];
			if(iType == 2)
			{
				m_rCtrl[iType] &= 0x7F;
				m_bFirstSetRamAddr = TRUE;
				m_bFirstSetRollOffset = TRUE;
			}
			break;
		
		case 4:
			m_rCtrl[4] = ReadSpriteRam();
			ucRet = m_rCtrl[4];
			break;
			
		case 7:
			m_rCtrl[7] = ReadRam();
			ucRet = m_rCtrl[7];			
			break;
	}	
	return ucRet;
}