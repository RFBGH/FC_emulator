
// FC_emulator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFC_emulatorApp:
// �йش����ʵ�֣������ FC_emulator.cpp
//

class CFC_emulatorApp : public CWinApp
{
public:
	CFC_emulatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFC_emulatorApp theApp;