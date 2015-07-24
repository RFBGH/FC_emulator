#include "6502CPU.h"


//instruction process.
void CPU6502::HA1_DoLdaChageIndirectAddrX()
{
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	UCHAR  ucParam;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("LDA ($%02x, 0x%02x)\n", usIndrtAddr, m_rX);
	
	usIndrtAddr += m_rX;
	
	ucParam = GetRamValueByAddr(usIndrtAddr);
	usDstAddr = ucParam;
	
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam<<8);
	
	m_rA = GetRamValueByAddr(usDstAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}


void CPU6502::hA5_DoLdaZeroPageAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	m_rA = GetRamValueByAddr(usAddr);
	
	Log("LDA $%02x\n", usAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HA9_DoLdaDirectData()
{
	m_rA = GetOperateParam8();
	
	Log("LDA $#%02x\n", m_rA);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HAD_DoLdaDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDA $%04x\n", usAddr);
	
	m_rA = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HB1_DoLdaIndirectChageAddrY()
{
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	UCHAR  ucParam;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("LDA ($%02x), %02x\n", usIndrtAddr, m_rY);
	
	ucParam = GetRamValueByAddr(usIndrtAddr);
	usDstAddr = ucParam;
	
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	usDstAddr += m_rY;
	
	m_rA = GetRamValueByAddr(usDstAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HB5_DoLdaZeroPageChageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LDA $%02x, %02x\n", usAddr, m_rX);
	
	usAddr += m_rX;
	
	m_rA = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HB9_DoLdaDirectChageAddrY()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDA $%04x, %02x\n", usAddr, m_rY);
	
	usAddr += m_rY;
	
	m_rA = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HBD_DoLdaDirectChageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDA $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	m_rA = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rA));
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::HA2_DoLdxDirectData()
{
	m_rX = GetOperateParam8();
	
	Log("LDX #$%02x\n", m_rX);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));
}

void CPU6502::HA6_DoLdxZeroPageAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LDX $%02x\n", usAddr);
	m_rX = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));
}

void CPU6502::HAE_DoLdxDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDX $%04x\n", usAddr);
	m_rX = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));
}

void CPU6502::HB6_DoLdxZeroPageChageAddrY()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	Log("LDX @%02x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	
	m_rX = GetRamValueByAddr(usAddr);	
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));
}

void CPU6502::HBE_DoLdxDirectChageAddrY()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDX @%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	
	m_rX = GetRamValueByAddr(usAddr);		
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));
}
	

void CPU6502::HA0_DoLdyDirectData()
{
	m_rY = GetOperateParam8();
	
	Log("LDY #@%02x\n", m_rY);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::HA4_DoLdyZeroPageAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LDY @%02x\n", usAddr);
	m_rY = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));		
}

void CPU6502::HAC_DoLdyDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDY @%04x\n", usAddr);
	m_rY = GetRamValueByAddr(usAddr);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::HB4_DoLdyZeroPageChageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LDY @%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	m_rY = GetRamValueByAddr(usAddr);	
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::HBC_DoLdyDirectChageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LDY @%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	m_rY = GetRamValueByAddr(usAddr);		
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::H81_DoStaChageIndirectAddrX()
{
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	UCHAR  ucParam;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("STA ($%02x, %02x)\n", usIndrtAddr, m_rX);
	
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam =  GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	SetRamValueByAddr(m_rA, usDstAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}
void CPU6502::H85_DoStaZeroPageAddr()
{
	USHORT usAddr;
	usAddr = GetOperateParam8();
	
	Log("STA $%02x\n", usAddr);
	
	SetRamValueByAddr(m_rA, usAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}

void CPU6502::H8D_DoStaDirectAddr()
{
	USHORT usAddr;
	usAddr = GetOperateParam16();
	
	Log("STA $%04x\n", usAddr);
	
	SetRamValueByAddr(m_rA, usAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}

void CPU6502::H91_DoStaIndirectChageAddrY()
{
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	UCHAR  ucParam;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("STA ($%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam   = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	usDstAddr += m_rY;
	
	SetRamValueByAddr(m_rA, usDstAddr);
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}

void CPU6502::H95_DoStaZeroPageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("STA $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	SetRamValueByAddr(m_rA, usAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}	

void CPU6502::H99_DoStaDirectAddrY()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("STA $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	SetRamValueByAddr(m_rA, usAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}

void CPU6502::H9D_DoStaDirectAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("STA $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	SetRamValueByAddr(m_rA, usAddr);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
	
}

void CPU6502::H86_DoStxZeroPageAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("STX $%02x\n", usAddr);
	SetRamValueByAddr(m_rX, usAddr);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));	
}

void CPU6502::H8E_DoStxDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("STX $%04x\n", usAddr);
	SetRamValueByAddr(m_rX, usAddr);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));	
}

void CPU6502::H96_DoStxZeroPageAddrY()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("STX $%02x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	SetRamValueByAddr(m_rX, usAddr);
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));	
}

void CPU6502::H84_DoStyZeroPageAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("STY $%02x\n", usAddr);
	SetRamValueByAddr(m_rY, usAddr);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::H8C_DoStyDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("STY $%04x\n", usAddr);
	SetRamValueByAddr(m_rY, usAddr);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));		
}

void CPU6502::H94_DoStyZeroPageAddrX()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("STY $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	SetRamValueByAddr(m_rY, usAddr);
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));
}

void CPU6502::HAA_DoTax()
{
	Log("TAX %02x, %02x\n", m_rA, m_rX);
	m_rX = m_rA;
}

void CPU6502::H8A_DoTxa()
{
	Log("TXA %02x, %02x\n", m_rX, m_rA);
	m_rA = m_rX;	
}

void CPU6502::HA8_DoTay()
{
	Log("TAY %02x, %02x\n", m_rA, m_rY);
	m_rY = m_rA;	
}

void CPU6502::H98_DoTya()
{
	Log("TYA %02x, %02x\n", m_rY, m_rA);
	m_rA = m_rY;		
}

void CPU6502::HBA_DoTsx()
{
	Log("TSX %02x, %02x\n", m_rSP, m_rX);
	m_rX = m_rSP;	
}

void CPU6502::H9A_DoTxs()
{
	Log("TXS %02x, %02x\n", m_rX, m_rSP);
	m_rSP = m_rX;	
}

void CPU6502::H61_DoAdcChageIndirectAddrX()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("ADC ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	usParam1 = GetRamValueByAddr(usDstAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())	//carry bit.
	{
		usParam2 += 1;
	} 
	
	usReslt = usParam1+usParam2;
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H65_DoAdcZeroPageAddr()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	
	usAddr = GetOperateParam8();
	
	Log("ADC $%02x\n", usAddr);
	usParam1 = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())
	{
		usParam2 += 1;
	}
	usReslt = usParam1 + usParam2;
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H69_DoAdcDirectData()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;	
	
	usParam1 = GetOperateParam8();
	
	Log("ADC #$%02x\n", usParam1);
	usParam2 = m_rA;
	
	if(IsSetCBit())
	{
		usParam2 += 1;
	}
	usReslt = usParam1 + usParam2;
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
	
}
void CPU6502::H6D_DoAdcDirectAddr()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;	
	
	usAddr = GetOperateParam16();
	Log("ADC $%04x\n", usAddr);
	usParam1 = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())
	{
		usParam2 += 1;
	}
	usReslt = usParam1 + usParam2;
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H71_DoAdcIndirectChageAddrY()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("ADC ($%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	usDstAddr += m_rY;
	
	usParam1 = GetRamValueByAddr(usDstAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())	//carry bit.
	{
		usParam2 += 1;
	}
	
	usReslt = usParam1+usParam2;
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H75_DoAdcZeroPageAddrX()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
		
	usAddr = GetOperateParam8();
	
	Log("ADC $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	usParam1 = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())	//carry bit.
	{
		usParam2 += 1;
	}
	
	usReslt = usParam1+usParam2;
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H79_DoAdcDirectAddrY()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
		
	usAddr = GetOperateParam16();
	
	Log("ADC $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	
	usParam1 = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())	//carry bit.
	{
		usParam2 += 1;
	}
	
	usReslt = usParam1+usParam2;
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H7D_DoAdcDirectAddrX()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
		
	usAddr = GetOperateParam16();
	
	Log("ADC $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	usParam1 = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(IsSetCBit())	//carry bit.
	{
		usParam2 += 1;
	}
	
	usReslt = usParam1+usParam2;
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit(usReslt&0x0100);
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));			
}

void CPU6502::HE1_DoSbcChageIndirectAddrX()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("SBC ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	ucParam = GetRamValueByAddr(usDstAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}
void CPU6502::HE5_DoSbcZeroPageAddr()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("SBC $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));

	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}
void CPU6502::HE9_DoSbcDirectData()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;	
	UCHAR  ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("SBC #$%02x\n", ucParam);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
		
}

void CPU6502::HED_DoSbcDirectAddr()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;	
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	Log("SBC $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));			
}

void CPU6502::HF1_DoSbcIndirectChageAddrY()
{
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("SBC ($%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	usDstAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usDstAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::HF5_DoSbcZeroPageAddrX()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
		
	usAddr = GetOperateParam8();
	
	Log("SBC $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	ucParam = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::HFD_DoSbcDirectAddrX()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
		
	usAddr = GetOperateParam16();
	
	Log("SBC $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	
	ucParam = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
		
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));			
}

void CPU6502::HF9_DoSbcDirectAddrY()
{
	USHORT usAddr;
	USHORT usParam1;
	USHORT usParam2;
	USHORT usReslt;
	UCHAR  ucParam;
		
	usAddr = GetOperateParam16();
	
	Log("SBC $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usAddr);
	usParam2 = m_rA;
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	usParam1 = ucParam;
	if(ucParam == 0)
	{
		usParam1 |= 0x100;
	}
	
	usReslt = usParam2 + usParam1;
	
	if(!IsSetCBit())	//carry bit.
	{
		usReslt += 0xFF;
	}
	
	m_rA = (UCHAR)(usReslt & 0xFF);
	
	SetVBit(((usParam1^usReslt)&0x80) && !((usParam1^usParam2)&0x80));
	
	SetCBit((usReslt&0x0100));
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));				
}

void CPU6502::HE6_DoIncZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("INC $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam++;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::HEE_DoIncDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("INC $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam++;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::HF6_DoIncZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("INC $%02x %0x2x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam++;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::HFE_DoIncDirectAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("INC $%04x %0x2x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam++;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::HC6_DoDecZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("DEC $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam--;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::HCE_DoDecDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("DEC $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam--;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::HD6_DoDecZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("DEC $%02x %0x2x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam--;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::HDE_DoDecDirectAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("DEC $%04x %0x2x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam--;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));		
}

void CPU6502::HE8_DoInx()
{
	m_rX++;
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));		
}

void CPU6502::HCA_DoDex()
{
	m_rX--;
	
	SetNBit(IsNegative(m_rX));
	SetZBit(IsEqualZero(m_rX));		
}

void CPU6502::HC8_DoIny()
{
	m_rY++;
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::H88_DoDey()
{
	m_rY--;
	
	SetNBit(IsNegative(m_rY));
	SetZBit(IsEqualZero(m_rY));	
}

void CPU6502::H21_DoAndChageIndirectAddrX()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("AND ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H25_DoAndZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("AND $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H29_DoAndDirectData()
{
	UCHAR  ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("AND $%02x\n", ucParam);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H2D_DoAndDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("AND $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H31_DoAndIndirectChageAddrY()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("AND (%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= ucParam << 8;
	usDstAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H35_DoAndZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("AND $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H39_DoAndDirectAddrY()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("AND $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
	
}
void CPU6502::H3D_DoAndDirectAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("AND $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA &= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H01_DoOraChageIndirectAddrX()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("ORA ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H05_DoOraZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("ORA $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H09_DoOraDirectData()
{
	UCHAR  ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("ORA #%02x\n", ucParam);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H0D_DoOraDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("ORA $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H11_DoOraIndirectChageAddrY()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("ORA (%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= ucParam << 8;
	usDstAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H15_DoOraZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("ORA $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H19_DoOraDirectAddrY()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("ORA $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H1D_DoOraDirectAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("ORA $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA |= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));			
}

void CPU6502::H41_DoEorChageIndirectAddrX()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("EOR ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H45_DoEorZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("EOR $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H49_DoEorDirectData()
{
	UCHAR  ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("EOR $%02x\n", ucParam);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H4D_DoEorDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("EOR $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H51_DoEorIndirectChageAddrY()
{
	UCHAR  ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("EOR (%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= ucParam << 8;
	usDstAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usDstAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H55_DoEorZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("EOR $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H59_DoEorDirectAddrY()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("EOR $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));		
}

void CPU6502::H5D_DoEorDirectAddrX()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("EOR $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	m_rA ^= ucParam;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));			
}

void CPU6502::H18_DoClc()
{
	SetCBit(0);
}

void CPU6502::H38_DoSec()
{
	SetCBit(1);
}

void CPU6502::HD8_DoCld()
{
	SetDBit(0);
}

void CPU6502::HF8_DoSed()
{
	SetDBit(1);
}

void CPU6502::HB8_DoClv()
{
	SetVBit(0);
}

void CPU6502::H58_DoCli()
{
	SetIBit(0);
}

void CPU6502::H78_DoSei()
{
	SetIBit(1);
}

void CPU6502::HC1_DoCmpChageIndirectAddrX()
{
	UCHAR ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("CMP ($%02x, %02x)\n", usIndrtAddr, m_rX);
	usIndrtAddr += m_rX;
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= (ucParam << 8);
	
	ucParam = GetRamValueByAddr(usDstAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;

	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);
	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HC5_DoCmpZeroPageAddr()
{
	USHORT usAddr; 
	UCHAR ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("CMP $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HC9_DoCmpDirectData()
{
	UCHAR  ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("CMP $%02x\n", ucParam);

	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HCD_DoCmpDirectAddr()
{
	USHORT  usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("CMP $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HD1_DoCmpIndirectChageAddrY()
{
	UCHAR ucParam;
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	
	usIndrtAddr = GetOperateParam8();
	
	Log("CMP (%02x), %02x\n", usIndrtAddr, m_rY);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= ucParam << 8;
	usDstAddr += m_rY;
	
	ucParam = GetRamValueByAddr(usDstAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HD5_DoCmpZeroPageAddrX()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("CMP $%02x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);

	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HD9_DoCmpDirectAddrY()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("CMP $%04x, %02x\n", usAddr, m_rY);
	usAddr += m_rY;
	ucParam = GetRamValueByAddr(usAddr);

	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HDD_DoCmpDirectAddrX()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("CMP $%04x, %02x\n", usAddr, m_rX);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rA + ucParam;
	if(ucParam == 0)
	{
		usReslt += 0x100;
	}

	SetCBit(usReslt&0x100);	
	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HE0_DoCpxDirectData()
{
	UCHAR ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("CPX #$%02x\n", ucParam);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rX + ucParam;

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
	
}
void CPU6502::HE4_DoCpxZeroPageAddr()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("CPX $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rX + ucParam;

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HEC_DoCpxDirectAddr()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("CPX $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rX + ucParam;

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));
	
	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HC0_DoCpyDirectData()
{
	UCHAR ucParam;
	
	ucParam = GetOperateParam8();
	
	Log("CPY #$%02x\n", ucParam);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rY + ucParam;

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));

	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HC4_DoCpyZeroPageAddr()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("CPY $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);

	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1;
	}
	
	USHORT usReslt = m_rY + ucParam;

	SetCBit(usReslt&0x100);	

	SetNBit(IsNegative(usReslt));

	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::HCC_DoCpyDirectAddr()
{
	USHORT usAddr;
	UCHAR ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("CPY $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	if(ucParam & 0x80)
	{
		ucParam -= 1;
		ucParam = ~ucParam;
	}else
	{
		ucParam = ~ucParam;
		ucParam += 1; 
	}
	
	USHORT usReslt = m_rY + ucParam;  

	SetCBit(usReslt&0x100);	

	
	SetNBit(IsNegative(usReslt));

	SetZBit(IsEqualZero(usReslt));
}

void CPU6502::H0A_DoAslAAddr()
{
	Log("ASL A\n");
	
	SetCBit(m_rA & 0x80);
	
	m_rA <<= 1;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));	
}

void CPU6502::H06_DoAslZeroPageAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("ASL $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H0E_DoAslDirectAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("ASL $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H16_DoAslZeroPageAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("ASL $%02x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H1E_DoAslDirectAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("ASL $%04x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));		
}

void CPU6502::H4A_DoLsrAAddr()
{
	Log("LSR A\n");
	
	SetCBit((m_rA & 0x01));
	
	m_rA >>= 1;
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H46_DoLsrZeroPageAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LSR $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H4E_DoLsrDirectAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LSR $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H56_DoLsrZeroPageAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam8();
	
	Log("LSR $%02x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H5E_DoLsrDirectAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	
	Log("LSR $%04x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H2A_DoRolAAddr()
{
	BOOL bCBitSet;
	Log("ROL A\n");

	bCBitSet = IsSetCBit();
	
	SetCBit((m_rA & 0x80));
	
	m_rA <<= 1;
	if(bCBitSet)
	{
		m_rA |= 0x01;
	}
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H26_DoRolZeroPageAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam8();
	
	Log("ROL $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	if(bCBitSet)
	{
		ucParam |= 0x01;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H2E_DoRolDirectAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam16();
	
	Log("ROL $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	if(bCBitSet)
	{
		ucParam |= 0x01;
	}
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H36_DoRolZeroPageAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam8();
	
	Log("ROL $%02x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	if(bCBitSet)
	{
		ucParam |= 0x01;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H3E_DoRolDirectAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam16();
	
	Log("ROL $%04x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x80));
	
	ucParam <<= 1;
	if(bCBitSet)
	{
		ucParam |= 0x01;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H6A_DoRorAAddr()
{
	BOOL bCBitSet;
	Log("ROR A\n");

	bCBitSet = IsSetCBit();
	
	SetCBit((m_rA & 0x01));
	
	m_rA >>= 1;
	if(bCBitSet)
	{
		m_rA |= 0x80;
	}
	
	SetNBit(IsNegative(m_rA));
	
	SetZBit(IsEqualZero(m_rA));
}

void CPU6502::H66_DoRorZeroPageAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam8();
	
	Log("ROR $%02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	if(bCBitSet)
	{
		ucParam |= 0x80;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H6E_DoRorDirectAddr()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam16();
	
	Log("ROR $%04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	if(bCBitSet)
	{
		ucParam |= 0x80;
	}
	SetRamValueByAddr(ucParam, usAddr);	
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H76_DoRorZeroPageAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam8();
	
	Log("ROR $%02x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));

	ucParam >>= 1;
	if(bCBitSet)
	{ 
		ucParam |= 0x80;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H7E_DoRorDirectAddrX()
{
	UCHAR ucParam;
	USHORT usAddr;
	BOOL bCBitSet;
	
	bCBitSet = IsSetCBit();
	usAddr = GetOperateParam16();
	
	Log("ROL $%04x X\n", usAddr);
	usAddr += m_rX;
	ucParam = GetRamValueByAddr(usAddr);
	
	SetCBit((ucParam & 0x01));
	
	ucParam >>= 1;
	if(bCBitSet)
	{
		ucParam |= 0x80;
	}
	SetRamValueByAddr(ucParam, usAddr);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));	
}

void CPU6502::H48_DoPha()
{
	Log("Push A\n");
	
	Push(m_rA);
}

void CPU6502::H68_DoPla()
{
	Log("Pop A");
	
	m_rA = Pop();
}

void CPU6502::H28_DoPlp()
{
	Log("Pop PSW");
	
	m_rPSW = Pop();
	
}

void CPU6502::H08_DoPhp()
{
	Log("Push PSW");
	
	Push(m_rPSW);
}

void CPU6502::H4C_DoJmpDirectAddr()
{
	USHORT usAddr;
	
	usAddr = GetOperateParam16();
	Log("JMP %04x\n", usAddr);
	
	m_rPC = usAddr-1;
}

void CPU6502::H5C_DoJmpIndirectAddr()
{
	USHORT usIndrtAddr;
	USHORT usDstAddr;
	UCHAR  ucParam;
	
	usIndrtAddr = GetOperateParam16();
	
	Log("JMP (%04x)\n", usIndrtAddr);
	usDstAddr = GetRamValueByAddr(usIndrtAddr);
	ucParam = GetRamValueByAddr(usIndrtAddr+1);
	usDstAddr |= ucParam << 8;
	
	m_rPC = usDstAddr-1;
}

void CPU6502::HF0_DoBeq()
{
	UCHAR ucParam;
	
	Log("BEQ ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(!IsSetZBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{	//²¹Âë
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}
}

void CPU6502::HD0_DoBne()
{
	UCHAR ucParam;
	
	Log("BNE ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	
	if(IsSetZBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}	
}

void CPU6502::HB0_DoBcs()
{
	UCHAR ucParam;
	
	Log("BCS ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(!IsSetCBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}		
}

void CPU6502::H90_DoBcc()
{
	UCHAR ucParam;
	
	Log("BCC ");
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(IsSetCBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}		
}

void CPU6502::H30_DoBmi()
{
	UCHAR ucParam;
	
	Log("BMI ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(!IsSetNBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}		
}

void CPU6502::H10_DoBpl()
{
	UCHAR ucParam;
	
	Log("BPL ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(IsSetNBit())
	{
		return;
	}

	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}		
}

void CPU6502::H70_DoBvs()
{
	UCHAR ucParam;
	
	Log("BVS ");
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	if(!IsSetVBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}		
}

void CPU6502::H50_DoBvc()
{
	UCHAR ucParam;
	
	ucParam = GetOperateParam8();
	Log("%02x \n", ucParam);
	
	Log("BVC ");
	if(IsSetVBit())
	{
		return;
	}
	
	if(ucParam&0x80)
	{
		if(ucParam != 0x80)
		{
			//ucParam &= 0x7F;
			ucParam -= 1;
			ucParam = ~ucParam;
		}
		m_rPC -= ucParam;
	}else
	{
		m_rPC += ucParam;
	}	
}


void CPU6502::H20_DoJsr()
{
	USHORT usParam;
	
	usParam = GetOperateParam16();
	Log("JSR %04x\n", usParam);
	
	Push(m_rPC>>8);
	Push((UCHAR)(m_rPC&0xFF));
	
	m_rPC = usParam-1;
}

void CPU6502::H60_DoRts()
{
	UCHAR ucParam;
	
	m_rPC = Pop();
	ucParam = Pop();
	m_rPC |= ucParam << 8;
	
	Log("RTS %04x\n", m_rPC);
}

void CPU6502::H24_BitZeroPageAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam8();
	
	Log("BIT %02x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam &= m_rA;
	
	SetVBit((ucParam & 0x40));
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H2C_BitDirectAddr()
{
	USHORT usAddr;
	UCHAR  ucParam;
	
	usAddr = GetOperateParam16();
	
	Log("BIT %04x\n", usAddr);
	ucParam = GetRamValueByAddr(usAddr);
	
	ucParam &= m_rA;
	
	SetVBit(ucParam & 0x40);
	
	SetNBit(IsNegative(ucParam));
	
	SetZBit(IsEqualZero(ucParam));
}

void CPU6502::H00_DoBrk()
{
	EnterIsr();
	
	SetBBit(1);
	SetIBit(1);
	
	m_rPC = m_isrBrkIrqAddr;
}

void CPU6502::H40_DoRti()
{
	UCHAR ucParam;
	m_rPSW = Pop();
	m_rPC = Pop();
	ucParam = Pop();
	m_rPC |= ucParam << 8;
}

void CPU6502::HEA_DoNop()
{
	//nop
}

//TODO...


