
// FC_emulatorDlg.h : 头文件
//
#include "6502CPU.h"
#include "PPU.h"
#include "FcInput.h"

#pragma once


// CFC_emulatorDlg 对话框
class CFC_emulatorDlg : public CDialogEx
{
// 构造
public:
	CFC_emulatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FC_EMULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
