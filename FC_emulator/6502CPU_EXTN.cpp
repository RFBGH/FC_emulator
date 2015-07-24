#include "6502CPU.h"
 
 void CPU6502::Push(UCHAR ucParam)
{
	USHORT usAddr;
	
	usAddr = m_rSP|0x0100;
	SetRamValueByAddr(ucParam, usAddr);
	Log("push[%04x]=%02x\n", usAddr, ucParam);
	
	m_rSP--;
}

UCHAR CPU6502::Pop()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	m_rSP++;
	usAddr = m_rSP|0x0100;
	
	ucParam = GetRamValueByAddr(usAddr);
	
	Log("pop[%04x]=%02x\n", usAddr, ucParam);
	
	return ucParam;	
}

//有效物理地址0x0000~0x07FF 2K
//其他地址为镜像
UCHAR CPU6502::GetRamValueByAddr(USHORT usAddr)
{
	
	UCHAR ucRet;

	//过滤有效地址
	if(usAddr < 0x2000)
	{	//物理地址
		
		usAddr &= 0x7FF;
		ucRet =  m_ram[usAddr];
	}else if(usAddr < 0x4000 && usAddr >= 0x2000)
	{	//PPU寄存器
		usAddr &= 0x7;
		ucRet = m_pPPU->ReadRegister(usAddr);

	}else if(usAddr == 0x8000){
	
		ucRet = m_rChageRomDst;
	}else if(usAddr == 0x8001){
	
		ucRet = m_rChageRomSrc;
	}else if(usAddr > 0x8001)
	{
		ucRet = m_rom[usAddr&0x7FFF];	
	}else if(usAddr >= 0x4016 && usAddr <= 0x4017)
	{
		//手柄1
		if(usAddr == 0x4016 && m_pFcInput != NULL)
		{
			ucRet = m_pFcInput->ReadRegister();
		}else
		{ 
			//ucRet = Random();
			ucRet = 0;
		}
	}
	else
	{
		ucRet = Random();
	}
	
	Log("Get ram[%04x] %02x\n", usAddr, ucRet);
	return ucRet;
}

void  CPU6502::SetRamValueByAddr(UCHAR ucValue, USHORT usAddr)
{
	//OpenDebug();

	Log("set ram[%04x] %02x\n", usAddr, ucValue);
	
	//过滤有效地址
	if(usAddr < 0x2000)
	{	//物理地址
		
		usAddr &= 0x7FF;
		m_ram[usAddr] = ucValue;
	}
	else if(usAddr < 0x4000 && usAddr >= 0x2000)
	{	//PPU寄存器
		usAddr &= 0x7;
		m_pPPU->WriteRegister(usAddr, ucValue);
		Log("m_rCtrl[%04x] %02x\n", usAddr, ucValue);
	}else if(usAddr >= 0x4016 && usAddr <= 0x4017)
	{
		//手柄1
		if(usAddr == 0x4016 && m_pFcInput != NULL)
		{
			m_pFcInput->WriteRegister(ucValue);
		}
	}else if(usAddr == 0x4014)
	{
		int i;
		USHORT usTmpAddr = ucValue << 8;
		for(i = 0; i < 256; i++)
		{
			if(m_pPPU)
			{
				m_pPPU->WriteSpriteRam(m_ram[usTmpAddr+i]);
			}
		}
	}else if(usAddr == 0x8000){
	
		m_rChageRomDst = ucValue;
	}else if(usAddr == 0x8001){
	
		m_rChageRomSrc = ucValue;

		int op = m_rChageRomDst&0x07;
		UCHAR* pRomDst = NULL;
		UCHAR* pFileSrc = NULL;
		int size;

		switch(op){
			
		case 0:
		case 1:

			break;

		case 2:
		case 3:
		case 4:
		case 5:
			
			pRomDst = &m_pPPU->m_ram[(op-2)];
			pFileSrc = nesFile.m_vrom+m_rChageRomSrc*0x800;
			size = 2*1024;
			break;

		case 6:
		case 7:

			pRomDst = &m_rom[0x2000*(op&0x01)];
			pFileSrc = nesFile.m_rom+m_rChageRomSrc*0x2000;
			size = 8*1024;
			break;

		default:

			break;
		}

		MemCpy(pRomDst, pFileSrc, size);
	}else
	{
		
	}
}

UCHAR CPU6502::GetNextOperate()
{
	UCHAR ucParam;
	
#ifdef _DEBUG
	static unsigned char suczOp[256];
	static BOOL isFirst = TRUE;
	
	if(isFirst == TRUE)
	{
		MemSet(suczOp, 0, sizeof(suczOp));
		isFirst = FALSE;
	}
#endif
	
	m_rPC++;
	ucParam = m_rom[m_rPC&0x7FFF];
	
#ifdef _DEBUG
	suczOp[ucParam] = 1;
#endif

	Log("\n");
	Log("OP[%02x] PC[%04x] PSW[%02x] SP[%02x] A[%02x] X[%02x] Y[%02x]\n",
			ucParam, m_rPC, m_rPSW, m_rSP, m_rA, m_rX, m_rY);
	
	return ucParam;
}

UCHAR CPU6502::GetOperateParam8()
{
	UCHAR ucParam;
	
	m_rPC++;

	ucParam = m_rom[m_rPC&0x7FFF];

	return ucParam;
}

USHORT CPU6502::GetOperateParam16()
{
	USHORT usParam;
	UCHAR  ucParam;
	
	m_rPC++;
	//32K ROM
	usParam = m_rom[m_rPC&0x7FFF];
		
	m_rPC++;
	//32K ROM
	ucParam = m_rom[m_rPC&0x7FFF];	
	
	usParam |= ucParam << 8;
	return usParam;
}

void CPU6502::UpdateRom(UCHAR* pucRom, USHORT usSize, int iRomType)
{
	if(pucRom == NULL)
	{
		return;
	}
	
	if(usSize > 32*1024)
	{
		usSize = 32*1024;
	}
	
	MemCpy(m_rom, pucRom, usSize);
	
	//更新中断地址。
	//32k ROM
	m_isrBrkIrqAddr = (USHORT)(m_rom[0x7FFE] | (m_rom[0x7FFF]<<8));
	m_isrNmiAddr = (USHORT)(m_rom[0x7FFA] | (m_rom[0x7FFB]<<8));
	m_isrResetAddr = (USHORT)(m_rom[0x7FFC] | (m_rom[0x7FFD]<<8));	

	m_rPC = m_isrResetAddr-1;
	
	Log("imn[%04x] reset[%04x] brk[%04x]\n",m_isrNmiAddr, m_isrResetAddr, m_isrBrkIrqAddr);
}

//提供模拟硬件中断功能

void CPU6502::EnterIsr()
{
	Push(m_rPC>>8);
	Push(m_rPC);
	Push(m_rPSW);	   
}

void CPU6502::IsrReset()
{
	Log("enter reset ISR\n");
	
	m_ErrCode = CPU6502_ERR_NONE;
	
	m_rA = 0;
	m_rX = 0;
	m_rY = 0;
	m_rSP = 0xFF;
	m_rPSW = 0x00;
	
	m_rPC = m_isrResetAddr-1;
	
	m_pPPU->Reset();
}

void CPU6502::IsrBrkIrq()
{
	while(m_IsrLock);
	m_StrLock = 1;
 
	Log("enter BrkIrq ISR\n");
	EnterIsr();
	SetIBit(1);

	m_StrLock = 0;
	m_rPC = m_isrBrkIrqAddr-1;	
}

void CPU6502::IsrNmi()
{
	while(m_IsrLock);
	m_StrLock = 1;

	Log("enter nmi ISR\n");
	EnterIsr();

	m_StrLock = 0;
	m_rPC = m_isrNmiAddr-1;	
}

BOOL CPU6502::IsNegative(UCHAR ucParam)
{
	Log("IsNegative ucParam[0x%02x]\n", ucParam);
	if(ucParam & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPU6502::IsEqualZero(UCHAR ucParam)
{
	Log("IsEqualZero ucParam[0x%02x]\n", ucParam);
	return (ucParam == 0x00);
}

/*
	7 6 5 4 3 2 1 0
	N V E B D I Z C
*/
void CPU6502::SetPswBit(int iType)
{
	if(iType < 0 || iType > 7)
	{
		return;
	}
	m_rPSW |= 0x01<<iType;
}

void CPU6502::ClrPswBit(int iType)
{

	if(iType < 0 || iType > 7)
	{
		return;
	}
	m_rPSW &= ~(0x01<<iType);
}

BOOL CPU6502::IsSetPswBit(int iType)
{
	if(iType < 0 || iType > 7)
	{
		return FALSE;
	}
	if(m_rPSW & (0x01<<iType))
	{
		return TRUE;
	}
	return FALSE;
}

//set C bit
void CPU6502::SetCBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set C Bit.\n");
		SetPswBit(0);		
	}else
	{
		Log("Clr C Bit\n");
		ClrPswBit(0);		
	}

}

//check C bit set.
BOOL CPU6502::IsSetCBit()
{
	Log("Check C Bit\n");
	return IsSetPswBit(0);
}

//Set Z bit
void CPU6502::SetZBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set Z Bit\n");
		SetPswBit(1);		
	}else
	{
		Log("Clr Z Bit\n");
		ClrPswBit(1);		
	}

}

//check Z bit set.
BOOL CPU6502::IsSetZBit()
{
	Log("Check Z Bit\n");
	return IsSetPswBit(1);
}

//set I bit.
void CPU6502::SetIBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set I Bit\n");
		SetPswBit(2);		
	}else
	{
		Log("Clr I Bit\n");
		ClrPswBit(2);		
	}

}

//check I bit set.
BOOL CPU6502::IsSetIBit()
{
	Log("Check I Bit\n");
	return IsSetPswBit(2);
}

//set D bit.
void CPU6502::SetDBit(BOOL bSet)
{
	Log("Set D Bit\n");
	if(bSet)
	{
		Log("Set I Bit\n");
		SetPswBit(3);		
	}else
	{
		Log("Clr I Bit\n");
		ClrPswBit(3);		
	}
}

//check D bit set.
BOOL CPU6502::IsSetDBit()
{
	Log("Check D Bit\n");
	return IsSetPswBit(3);
}

//set B bit.
void CPU6502::SetBBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set B Bit\n");
		SetPswBit(4);
	}else
	{
		Log("Clr B Bit\n");
		ClrPswBit(4);	
	}
}

//check B bit set.
BOOL CPU6502::IsSetBBit()
{
	Log("Check B Bit\n");
	return IsSetPswBit(4);
}

//set V bit.
void CPU6502::SetVBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set V Bit\n");
		SetPswBit(6);	
	}else
	{
		Log("Clr V Bit\n");
		ClrPswBit(6);
	}

}

//check V bit.
BOOL CPU6502::IsSetVBit()
{
	Log("Check V Bit\n");
	return IsSetPswBit(6);
}

//set N bit.
void CPU6502::SetNBit(BOOL bSet)
{
	if(bSet)
	{
		Log("Set N Bit\n");
		SetPswBit(7);		
	}else
	{
		Log("Clr N Bit\n");
		ClrPswBit(7);	
	}

}

//check N bit set.
BOOL CPU6502::IsSetNBit()
{
	Log("Check N Bit\n");
	return IsSetPswBit(7);
}

void CPU6502::SelectInput(FcInput* fcInput)
{
	m_pFcInput = fcInput;
}

void CPU6502::SelectPPU(PPU* pPPU)
{
	m_pPPU = pPPU;
}

void CPU6502::Reset()
{
	m_pPPU = NULL;

	m_ErrCode = CPU6502_ERR_NONE;
	
	m_IsrLock = 1;
	m_StrLock = 0;

	m_rA = 0;
	m_rX = 0;
	m_rY = 0;
	m_rSP = 0xFF;
	//m_rPC = 0x8000;
	m_rPC = m_isrResetAddr-1;
	m_rPSW = 0x00;
	
	m_isrNmiAddr = 0x0000;
	m_isrResetAddr = 0x0000;
	m_isrBrkIrqAddr = 0x0000;
	
	MemSet(m_ram, 0, sizeof(m_ram));
	MemSet(m_rom, 0, sizeof(m_rom));
	MemSet(m_rPPU, 0, sizeof(m_rPPU));
	MemSet(m_rAPU, 0, sizeof(m_rAPU));
	MemSet(m_rInput, 0, sizeof(m_rInput));
	m_rOAM = 0x00;
}

CPU6502::CPU6502()
{
	Reset();
} 

CPU6502::~CPU6502()
{
	Reset();
}
