
// FC_emulatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FC_emulator.h"
#include "FC_emulatorDlg.h"
#include "afxdialogex.h"

#include "PPUTask.h"
#include "NesLoad.h"
#include "Task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFC_emulatorDlg 对话框



CFC_emulatorDlg::CFC_emulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFC_emulatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFC_emulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT_ROM, m_editOpCount);

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFC_emulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UP, &CFC_emulatorDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CFC_emulatorDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CFC_emulatorDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CFC_emulatorDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_SEL, &CFC_emulatorDlg::OnBnClickedButtonSel)
	ON_BN_CLICKED(IDC_BUTTON_START, &CFC_emulatorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_A, &CFC_emulatorDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CFC_emulatorDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(ID_BUTTON_LOAD, &CFC_emulatorDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CFC_emulatorDlg::OnBnClickedButtonRun)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CFC_emulatorDlg 消息处理程序

BOOL CFC_emulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	cpu6502.Reset();
	ppu.Reset();
	fcInput.Reset();
	
	//ppu.m_rCtrl[2] |= 0x80;
	
	cpu6502.SelectPPU(&ppu);
	cpu6502.SelectInput(&fcInput);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFC_emulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFC_emulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CBitmap bmp;
		bmp.CreateBitmap(256,240,1,32,gScreenBuf);

		CPaintDC dc(this);

		CDC memDc;
		memDc.CreateCompatibleDC(NULL);
		memDc.SelectObject(bmp);

		dc.BitBlt(0,0,256,240,&memDc,0,0,SRCCOPY);

		CDialogEx::OnPaint();
	}
}



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFC_emulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFC_emulatorDlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x08);
}


void CFC_emulatorDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x02);
}

void CFC_emulatorDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
		fcInput.SetInputValue(0x04);
}


void CFC_emulatorDlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
		fcInput.SetInputValue(0x01);
}


void CFC_emulatorDlg::OnBnClickedButtonSel()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x20);
}


void CFC_emulatorDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x10);
}


void CFC_emulatorDlg::OnBnClickedButtonA()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x80);
}


void CFC_emulatorDlg::OnBnClickedButtonB()
{
	// TODO: 在此添加控件通知处理程序代码
	fcInput.SetInputValue(0x40);
}


void CFC_emulatorDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog fileDlg(TRUE,"nes",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Bin Files (*.bin)|*.bin|All Files (*.*)|*.*||",this);
	if(IDOK == fileDlg.DoModal())
	{
		m_editOpCount.SetWindowTextA(fileDlg.GetPathName());
		//nesLoad.LoadNesFile(fileDlg.GetPathName().GetBuffer(0),&cpu6502,&ppu);
		nesLoad.LoadNesFile(fileDlg.GetPathName().GetBuffer(0), cpu6502.nesFile, &cpu6502,&ppu);
		
		cpu6502.SelectPPU(&ppu);
		cpu6502.SelectInput(&fcInput);
		ppuTask.StartTask(&ppu, &cpu6502);
		SetTimer(1,10,NULL);
	}else
	{
		MessageBox("Need BIN FILE!","UpdateBoot",MB_OK);
		return;
	}
}


void CFC_emulatorDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	ppuTask.StartTask(&ppu, &cpu6502);
	SetTimer(1,20,NULL);
}


void CFC_emulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(nIDEvent == 1)
	{
		CRect rect;
		rect.SetRect(0,0,256,256);
		RedrawWindow(&rect);
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CFC_emulatorDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
