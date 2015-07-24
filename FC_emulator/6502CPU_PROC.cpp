 #include "6502CPU.h"
 
 
int CPU6502::InstructMechina()
{
	UCHAR opr;
	
	while(m_StrLock);
	m_IsrLock = 1;

	m_ErrCode = CPU6502_ERR_NONE;
	opr = GetNextOperate();

#ifdef _DEBUG
	if(m_rPC < 0x8000)
	{
		int iDebug;
		iDebug = 1;
	}
	if(m_rPC == 0xBFB7)
	{
		//guDebugFlag = 1;
	}
#endif

	switch(opr)
	{
		//LDA M->A
		case LDA_CHAGE_INDIRECT_ADDR_X:
			
			HA1_DoLdaChageIndirectAddrX();
			break;
			
		case LDA_ZEROPAGE_ADDR:
			
			hA5_DoLdaZeroPageAddr();
			break;
			
		case LDA_DIRECT_DATA:
			
			HA9_DoLdaDirectData();
			break;
			
		case LDA_DIRECT_ADDR:
			
			HAD_DoLdaDirectAddr();
			break;
			
		case LDA_INDIRECT_CHAGE_ADDR_Y:
			
			HB1_DoLdaIndirectChageAddrY();
			break;
			
		case LDA_ZEROPAGE_CHAGE_ADDR_X:
			
			HB5_DoLdaZeroPageChageAddrX();
			break;
			
		case LDA_DIERCT_CHAGE_ADDR_Y:
			
			HB9_DoLdaDirectChageAddrY();
			break;
			
		case LDA_DIERCT_CHAGE_ADDR_X:
			
			HBD_DoLdaDirectChageAddrX();
			break;

		//LDX M->X
		case LDX_DIRECT_DATA:
			
			HA2_DoLdxDirectData();
			break;
			
		case LDX_ZEROPAGE_ADDR:
			
			HA6_DoLdxZeroPageAddr();
			break;
			
		case LDX_DIRECT_ADDR:
			
			HAE_DoLdxDirectAddr();
			break;
			
		case LDX_ZEROPAGE_CHAGE_ADDR_Y:
			
			HB6_DoLdxZeroPageChageAddrY();
			break;
			
		case LDX_DIRECT_CHAGE_ADDR_Y:
			
			HBE_DoLdxDirectChageAddrY();
			break;

		//LDY M->Y
		case LDY_DIRECT_DATA:
			
			HA0_DoLdyDirectData();
			break;
			
		case LDY_ZEROPAGE_ADDR:
			
			HA4_DoLdyZeroPageAddr();
			break;
			
		case LDY_DIRECT_ADDR:
			
			HAC_DoLdyDirectAddr();
			break;
			
		case LDY_ZEROPAGE_CHAGE_ADDR_X:
			
			HB4_DoLdyZeroPageChageAddrX();
			break;
			
		case LDY_DIRECT_CHAGE_ADDR_X:
			
			 HBC_DoLdyDirectChageAddrX();
			break;

		//STA A->M
		case STA_CHAGE_INDIRECT_ADDR_X:
			
			H81_DoStaChageIndirectAddrX();
			break;
			
		case STA_ZEROPAGE_ADDR:
			
			H85_DoStaZeroPageAddr();
			break;
			
		case STA_DIRECT_ADDR:
			
			H8D_DoStaDirectAddr();
			break;
			
		case STA_INDIRECT_CHAGE_ADDR_Y:
			
			H91_DoStaIndirectChageAddrY();
			break;
			
		case STA_ZEROPAGE_ADDR_X:
			
			H95_DoStaZeroPageAddrX();
			break;
			
		case STA_DIRECT_ADDR_Y:
			
			H99_DoStaDirectAddrY();
			break;
			
		case STA_DIRECT_ADDR_X:
			
			H9D_DoStaDirectAddrX();
			break;

		//STX X->M
		case STX_ZEROPAGE_ADDR:
			
			H86_DoStxZeroPageAddr();
			break;

		case STX_DIRECT_ADDR:
			
			H8E_DoStxDirectAddr();
			break;

		case STX_ZEROPAGE_ADDR_Y:
			
			H96_DoStxZeroPageAddrY();
			break;

		//STX Y->M
		case STY_ZEROPAGE_ADDR:
			
			H84_DoStyZeroPageAddr();
			break;

		case STY_DIRECT_ADDR:
			
			H8C_DoStyDirectAddr();
			break;

		case STY_ZEROPAGE_ADDR_X:
			
			H94_DoStyZeroPageAddrX();
			break;

		//A, X, Y, SP
		case TAX:
			
			HAA_DoTax();
			break;

		case TXA:
			
			H8A_DoTxa();
			break;

		case TAY:
			
			HA8_DoTay();
			break;

		case TYA:
			
			H98_DoTya();
			break;

		case TSX:
			
			HBA_DoTsx();
			break;

		case TXS:
			
			H9A_DoTxs();
			break;

		//ADC A+M+C->A
		case ADC_CHAGE_INDIRECT_ADDR_X:
			
			H61_DoAdcChageIndirectAddrX();
			break;

		case ADC_ZEROPAGE_ADDR:
			
			H65_DoAdcZeroPageAddr();
			break;

		case ADC_DIRECT_DATA:
			
			H69_DoAdcDirectData();
			break;

		case ADC_DIRECT_ADDR:
			
			H6D_DoAdcDirectAddr();
			break;

		case ADC_INDIRECT_CHAGE_ADDR_Y:
			
			H71_DoAdcIndirectChageAddrY();
			break;

		case ADC_ZEROPAGE_ADDR_X:
			
			H75_DoAdcZeroPageAddrX();
			break;

		case ADC_DIRECT_ADDR_Y:
			
			H79_DoAdcDirectAddrY();
			break;

		case ADC_DIRECT_ADDR_X:
			
			H7D_DoAdcDirectAddrX();
			break;

		//SBC A-M-C->A
		case SBC_CHAGE_INDIRECT_ADDR_X:
			
			HE1_DoSbcChageIndirectAddrX();
			break;

		case SBC_ZEROPAGE_ADDR:
			
			HE5_DoSbcZeroPageAddr();
			break;

		case SBC_DIRECT_DATA:
			
			HE9_DoSbcDirectData();
			break;

		case SBC_DIRECT_ADDR:
			
			HED_DoSbcDirectAddr();
			break;

		case SBC_INDIRECT_CHAGE_ADDR_Y:
			
			HF1_DoSbcIndirectChageAddrY();
			break;

		case SBC_ZEROPAGE_ADDR_X:
			
			HF5_DoSbcZeroPageAddrX();
			break;

		case SBC_DIRECT_ADDR_Y:
			
			HF9_DoSbcDirectAddrY();
			break;

		case SBC_DIRECT_ADDR_X:
			
			HFD_DoSbcDirectAddrX();
			break;

		//INC M+1->M
		case INC_ZEROPAGE_ADDR:
			
			HE6_DoIncZeroPageAddr();
			break;

		case INC_DIRECT_ADDR:
			
			HEE_DoIncDirectAddr();
			break;

		case INC_ZEROPAGE_ADDR_X:
			
			HF6_DoIncZeroPageAddrX();
			break;

		case INC_DIRECT_ADDR_X:
			
			HFE_DoIncDirectAddrX();
			break;

		//DEC M-1->M
		case DEC_ZEROPAGE_ADDR:
			
			HC6_DoDecZeroPageAddr();
			break;

		case DEC_DIRECT_ADDR:
			
			HCE_DoDecDirectAddr();
			break;

		case DEC_ZEROPAGE_ADDR_X:
			
			HD6_DoDecZeroPageAddrX();
			break;

		case DEC_DIRECT_ADDR_X:
			
			HDE_DoDecDirectAddrX();
			break;

		//X,Y +1; -1
		case INX:
			
			HE8_DoInx();
			break;

		case DEX:
			
			HCA_DoDex();
			break;

		case INY:
			
			HC8_DoIny();
			break;

		case DEY:
			
			H88_DoDey();
			break;

		//AND A&M->A
		case AND_CHAGE_INDIRECT_ADDR_X:
			
			H21_DoAndChageIndirectAddrX();
			break;

		case AND_ZEROPAGE_ADDR:
			
			H25_DoAndZeroPageAddr();
			break;

		case AND_DIRECT_DATA:
			
			H29_DoAndDirectData();
			break;

		case AND_DIRECT_ADDR:
			
			H2D_DoAndDirectAddr();
			break;

		case AND_INDIRECT_CHAGE_ADDR_Y:
			
			H31_DoAndIndirectChageAddrY();
			break;

		case AND_ZEROPAGE_ADDR_X:
			
			H35_DoAndZeroPageAddrX();
			break;

		case AND_DIRECT_ADDR_Y:
			
			H39_DoAndDirectAddrY();
			break;

		case AND_DIRECT_ADDR_X:
			
			H3D_DoAndDirectAddrX();
			break;

		//ORA A|M->A
		case ORA_CHAGE_INDIRECT_ADDR_X:
			
			H01_DoOraChageIndirectAddrX();
			break;

		case ORA_ZEROPAGE_ADDR:
			
			H05_DoOraZeroPageAddr();
			break;

		case ORA_DIRECT_DATA:
			
			H09_DoOraDirectData();
			break;

		case ORA_DIRECT_ADDR:
			
			H0D_DoOraDirectAddr();
			break;

		case ORA_INDIRECT_CHAGE_ADDR_Y:
			
			H11_DoOraIndirectChageAddrY();
			break;

		case ORA_ZEROPAGE_ADDR_X:
			
			H15_DoOraZeroPageAddrX();
			break;

		case ORA_DIRECT_ADDR_Y:
			
			H19_DoOraDirectAddrY();
			break;

		case ORA_DIRECT_ADDR_X:
			
			H1D_DoOraDirectAddrX();
			break;

		//EOR A^M->A
		case EOR_CHAGE_INDIRECT_ADDR_X:
			
			H41_DoEorChageIndirectAddrX();
			break;

		case EOR_ZEROPAGE_ADDR:
			
			H45_DoEorZeroPageAddr();
			break;

		case EOR_DIRECT_DATA:
			
			H49_DoEorDirectData();
			break;

		case EOR_DIRECT_ADDR:
			
			H4D_DoEorDirectAddr();
			break;

		case EOR_INDIRECT_CHAGE_ADDR_Y:
			
			H51_DoEorIndirectChageAddrY();
			break;

		case EOR_ZEROPAGE_ADDR_X:
			
			H55_DoEorZeroPageAddrX();
			break;

		case EOR_DIRECT_ADDR_Y:
			
			H59_DoEorDirectAddrY();
			break;

		case EOR_DIRECT_ADDR_X:
			
			H5D_DoEorDirectAddrX();
			break;

		//CLC
		case CLC:
			
			H18_DoClc();
			break;

		case SEC:
			
			H38_DoSec();
			break;

		case CLD:
			
			HD8_DoCld();
			break;

		case SED:
			
			HF8_DoSed();
			break;

		case CLV:
			
			HB8_DoClv();
			break;

		case CLI:
			
			H58_DoCli();
			break;

		case SEI:
			
			H78_DoSei();
			break;

		//CMP A CMP M
		//若结果为 负值，N=1；若结果为0，Z=0；若无借位，即A>=M，C=1；
		case CMP_CHAGE_INDIRECT_ADDR_X:
			
			HC1_DoCmpChageIndirectAddrX();
			break;

		case CMP_ZEROPAGE_ADDR:
			
			HC5_DoCmpZeroPageAddr();
			break;

		case CMP_DIRECT_DATA:
			
			HC9_DoCmpDirectData();
			break;

		case CMP_DIRECT_ADDR:
			
			HCD_DoCmpDirectAddr();
			break;

		case CMP_INDIRECT_CHAGE_ADDR_Y:
			
			HD1_DoCmpIndirectChageAddrY();
			break;

		case CMP_ZEROPAGE_ADDR_X:
			
			HD5_DoCmpZeroPageAddrX();
			break;

		case CMP_DIRECT_ADDR_Y:
			
			HD9_DoCmpDirectAddrY();
			break;

		case CMP_DIRECT_ADDR_X:
			
			HDD_DoCmpDirectAddrX();
			break;

		//CMP X CMP M
		case CPX_DIRECT_DATA:
			
			HE0_DoCpxDirectData();
			break;

		case CPX_ZEROPAGE_ADDR:
			
			HE4_DoCpxZeroPageAddr();
			break;

		case CPX_DIRECT_ADDR:
			
			HEC_DoCpxDirectAddr();
			break;

		//CMP Y CMP M
		case CPY_DIRECT_DATA:
			
			HC0_DoCpyDirectData();
			break;

		case CPY_ZEROPAGE_ADDR:
			
			HC4_DoCpyZeroPageAddr();
			break;

		case CPY_DIRECT_ADDR:
			
			HCC_DoCpyDirectAddr();
			break;

		//shift left 1bit
		case ASL_A_ADDR:
			
			H0A_DoAslAAddr();
			break;

		case ASL_ZEROPAGE_ADDR:
			
			H06_DoAslZeroPageAddr();
			break;

		case ASL_DIRECT_ADDR:
			
			H0E_DoAslDirectAddr();
			break;

		case ASL_ZEROPAGE_ADDR_X:
			
			H16_DoAslZeroPageAddrX();
			break;

		case ASL_DIRECT_ADDR_X:
			
			H1E_DoAslDirectAddrX();
			break;

		//shift right 1bit
		case LSR_COUNTER_ADDR:
			
			H4A_DoLsrAAddr();
			break;

		case LSR_ZEROPAGE_ADDR:
			
			H46_DoLsrZeroPageAddr();
			break;

		case LSR_DIRECT_ADDR:
			
			H4E_DoLsrDirectAddr();
			break;

		case LSR_ZEROPAGE_ADDR_X:
			
			H56_DoLsrZeroPageAddrX();
			break;

		case LSR_DIRECT_ADDR_X:
			
			H5E_DoLsrDirectAddrX();
			break;

		//rotate left rotate with bit C in 1bit
		case ROL_COUNTER_ADDR:
			
			H2A_DoRolAAddr();
			break;

		case ROL_ZEROPAGE_ADDR:
			
			H26_DoRolZeroPageAddr();
			break;

		case ROL_DIRECT_ADDR:
			
			H2E_DoRolDirectAddr();
			break;

		case ROL_ZEROPAGE_ADDR_X:
			
			H36_DoRolZeroPageAddrX();
			break;

		case ROL_DIRECT_ADDR_X:
			
			H3E_DoRolDirectAddrX();
			break;

		//rotate right rotate with bit C in 1bit
		case ROR_COUNTER_ADDR:
			
			H6A_DoRorAAddr();
			break;

		case ROR_ZEROPAGE_ADDR:
			
			H66_DoRorZeroPageAddr();
			break;

		case ROR_DIRECT_ADDR:
			
			H6E_DoRorDirectAddr();
			break;

		case ROR_ZEROPAGE_ADDR_X:
			
			H76_DoRorZeroPageAddrX();
			break;

		case ROR_DIRECT_ADDR_X:
			
			H7E_DoRorDirectAddrX();
			break;

		case PHA:
			
			H48_DoPha();
			break;

		case PLA:
			
			H68_DoPla();
			break;

		case PLP:
			
			H28_DoPlp();
			break;

		case PHP:
			
			H08_DoPhp();
			break;
			
		//JMP
		case JMP_DIRECT_ADDR:
			
			H4C_DoJmpDirectAddr();
			break;

		case JMP_INDIRECT_ADDR:
			
			H5C_DoJmpIndirectAddr();
			break;

		//condition jump indirect.
		case BEQ:
			
			HF0_DoBeq();
			break;

		case BNE:
			
			HD0_DoBne();
			break;

		case BCS:
			
			HB0_DoBcs();
			break;

		case BCC:
			
			H90_DoBcc();
			break;

		case BMI:
			
			H30_DoBmi();
			break;

		case BPL:
			
			H10_DoBpl();
			break;

		case BVS:
			
			H70_DoBvs();
			break;

		case BVC:
			
			H50_DoBvc();
			break;

		case JSR:
			
			H20_DoJsr();
			break;

		case RTS:
			
			H60_DoRts();
			break;

		//Bit
		case BIT_ZEROPAGE_ADDR:
			
			H24_BitZeroPageAddr();
			break;

		case BIT_DIRECT_ADDR:
			
			H2C_BitDirectAddr();
			break;

		//BRK
		case BRK:
			
			H00_DoBrk();
			break;


		//return from interrupt
		case RTI:
			
			H40_DoRti();
			break;


		//nop
		case NOP:
			
			HEA_DoNop();
			break;
			
		default:
			m_ErrCode = CPU6502_ERR_WRONG_OPER;
			Log("error...\n");
			break;
	}

	m_IsrLock = 0;
	return m_ErrCode;
}