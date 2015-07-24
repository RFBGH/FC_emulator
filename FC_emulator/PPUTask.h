#ifndef __PPUTASK_H__
#define __PPUTASK_H__

#include "stdafx.h"
#include "Public.h"
#include "6502CPU.h"
#include "PPU.h"

class CPPUTask
{
public:

	static UINT WaitForTaskRollFun(void* pParam);

	CWinThread* m_pThread;
	HANDLE m_event;

	PPU*	 m_pPPU;
	CPU6502* m_pCPU;
	BOOL     m_isRun;

	CPPUTask();
	~CPPUTask();

	BOOL IsRun();

	void StartTask(PPU* pPPU, CPU6502* pCPU);

	void Suspend();
	void Resume();
};

extern CPPUTask ppuTask;

#endif