#ifndef __INPUT_H__
#define __INPUT_H__

#include "Public.h"

//ģ���������豸
class FcInput
{

public:
	UCHAR m_rCtrl;
	UCHAR m_curInput;
	UINT  m_shiftCnt;
	
	void Reset();
	FcInput();
	~FcInput();
	
	void WriteRegister(UCHAR ucCtrl);
	UCHAR ReadRegister();

	void SetInputValue(UCHAR ucValue);
};

#endif
