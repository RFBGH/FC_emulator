
#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include <stdarg.h>
#include <stdio.h>

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef FALSE
#define FALSE (1==0)
#endif

#define COLOR32			UINT
#define FormatR(R)      (COLOR32)((R<<24) & 0xFF000000)
#define FormatG(G)		(COLOR32)((G<<16) & 0x00FF0000)	
#define FormatB(B)		(COLOR32)((B<<08) & 0x0000FF00)	
#define FormatA(A)		(COLOR32)((A<<00) & 0x000000FF)	

#define GetR(rgba)      (COLOR32)((rgba >> 24) & 0x000000FF)
#define GetG(rgba)      (COLOR32)((rgba >> 16) & 0x000000FF)
#define GetB(rgba)      (COLOR32)((rgba >> 08) & 0x000000FF)
#define GetA(rgba)      (COLOR32)((rgba >> 00) & 0x000000FF)

#define RGBA(R,G,B,A)	(COLOR32)(FormatR(R) | FormatR(G) | FormatR(B) | FormatR(A))  

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 240

extern UINT gScreenBuf[300*300];
extern COLOR32 tFcColorTable[64+5];

void SetScreenBuf(int x, int y, COLOR32 color);
COLOR32 GetColor(int x, int y);

void MemSet(void* pDst, int iVal, int iSize);
void MemCpy(void* pDst, void* pSrc, int iSize);

int Random(void);

void Log(char* pFormat, ...);

BOOL IsBigger(UCHAR uc1, UCHAR uc2);

/*
typedef struct _Rect
{
	int iTop;
	int iLeft;
	int iWidth;
	int iHeight;
}CRect, *PRect;

BOOL RectHitRect(CRect r1, CRect r2);
*/

//typedef void (*WaitForTaskRollFun)(void* pParam);

//typedef int (*PFCpuRun)();
//typedef void (*PFppuPrint)();

extern UINT guDebugFlag;
#define OpenDebug() do{guDebugFlag = 1;}while(0)
#define CloseDebug() do{guDebugFlag = 0;}while(0)

#endif