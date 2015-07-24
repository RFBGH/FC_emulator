#include "PPUTask.h"

CPPUTask ppuTask;


UINT CPPUTask::WaitForTaskRollFun (void* pParam)
{
	CPPUTask* pTask = (CPPUTask*)pParam;
	int iRow;
	int iInstr;

	WaitForSingleObject(pTask->m_event,INFINITE);	//挂起自身
	pTask->m_isRun = TRUE;

	while(TRUE)
	{
		
		if(!pTask->m_pPPU || !pTask->m_pCPU)
		{
			continue;
		}
		
		pTask->m_pPPU->UpdateScreen();
		
		for(iRow = 0; iRow < 296/*312*/; iRow++)
		{
			for(iInstr = 0; iInstr < 114; iInstr++)
			{
				pTask->m_pCPU->InstructMechina();
			}	

			if(iRow >= 56 && iRow < 296)
			{
				pTask->m_pPPU->UpdateLine(iRow-56);
			}
		}
		
		if(pTask->m_pPPU->m_rCtrl[0]&0x80 && pTask->m_pPPU->m_rCtrl[2]&0x80)
		{
			pTask->m_pCPU->IsrNmi();
			
			//清除register D7
			pTask->m_pPPU->m_rCtrl[2] &= 0x7F;
		}
		Sleep(5);
	}
}

CPPUTask::CPPUTask()
{
	m_pPPU = NULL;

	m_event = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_pThread = AfxBeginThread(WaitForTaskRollFun,this,0,0,CREATE_SUSPENDED);

	if(m_event == NULL || m_pThread == NULL)
	{
		Log("task create failed...\n");
		return;
	}

	m_pThread->ResumeThread();
}

void CPPUTask::Suspend()
{
	if(m_pThread)
		m_pThread->SuspendThread();

}
void CPPUTask::Resume()
{
	if(m_pThread)
		m_pThread->ResumeThread();
}

CPPUTask::~CPPUTask()
{

}

void CPPUTask::StartTask(PPU* pPPU, CPU6502* pCPU)
{
	m_pPPU = pPPU;
	m_pCPU = pCPU;
	m_isRun = FALSE;
	SetEvent(m_event);
}

BOOL CPPUTask::IsRun()
{
	return m_isRun;	
}