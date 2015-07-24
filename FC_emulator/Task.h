#ifndef __TASK_H__
#define __TASK_H__

#include "stdafx.h"
#include "Public.h"
#include "6502CPU.h"
#include "PPU.h"

class CTask
{
public:

	static UINT WaitForTaskRollFun(void* pParam);

	CWinThread* m_pThread;
	HANDLE m_event;

	UINT     m_count;
	CPU6502* m_pCpu;
	BOOL     m_isRun;

	CTask();
	~CTask();

	BOOL IsRun();

	void StartTask(CPU6502* pCpu);
		
	void Suspend();
	void Resume();
};

extern CTask task;

#endif