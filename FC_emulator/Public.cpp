#include "Public.h"
#include "time.h"

static UINT gsScreenBufFlag = 0;

#ifdef _DEBUG
UINT guDebugFlag = 0;
//UINT guDebugFlag = 1;
#else
UINT guDebugFlag = 0;
#endif


COLOR32 gScreenBuf[300*300];

//ARGB
COLOR32 tFcColorTable[64+5] = {0xFF868082,0xFF013983,0xFF0B1BB9,0xFF430398,
								0xFFA1005D,0xFFC40227,0xFFBA0800,0xFF911402,
								0xFF5D2E02,0xFF0B4701,0xFF044B00,0xFF05452B,
								0xFF054368,0xFF000100,0xFF010000,0xFF000205,
								0xFFC6C6C8,0xFF0079FF,0xFF2353FB,0xFF8336F8,
								0xFFEA2FB0,0xFFF9204B,0xFFFD2401,0xFFD73100,
								0xFFC36204,0xFF348101,0xFF078D06,0xFF008C57,
								0xFF079ED5,0xFF231E1A,0xFF070508,0xFF0B0704,
								0xFFF9FCFF,0xFF0ED8FC,0xFF6CA2FA,0xFFD480FC,
								0xFFFD46F0,0xFFFB658B,0xFFFDBA32,0xFFFF9B13,
								0xFFFDBA21,0xFF9EE118,0xFF2BEF35,0xFF09F0A2,
								0xFF06FAFB,0xFF5D5D5D,0xFF0D0D0F,0xFF0E0C11,
								0xFFF9FFFD,0xFFB8F3FF,0xFFB3EEFE,0xFFDCAAE5,
								0xFFFAA8FC,0xFFFDAEB4,0xFFFDACB5,0xFFFFEEA8,
								0xFFFDF799,0xFFD6E892,0xFFA9EEAF,0xFF9DF7D4,
								0xFF96FCFE,0xFFDFD8DF,0xFF121011,0xFF130F1E};


void SetScreenBuf(int x, int y, COLOR32 color)
{
	int iIndex = 0;

	if(x < 0)
	{
		x = 0;
	}
	if(y < 0)
	{
		y = 0;
	}
	if(x >= SCREEN_WIDTH)
	{
		x = SCREEN_WIDTH-1;
	}
	if(y >= SCREEN_HEIGHT)
	{
		y = SCREEN_HEIGHT-1;
	}

	iIndex = y*SCREEN_WIDTH+x;
	gScreenBuf[iIndex] = color;
}

COLOR32 GetColor(int x, int y)
{
	int iIndex = 0;

	if(x < 0)
	{
		x = 0;
	}
	if(y < 0)
	{
		y = 0;
	}
	if(x >= SCREEN_WIDTH)
	{
		x = SCREEN_WIDTH-1;
	}
	if(y >= SCREEN_HEIGHT)
	{
		y = SCREEN_HEIGHT-1;
	}

	return gScreenBuf[iIndex];
}

void MemSet(void* pDst, int iVal, int iSize)
{
	char* pucDst = NULL;
	
	pucDst = (char*)pDst;
	while(iSize > 0)
	{
		*pucDst++ = iVal;
		iSize--;
	}
}

void MemCpy(void* pDst, void* pSrc, int iSize)
{
	char* pucDst = NULL;
	char* pucSrc = NULL;
	
	pucDst = (char*)pDst;
	pucSrc = (char*)pSrc;
	
	while(iSize > 0)
	{
		*pucDst++ = *pucSrc++;
		iSize--;
	}
}

void Log(char* pFormat, ...)
{
	
#if 0
	if(guDebugFlag)
	{
		FILE* pFile = NULL;
		va_list vl;
		char czTmpLog[512];
	
		/*
		if(!access("./log", 0))
		{
			//存在log文件夹
		}else
		{
			//不存在log文件夹，重新创建
			iRet = CreateDirectory("./log", 0);
			if(iRet)
			{
			
			}else{
				//printf("create directory faild...\n");
				return;
			}
		}
		*/
	
	
		pFile = fopen("L:/nes/neslog.txt", "at");
		if(pFile == NULL)
		{
			//printf("can't open file\n");
			return ;
			//exit(1);
		}
	
		va_start(vl, pFormat);
		vsprintf(czTmpLog, pFormat, vl);
		fprintf(pFile, czTmpLog);
		va_end(vl);
	
		fclose(pFile);
	}else
	{

	}
#endif
}

int Random(void)
{
	static int n = 1;
	int uRnd = 0;
	int uCount;
	time_t tCurrTime;

	n++;
	uRnd |= n;
	time(&tCurrTime);
	for(uCount = 0; uCount < (n%256); uCount++)
	{
		if((uCount%2) == 0)
		{
			uRnd |= 0xAA873555;
		}
		if((uCount%3) == 0)
		{
			uRnd ^= 0xFFFFFFFF;
		}
		if((uCount%4) == 0)
		{
			uRnd <<= 1;
		}
		if((uCount%5) == 0)
		{
			uRnd ^= n;
		}
	}
	uRnd ^= tCurrTime;
	return uRnd;
}

BOOL IsBigger(UCHAR uc1, UCHAR uc2)
{
	if(!(uc1&0x80) && (uc2&0x80))
	{
		return TRUE;
	}
	if(!(uc1&0x80) && !(uc2&0x80))
	{
		return (uc1 > uc2);
	}
	if((uc1&0x80) && (uc2&0x80))
	{
		uc1 -= 1;
		uc1 = ~uc1;
		
		uc2 -= 1;
		uc2 = ~uc2;		
		
		return (uc1 < uc2);
	}
	return FALSE;
}

/*
BOOL RectHitRect(CRect r1, CRect r2)
{
	if(r2.iTop >= r1.iTop 
		&& r2.iLeft >= r1.iLeft 
		&& r2.iTop <= (r1.iTop+r1.iHeight) 
		&& r2.iLeft <= (r1.iLeft+r1.iWidth))
	{
		return TRUE;
	}
	
	if((r2.iTop+r2.iHeight) >= r1.iTop 
		&& r2.iLeft >= r1.iLeft 
		&& (r2.iTop+r2.iHeight) <= (r1.iTop+r1.iHeight) 
		&& r2.iLeft <= (r1.iLeft+r1.iWidth))
	{
		return TRUE;
	}
	
	if(r2.iTop >= r1.iTop 
		&& (r2.iLeft+r2.iWidth) >= r1.iLeft 
		&& r2.iTop <= (r1.iTop+r1.iHeight) 
		&& (r2.iLeft+r2.iWidth) <= (r1.iLeft+r1.iWidth))
	{
		return TRUE;
	}
	
	if((r2.iTop+r2.iHeight) >= r1.iTop  
		&& (r2.iLeft+r2.iWidth) >= r1.iLeft 
		&& (r2.iTop+r2.iHeight) <= (r1.iTop+r1.iHeight) 
		&& (r2.iLeft+r2.iWidth) <= (r1.iLeft+r1.iWidth))
	{
		return TRUE;
	}
	
	return FALSE;
}
*/

/*
int Complement(UCHAR ucData)
{
	if(ucData & 0x80)
	{
		ucData-=1;
		ucData = ~ucData;
	}
	return ucData;
}
*/
