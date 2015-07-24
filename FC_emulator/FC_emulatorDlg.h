
// FC_emulatorDlg.h : ͷ�ļ�
//
#include "6502CPU.h"
#include "PPU.h"
#include "FcInput.h"

#pragma once


// CFC_emulatorDlg �Ի���
class CFC_emulatorDlg : public CDialogEx
{
// ����
public:
	CFC_emulatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FC_EMULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CEdit   m_editOpCount;
	CPU6502 cpu6502; 
	PPU     ppu;
	FcInput fcInput;


	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonSel();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
