#ifndef __6502CPU_H__
#define __6502CPU_H__

#include "Public.h"
#include "PPU.h"
#include "FcInput.h"    
#include "NesFile.h"

#define CPU6502_ERR_NONE			0x00
#define CPU6502_ERR_WRONG_RAM_ADDR  0x01
#define CPU6502_ERR_WRONG_PRM_ADDR  0x04
#define CPU6502_ERR_SP_OVERFLOW0 	0x03
#define CPU6502_ERR_SP_OVERFLOW1 	0x05
#define CPU6502_ERR_WRONG_OPER  	0x02

#define ROM_TYPE_32K 1
#define ROM_TYPE_16K 0

//定义6502CPU资源和内容。
class CPU6502
{
public:
	
	PPU* m_pPPU;
	FcInput* m_pFcInput;
	
	UINT  m_ErrCode;
	UINT  m_IsrLock;
	UINT  m_StrLock;
	
	UCHAR m_rA;		//寄存器A
	UCHAR m_rX;		//寄存器X
	UCHAR m_rY;		//寄存器Y
	UCHAR m_rSP;	//堆栈指针
	USHORT m_rPC;	//程序计数器
	UCHAR m_rPSW;	//程序状态字
					/*
					7 6 5 4 3 2 1 0
					N V E B D I Z C
					*/
					
	USHORT m_isrNmiAddr;
	USHORT m_isrResetAddr;
	USHORT m_isrBrkIrqAddr;

	UCHAR m_ram[2*1024+5];	//缓存
	UCHAR m_rom[64*1024+5];	//program rom
	UCHAR m_rPPU[8];		//PPU寄存器
	UCHAR m_rAPU[21];		//APU寄存器
	UCHAR m_rOAM;			//OAM寄存器
	UCHAR m_rInput[2];		//输入寄存器
	
	void SelectPPU(PPU* pPPU);
	void SelectInput(FcInput* fcInput);
	
	void Reset();
	CPU6502();
	~CPU6502();

	NesFile nesFile;
	USHORT m_rChageRomDst;
	USHORT m_rChageRomSrc;

	/*
	 *******************************************************
	 *状态位设置功能
	 *
	 *******************************************************
	 */

	//PSW state bit.
	void SetPswBit(int iType);
	void ClrPswBit(int iType);
	BOOL IsSetPswBit(int iType);
	
	//C bit
	void SetCBit(BOOL bSet);
	BOOL IsSetCBit();
	
	//Z bit
	void SetZBit(BOOL bSet);
	BOOL IsSetZBit();
	
	//I bit
	void SetIBit(BOOL bSet);
	BOOL IsSetIBit();
	
	//D bit
	void SetDBit(BOOL bSet);
	BOOL IsSetDBit();
	
	//B bit
	void SetBBit(BOOL bSet);
	BOOL IsSetBBit();
	
	//V bit
	void SetVBit(BOOL bSet);
	BOOL IsSetVBit();
	
	//N bit
	void SetNBit(BOOL bSet);
	BOOL IsSetNBit();
	
	BOOL IsNegative(UCHAR ucParam);
	BOOL IsEqualZero(UCHAR ucParam);
	
	UCHAR GetRamValueByAddr(USHORT usAddr);
	void  SetRamValueByAddr(UCHAR ucValue, USHORT usAddr);
	
	void IsrReset();
	void IsrBrkIrq();
	void IsrNmi();
	void EnterIsr();

	/*
	 *******************************************************
	 *指令执行功能
	 *
	 *******************************************************
	 */

/*
//LDA M->A
#define LDA_CHAGE_INDIRECT_ADDR_X	0xA1
#define LDA_ZEROPAGE_ADDR			0xA5
#define LDA_DIRECT_DATA				0xA9
#define LDA_DIRECT_ADDR 			0xAD
#define LDA_INDIRECT_CHAGE_ADDR_Y	0xB1
#define LDA_ZEROPAGE_CHAGE_ADDR_X	0xB5
#define LDA_DIERCT_CHAGE_ADDR_Y		0xB9
#define LDA_DIERCT_CHAGE_ADDR_X		0xBD
*/

	void HA1_DoLdaChageIndirectAddrX();
	void hA5_DoLdaZeroPageAddr();
	void HA9_DoLdaDirectData();
	void HAD_DoLdaDirectAddr();
	void HB1_DoLdaIndirectChageAddrY();
	void HB5_DoLdaZeroPageChageAddrX();
	void HB9_DoLdaDirectChageAddrY();
	void HBD_DoLdaDirectChageAddrX();
	
/*
//LDX M->X
#define LDX_DIRECT_DATA				0xA2
#define LDX_ZEROPAGE_ADDR			0xA6
#define LDX_DIRECT_ADDR				0xAE
#define LDX_ZEROPAGE_CHAGE_ADDR_Y	0xB6
#define LDX_DIRECT_CHAGE_ADDR_Y		0xBE
*/
	void HA2_DoLdxDirectData();
	void HA6_DoLdxZeroPageAddr();
	void HAE_DoLdxDirectAddr();
	void HB6_DoLdxZeroPageChageAddrY();
	void HBE_DoLdxDirectChageAddrY();
	
/*
//LDY M->Y
#define LDY_DIRECT_DATA				0xA0
#define LDY_ZEROPAGE_ADDR			0xA4
#define LDY_DIRECT_ADDR				0xAC
#define LDY_ZEROPAGE_CHAGE_ADDR_X	0xB4
#define LDY_DIRECT_CHAGE_ADDR_X		0xBC
*/
	void HA0_DoLdyDirectData();
	void HA4_DoLdyZeroPageAddr();
	void HAC_DoLdyDirectAddr();
	void HB4_DoLdyZeroPageChageAddrX();
	void HBC_DoLdyDirectChageAddrX();

/*
//STA A->M
#define STA_CHAGE_INDIRECT_ADDR_X	0x81
#define STA_ZEROPAGE_ADDR			0x85
#define STA_DIRECT_ADDR				0x8D
#define STA_INDIRECT_CHAGE_ADDR_Y	0x91
#define STA_ZEROPAGE_ADDR_X			0x95
#define STA_DIRECT_ADDR_Y			0x99
#define STA_DIRECT_ADDR_X			0x9D
*/
	void H81_DoStaChageIndirectAddrX();
	void H85_DoStaZeroPageAddr();
	void H8D_DoStaDirectAddr();
	void H91_DoStaIndirectChageAddrY();
	void H95_DoStaZeroPageAddrX();
	void H99_DoStaDirectAddrY();
	void H9D_DoStaDirectAddrX();
	
/*
//STX X->M
#define STX_ZEROPAGE_ADDR			0x86
#define STX_DIRECT_ADDR				0x8E
#define STX_ZEROPAGE_ADDR_Y			0x96
*/
	void H86_DoStxZeroPageAddr();
	void H8E_DoStxDirectAddr();
	void H96_DoStxZeroPageAddrY();
	
/*
//STX Y->M
#define STY_ZEROPAGE_ADDR			0x84
#define STY_DIRECT_ADDR				0x8C
#define STY_ZEROPAGE_ADDR_X			0x94
*/
	void H84_DoStyZeroPageAddr();
	void H8C_DoStyDirectAddr();
	void H94_DoStyZeroPageAddrX();
	
/*
//A, X, Y, SP
#define TAX		0xAA	//A->X
#define TXA		0x8A	//X->A
#define TAY		0xA8	//A->Y
#define TYA		0x98	//Y->A
#define TSX		0xBA	//SP->X
#define TXS		0x9A	//X->SP
*/
	void HAA_DoTax();
	void H8A_DoTxa();
	void HA8_DoTay();
	void H98_DoTya();
	void HBA_DoTsx();
	void H9A_DoTxs();
	
/*
//ADC A+M+C->A
#define ADC_CHAGE_INDIRECT_ADDR_X	0x61
#define ADC_ZEROPAGE_ADDR			0x65
#define ADC_DIRECT_DATA				0x69
#define ADC_DIRECT_ADDR				0x6D
#define ADC_INDIRECT_CHAGE_ADDR_Y	0x71
#define ADC_ZEROPAGE_ADDR_X			0x75
#define ADC_DIRECT_ADDR_Y			0x79
#define ADC_DIRECT_ADDR_X			0x7D
*/

	void H61_DoAdcChageIndirectAddrX();
	void H65_DoAdcZeroPageAddr();
	void H69_DoAdcDirectData();
	void H6D_DoAdcDirectAddr();
	void H71_DoAdcIndirectChageAddrY();
	void H75_DoAdcZeroPageAddrX();
	void H79_DoAdcDirectAddrY();
	void H7D_DoAdcDirectAddrX();
	
/*
//SBC A-M-C->A
#define SBC_CHAGE_INDIRECT_ADDR_X	0xE1
#define SBC_ZEROPAGE_ADDR			0xE5
#define SBC_DIRECT_DATA				0xE9
#define SBC_DIRECT_ADDR				0xED
#define SBC_INDIRECT_CHAGE_ADDR_Y	0xF1
#define SBC_ZEROPAGE_ADDR_X			0xF5
#define SBC_DIRECT_ADDR_Y			0xF9
#define SBC_DIRECT_ADDR_x			0xFD
*/
	void HE1_DoSbcChageIndirectAddrX();
	void HE5_DoSbcZeroPageAddr();
	void HE9_DoSbcDirectData();
	void HED_DoSbcDirectAddr();
	void HF1_DoSbcIndirectChageAddrY();
	void HF5_DoSbcZeroPageAddrX();
	void HFD_DoSbcDirectAddrX();
	void HF9_DoSbcDirectAddrY();

/*
//INC M+1->M
#define INC_ZEROPAGE_ADDR			0xE6
#define INC_DIRECT_ADDR				0xEE
#define INC_ZEROPAGE_ADDR_X				0xF6
#define INC_DIRECT_ADDR_X			0xFE
*/
	void HE6_DoIncZeroPageAddr();
	void HEE_DoIncDirectAddr();
	void HF6_DoIncZeroPageAddrX();
	void HFE_DoIncDirectAddrX();
	
/*
//DEC M-1->M
#define DEC_ZEROPAGE_ADDR			0xC6
#define DEC_DIRECT_ADDR				0xCE
#define DEC_ZEROPAGE_ADDR_X			0xD6
#define DEC_DIRECT_ADDR_X			0xDE
*/
	void HC6_DoDecZeroPageAddr();
	void HCE_DoDecDirectAddr();
	void HD6_DoDecZeroPageAddrX();
	void HDE_DoDecDirectAddrX();
	
/*
//X,Y +1; -1
#define INX 0xE8	//X+1 -> X
#define DEX 0xCA	//X-1 -> X
#define INY 0xC8	//Y+1 -> Y
#define DEY 0x88	//Y-1 -> Y
*/
	void HE8_DoInx();
	void HCA_DoDex();
	void HC8_DoIny();
	void H88_DoDey();
	
/*
#define AND_CHAGE_INDIRECT_ADDR_X	0x21
#define AND_ZEROPAGE_ADDR			0x25
#define AND_DIRECT_DATA				0x29
#define AND_DIRECT_ADDR				0x2D
#define AND_INDIRECT_CHAGE_ADDR_Y	0x31
#define AND_ZEROPAGE_ADDR_X			0x35
#define AND_DIRECT_ADDR_Y			0x39
#define AND_DIRECT_ADDR_X			0x3D
*/
	void H21_DoAndChageIndirectAddrX();
	void H25_DoAndZeroPageAddr();
	void H29_DoAndDirectData();
	void H2D_DoAndDirectAddr();
	void H31_DoAndIndirectChageAddrY();
	void H35_DoAndZeroPageAddrX();
	void H39_DoAndDirectAddrY();
	void H3D_DoAndDirectAddrX();
	
/*
//ORA A|M->A
#define ORA_CHAGE_INDIRECT_ADDR_X	0x01
#define ORA_ZEROPAGE_ADDR			0x05
#define ORA_DIRECT_DATA				0x09
#define ORA_DIRECT_ADDR				0x0D
#define ORA_INDIRECT_CHAGE_ADDR_Y	0x11
#define ORA_ZEROPAGE_ADDR_X			0x15
#define ORA_DIRECT_ADDR_Y			0x19
#define ORA_DIRECT_ADDR_X			0x1D
*/
	void H01_DoOraChageIndirectAddrX();
	void H05_DoOraZeroPageAddr();
	void H09_DoOraDirectData();
	void H0D_DoOraDirectAddr();
	void H11_DoOraIndirectChageAddrY();
	void H15_DoOraZeroPageAddrX();
	void H19_DoOraDirectAddrY();
	void H1D_DoOraDirectAddrX();

/*
//EOR A^M->A
#define EOR_CHAGE_INDIRECT_ADDR_X	0x41
#define EOR_ZEROPAGE_ADDR			0x45
#define EOR_DIRECT_DATA				0x49
#define EOR_DIRECT_ADDR				0x4D
#define EOR_INDIRECT_CHAGE_ADDR_Y	0x51
#define EOR_ZEROPAGE_ADDR_X			0x55
#define EOR_DIRECT_ADDR_Y			0x59
#define EOR_DIRECT_ADDR_X			0x5D
*/
	void H41_DoEorChageIndirectAddrX();
	void H45_DoEorZeroPageAddr();
	void H49_DoEorDirectData();
	void H4D_DoEorDirectAddr();
	void H51_DoEorIndirectChageAddrY();
	void H55_DoEorZeroPageAddrX();
	void H59_DoEorDirectAddrY();
	void H5D_DoEorDirectAddrX();

/*
//CLC
#define CLC 0x18	//0->C
#define SEC 0x38	//1->C
#define CLD 0xD8	//0->D
#define SED 0xF8	//1->D
#define CLV 0xB8	//0->V
#define CLI 0x58	//0->I
#define SEI 0x78	//1->I
*/
	void H18_DoClc();
	void H38_DoSec();
	void HD8_DoCld();
	void HF8_DoSed();
	void HB8_DoClv();
	void H58_DoCli();
	void H78_DoSei();
	
/*
//CMP A CMP M
//若结果为 负值，N=1；若结果为0，Z=0；若无借位，即A>=M，C=1；
#define CMP_CHAGE_INDIRECT_ADDR_X	0xC1
#define CMP_ZEROPAGE_ADDR			0xC5
#define CMP_DIRECT_DATA				0xC9
#define CMP_DIRECT_ADDR				0xCD
#define CMP_INDIRECT_CHAGE_ADDR_Y	0xD1
#define CMP_ZEROPAGE_ADDR_X			0xD5
#define CMP_DIRECT_ADDR_Y			0xD9
#define CMP_DIRECT_ADDR_X			0xDD
*/
	void HC1_DoCmpChageIndirectAddrX();
	void HC5_DoCmpZeroPageAddr();
	void HC9_DoCmpDirectData();
	void HCD_DoCmpDirectAddr();
	void HD1_DoCmpIndirectChageAddrY();
	void HD5_DoCmpZeroPageAddrX();
	void HD9_DoCmpDirectAddrY();
	void HDD_DoCmpDirectAddrX();

/*
//CMP X CMP M
#define CPX_DIRECT_DATA				0xE0
#define CPX_ZEROPAGE_ADDR			0xE4
#define CPX_DIRECT_ADDR				0xEC
*/
	void HE0_DoCpxDirectData();
	void HE4_DoCpxZeroPageAddr();
	void HEC_DoCpxDirectAddr();

/*
//CMP Y CMP M
#define CPY_DIRECT_DATA				0xC0
#define CPY_ZEROPAGE_ADDR			0xC4
#define CPY_DIRECT_ADDR				0xCC
*/
	void HC0_DoCpyDirectData();
	void HC4_DoCpyZeroPageAddr();
	void HCC_DoCpyDirectAddr();

/*
//shift left 1bit
#define ASL_A_ADDR					0x0A
#define ASL_ZEROPAGE_ADDR			0x06
#define ASL_DIRECT_ADDR				0x0E
#define ASL_ZEROPAGE_ADDR_X			0x16
#define ASL_DIRECT_ADDR_X			0x1E
*/
	void H0A_DoAslAAddr();
	void H06_DoAslZeroPageAddr();
	void H0E_DoAslDirectAddr();
	void H16_DoAslZeroPageAddrX();
	void H1E_DoAslDirectAddrX();
	
/*
//shift right 1bit
#define LSR_COUNTER_ADDR			0x4A
#define LSR_ZEROPAGE_ADDR			0x46
#define LSR_DIRECT_ADDR				0x4E
#define LSR_ZEROPAGE_ADDR_X			0x56
#define LSR_DIRECT_ADDR_X			0x5E
*/
	void H4A_DoLsrAAddr();
	void H46_DoLsrZeroPageAddr();
	void H4E_DoLsrDirectAddr();
	void H56_DoLsrZeroPageAddrX();
	void H5E_DoLsrDirectAddrX();
	

/*
//rotate left rotate with bit C in 1bit
#define ROL_COUNTER_ADDR			0x2A
#define ROL_ZEROPAGE_ADDR			0x26
#define ROL_DIRECT_ADDR				0x2E
#define ROL_ZEROPAGE_ADDR_X			0x36
#define ROL_DIRECT_ADDR_X			0x3E
*/
	void H2A_DoRolAAddr();
	void H26_DoRolZeroPageAddr();
	void H2E_DoRolDirectAddr();
	void H36_DoRolZeroPageAddrX();
	void H3E_DoRolDirectAddrX();
	

/*
//rotate right rotate with bit C in 1bit
#define ROR_COUNTER_ADDR			0x6A
#define ROR_ZEROPAGE_ADDR			0x66
#define ROR_DIRECT_ADDR				0x6E
#define ROR_ZEROPAGE_ADDR_X			0x76
#define ROR_DIRECT_ADDR_X			0x7E
*/
	void H6A_DoRorAAddr();
	void H66_DoRorZeroPageAddr();
	void H6E_DoRorDirectAddr();
	void H76_DoRorZeroPageAddrX();
	void H7E_DoRorDirectAddrX();

/*
#define PHA		0x48	//A->@SP
#define PLA		0x68	//@SP->A
#define PHP		0x08	//PSW->@SP
#define PLP		0x28	//@SP->PSW
*/
	void H48_DoPha();
	void H68_DoPla();
	void H28_DoPlp();
	void H08_DoPhp();

/*
//JMP
#define JMP_DIRECT_ADDR		0x4C
#define JMP_INDIRECT_ADDR	0x5C
*/
	void H4C_DoJmpDirectAddr();
	void H5C_DoJmpIndirectAddr();
	
/*
//condition jump indirect.
#define BEQ		0xF0	//Z=1,jump
#define BNE		0xD0	//Z=0,jump
#define BCS		0xB0	//C=1,jump
#define BCC		0x90	//C=0,jump
#define BMI		0x30	//N=1,jump
#define BPL		0x10	//N=0,jump
#define BVS		0x70	//V=1,jump
#define BVC		0x50	//V=0,jump
*/
	void HF0_DoBeq();
	void HD0_DoBne();
	void HB0_DoBcs();
	void H90_DoBcc();
	void H30_DoBmi();
	void H10_DoBpl();
	void H70_DoBvs();
	void H50_DoBvc();
	
/*
#define JSR	0x20	//jump to function
#define RTS 0x60	//return from function.
*/
	void H20_DoJsr();
	void H60_DoRts();

/*
//Bit
#define BIT_ZEROPAGE_ADDR	0x24
#define BIT_DIRECT_ADDR		0x2C
*/
	void H24_BitZeroPageAddr();
	void H2C_BitDirectAddr();
	
/*
#define BRK	0x00
#define RTI	0x40
#define NOP 0xEA
*/
	void H00_DoBrk();
	void H40_DoRti();
	void HEA_DoNop();

	void  Push(UCHAR ucParam);
	UCHAR  Pop();
	UCHAR GetNextOperate();
	UCHAR GetOperateParam8();
	USHORT GetOperateParam16();

	void UpdateRom(UCHAR* pucRom, USHORT usSize, int iType);
	int InstructMechina();
};

//LDA M->A
#define LDA_CHAGE_INDIRECT_ADDR_X	0xA1
#define LDA_ZEROPAGE_ADDR			0xA5
#define LDA_DIRECT_DATA				0xA9
#define LDA_DIRECT_ADDR 			0xAD
#define LDA_INDIRECT_CHAGE_ADDR_Y	0xB1
#define LDA_ZEROPAGE_CHAGE_ADDR_X	0xB5
#define LDA_DIERCT_CHAGE_ADDR_Y		0xB9
#define LDA_DIERCT_CHAGE_ADDR_X		0xBD

//LDX M->X
#define LDX_DIRECT_DATA				0xA2
#define LDX_ZEROPAGE_ADDR			0xA6
#define LDX_DIRECT_ADDR				0xAE
#define LDX_ZEROPAGE_CHAGE_ADDR_Y	0xB6
#define LDX_DIRECT_CHAGE_ADDR_Y		0xBE

//LDY M->Y
#define LDY_DIRECT_DATA				0xA0
#define LDY_ZEROPAGE_ADDR			0xA4
#define LDY_DIRECT_ADDR				0xAC
#define LDY_ZEROPAGE_CHAGE_ADDR_X	0xB4
#define LDY_DIRECT_CHAGE_ADDR_X		0xBC

//STA A->M
#define STA_CHAGE_INDIRECT_ADDR_X	0x81
#define STA_ZEROPAGE_ADDR			0x85
#define STA_DIRECT_ADDR				0x8D
#define STA_INDIRECT_CHAGE_ADDR_Y	0x91
#define STA_ZEROPAGE_ADDR_X			0x95
#define STA_DIRECT_ADDR_Y			0x99
#define STA_DIRECT_ADDR_X			0x9D

//STX X->M
#define STX_ZEROPAGE_ADDR			0x86
#define STX_DIRECT_ADDR				0x8E
#define STX_ZEROPAGE_ADDR_Y			0x96

//STX Y->M
#define STY_ZEROPAGE_ADDR			0x84
#define STY_DIRECT_ADDR				0x8C
#define STY_ZEROPAGE_ADDR_X			0x94

//A, X, Y, SP
#define TAX		0xAA	//A->X
#define TXA		0x8A	//X->A
#define TAY		0xA8	//A->Y
#define TYA		0x98	//Y->A
#define TSX		0xBA	//SP->X
#define TXS		0x9A	//X->SP

//ADC A+M+C->A
#define ADC_CHAGE_INDIRECT_ADDR_X	0x61
#define ADC_ZEROPAGE_ADDR			0x65
#define ADC_DIRECT_DATA				0x69
#define ADC_DIRECT_ADDR				0x6D
#define ADC_INDIRECT_CHAGE_ADDR_Y	0x71
#define ADC_ZEROPAGE_ADDR_X			0x75
#define ADC_DIRECT_ADDR_Y			0x79
#define ADC_DIRECT_ADDR_X			0x7D

//SBC A-M-C->A
#define SBC_CHAGE_INDIRECT_ADDR_X	0xE1
#define SBC_ZEROPAGE_ADDR			0xE5
#define SBC_DIRECT_DATA				0xE9
#define SBC_DIRECT_ADDR				0xED
#define SBC_INDIRECT_CHAGE_ADDR_Y	0xF1
#define SBC_ZEROPAGE_ADDR_X			0xF5
#define SBC_DIRECT_ADDR_Y			0xF9
#define SBC_DIRECT_ADDR_X			0xFD

//INC M+1->M
#define INC_ZEROPAGE_ADDR			0xE6
#define INC_DIRECT_ADDR				0xEE
#define INC_ZEROPAGE_ADDR_X			0xF6
#define INC_DIRECT_ADDR_X			0xFE

//DEC M-1->M
#define DEC_ZEROPAGE_ADDR			0xC6
#define DEC_DIRECT_ADDR				0xCE
#define DEC_ZEROPAGE_ADDR_X			0xD6
#define DEC_DIRECT_ADDR_X			0xDE

//X,Y +1; -1
#define INX 0xE8	//X+1 -> X
#define DEX 0xCA	//X-1 -> X
#define INY 0xC8	//Y+1 -> Y
#define DEY 0x88	//Y-1 -> Y

//AND A&M->A
#define AND_CHAGE_INDIRECT_ADDR_X	0x21
#define AND_ZEROPAGE_ADDR			0x25
#define AND_DIRECT_DATA				0x29
#define AND_DIRECT_ADDR				0x2D
#define AND_INDIRECT_CHAGE_ADDR_Y	0x31
#define AND_ZEROPAGE_ADDR_X			0x35
#define AND_DIRECT_ADDR_Y			0x39
#define AND_DIRECT_ADDR_X			0x3D

//ORA A|M->A
#define ORA_CHAGE_INDIRECT_ADDR_X	0x01
#define ORA_ZEROPAGE_ADDR			0x05
#define ORA_DIRECT_DATA				0x09
#define ORA_DIRECT_ADDR				0x0D
#define ORA_INDIRECT_CHAGE_ADDR_Y	0x11
#define ORA_ZEROPAGE_ADDR_X			0x15
#define ORA_DIRECT_ADDR_Y			0x19
#define ORA_DIRECT_ADDR_X			0x1D

//EOR A^M->A
#define EOR_CHAGE_INDIRECT_ADDR_X	0x41
#define EOR_ZEROPAGE_ADDR			0x45
#define EOR_DIRECT_DATA				0x49
#define EOR_DIRECT_ADDR				0x4D
#define EOR_INDIRECT_CHAGE_ADDR_Y	0x51
#define EOR_ZEROPAGE_ADDR_X			0x55
#define EOR_DIRECT_ADDR_Y			0x59
#define EOR_DIRECT_ADDR_X			0x5D

//CLC
#define CLC 0x18	//0->C
#define SEC 0x38	//1->C
#define CLD 0xD8	//0->D
#define SED 0xF8	//1->D
#define CLV 0xB8	//0->V
#define CLI 0x58	//0->I
#define SEI 0x78	//1->I

//CMP A CMP M
//若结果为 负值，N=1；若结果为0，Z=0；若无借位，即A>=M，C=1；
#define CMP_CHAGE_INDIRECT_ADDR_X	0xC1
#define CMP_ZEROPAGE_ADDR			0xC5
#define CMP_DIRECT_DATA				0xC9
#define CMP_DIRECT_ADDR				0xCD
#define CMP_INDIRECT_CHAGE_ADDR_Y	0xD1
#define CMP_ZEROPAGE_ADDR_X			0xD5
#define CMP_DIRECT_ADDR_Y			0xD9
#define CMP_DIRECT_ADDR_X			0xDD

//CMP X CMP M
#define CPX_DIRECT_DATA				0xE0
#define CPX_ZEROPAGE_ADDR			0xE4
#define CPX_DIRECT_ADDR				0xEC

//CMP Y CMP M
#define CPY_DIRECT_DATA				0xC0
#define CPY_ZEROPAGE_ADDR			0xC4
#define CPY_DIRECT_ADDR				0xCC

//shift left 1bit
#define ASL_A_ADDR					0x0A
#define ASL_ZEROPAGE_ADDR			0x06
#define ASL_DIRECT_ADDR				0x0E
#define ASL_ZEROPAGE_ADDR_X			0x16
#define ASL_DIRECT_ADDR_X			0x1E

//shift right 1bit
#define LSR_COUNTER_ADDR			0x4A
#define LSR_ZEROPAGE_ADDR			0x46
#define LSR_DIRECT_ADDR				0x4E
#define LSR_ZEROPAGE_ADDR_X			0x56
#define LSR_DIRECT_ADDR_X			0x5E

//rotate left rotate with bit C in 1bit
#define ROL_COUNTER_ADDR			0x2A
#define ROL_ZEROPAGE_ADDR			0x26
#define ROL_DIRECT_ADDR				0x2E
#define ROL_ZEROPAGE_ADDR_X			0x36
#define ROL_DIRECT_ADDR_X			0x3E

//rotate right rotate with bit C in 1bit
#define ROR_COUNTER_ADDR			0x6A
#define ROR_ZEROPAGE_ADDR			0x66
#define ROR_DIRECT_ADDR				0x6E
#define ROR_ZEROPAGE_ADDR_X			0x76
#define ROR_DIRECT_ADDR_X			0x7E

#define PHA		0x48	//A->@SP
#define PLA		0x68	//@SP->A
#define PLP		0x28	//@SP->PSW
#define PHP		0x08	//PSW->@SP

//JMP
#define JMP_DIRECT_ADDR		0x4C
#define JMP_INDIRECT_ADDR	0x6C //5C

//condition jump indirect.
#define BEQ		0xF0	//Z=1,jump
#define BNE		0xD0	//Z=0,jump
#define BCS		0xB0	//C=1,jump
#define BCC		0x90	//C=0,jump
#define BMI		0x30	//N=1,jump
#define BPL		0x10	//N=0,jump
#define BVS		0x70	//V=1,jump
#define BVC		0x50	//V=0,jump

#define JSR	0x20	//jump to function
#define RTS 0x60	//return from function.

//Bit
#define BIT_ZEROPAGE_ADDR	0x24
#define BIT_DIRECT_ADDR		0x2C

//BRK
#define BRK	0x00

//return from interrupt
#define RTI	0x40

//nop
#define NOP 0xEA

#endif