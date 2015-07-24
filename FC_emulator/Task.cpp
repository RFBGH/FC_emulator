#include "Task.h"

CTask task;


UINT CTask::WaitForTaskRollFun (void* pParam)
{
	CTask* pTask = (CTask*)pParam;

	WaitForSingleObject(pTask->m_event,INFINITE);	//¹ÒÆð×ÔÉí
	pTask->m_isRun = TRUE;

	while(TRUE)
	{
		if(pTask->m_pCpu)
		{
			pTask->m_pCpu->InstructMechina();
		}			
	}
}

CTask::CTask()
{
	m_pCpu = NULL;

	m_event = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_pThread = AfxBeginThread(WaitForTaskRollFun,this,0,0,CREATE_SUSPENDED);

	if(m_event == NULL || m_pThread == NULL)
	{
		Log("task create failed...\n");
		return;
	}

	m_pThread->ResumeThread();
}

void CTask::Suspend()
{
	if(m_pThread)
		m_pThread->SuspendThread();

}
void CTask::Resume()
{
	if(m_pThread)
		m_pThread->ResumeThread();
}

CTask::~CTask()
{

}

void CTask::StartTask(CPU6502* pCpu)
{
	m_pCpu = pCpu;
	m_isRun = FALSE;
	SetEvent(m_event);
}

BOOL CTask::IsRun()
{
	return m_isRun;	
}