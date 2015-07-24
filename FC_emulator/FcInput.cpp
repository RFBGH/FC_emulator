#include "FcInput.h"

void FcInput::Reset()
{
	m_shiftCnt = 0;
	//m_curInput = 0;
	m_rCtrl = 0;
}

FcInput::FcInput()
{
	m_curInput = 0;
	Reset();
}

FcInput::~FcInput()
{
	Reset();
}


void FcInput::WriteRegister(UCHAR ucCtrl)
{
	static int iCnt = 0;
	
	if(ucCtrl & 0x01)
	{
		iCnt = 1;
		Reset();
	}else
	{
		if(iCnt == 1)
		{
			iCnt = 0;
			Reset();
		}
		//Çå³ý
		//m_curInput = 0;
	}
}

UCHAR FcInput::ReadRegister()
{

	if((m_shiftCnt < 8)
		&&((m_curInput >> (7-m_shiftCnt))&0x01))
	{
		m_rCtrl |= 0x01;
	}else
	{
		m_rCtrl &= 0xFE;
	}
	m_shiftCnt++;
	
	if(m_shiftCnt == 24)
	{
		m_shiftCnt = 0;
	}

	if(m_shiftCnt == 8)
	{
		m_curInput = 0;
	}
	
	return m_rCtrl;
}

void FcInput::SetInputValue(UCHAR ucValue)
{
	m_curInput = ucValue;
}