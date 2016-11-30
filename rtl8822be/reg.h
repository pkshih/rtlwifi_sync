/******************************************************************************
 *
 * Copyright(c) 2009-2010  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#ifndef __RTL8822B_REG_H__
#define __RTL8822B_REG_H__

#include "../halmac/halmac_reg_8822b.h"
#include "../halmac/halmac_bit_8822b.h"

#define TXPKT_BUF_SELECT			0x69
#define RXPKT_BUF_SELECT			0xA5
#define DISABLE_TRXPKT_BUF_ACCESS		0x0


/* Page 0 */
#define REG_LEDCFG2_8822B				0x004E	/* need review */
#define REG_SPS0_CTRL_8822B				0x0011	/* need review: swlps */

#define REG_EFUSE_ACCESS_8822B			(REG_PMC_DBG_CTRL2_8822B+3)	/*0x00CF*/
#define REG_AFE_XTAL_CTRL_8822B			REG_AFE_CTRL1_8822B
#define REG_AFE_PLL_CTRL_8822B			REG_AFE_CTRL2_8822B

/* Page 1 */

#define	MSR					(REG_CR_8822B + 2)

/* for MSR 0x102 */
#define	MSR_NOLINK				0x00
#define	MSR_ADHOC				0x01
#define	MSR_INFRA				0x02
#define	MSR_AP					0x03

/*-----------------------------------------------------
 *
 *	0x0200h ~ 0x027Fh	TXDMA Configuration
 *
 *-----------------------------------------------------
 */

/*-----------------------------------------------------
 *
 *	0x0280h ~ 0x02FFh	RXDMA Configuration
 *
 *-----------------------------------------------------
 */
#define REG_RXDMA_CONTROL_8822B		(REG_RXPKT_NUM_8822B+2)	/* 0x0286 */

/*-----------------------------------------------------
 *
 *	0x0300h ~ 0x03FFh	PCIe
 *
 *-----------------------------------------------------
 */

/* REG_HIMR3_8822B */
#define IMR_H2CDOK			BIT_SETH2CDOK_MASK_8822B

/* spec version 11
 *-----------------------------------------------------
 *
 *	0x0400h ~ 0x047Fh	Protocol Configuration
 *
 *-----------------------------------------------------
 */

#define REG_MAX_AGGR_NUM_8822B			(REG_PROT_MODE_CTRL_8822B+2)/*0x04CA*/

/* for RRSR 0x440 */
#define	RRSR_RSC_OFFSET				21
#define	RRSR_SHORT_OFFSET			23
#define	RRSR_RSC_BW_40M				0x600000
#define	RRSR_RSC_UPSUBCHNL			0x400000
#define	RRSR_RSC_LOWSUBCHNL			0x200000
#define	RRSR_1M					BIT(0)
#define	RRSR_2M					BIT(1)
#define	RRSR_5_5M				BIT(2)
#define	RRSR_11M				BIT(3)
#define	RRSR_6M					BIT(4)
#define	RRSR_9M					BIT(5)
#define	RRSR_12M				BIT(6)
#define	RRSR_18M				BIT(7)
#define	RRSR_24M				BIT(8)
#define	RRSR_36M				BIT(9)
#define	RRSR_48M				BIT(10)
#define	RRSR_54M				BIT(11)
#define	RRSR_MCS0				BIT(12)
#define	RRSR_MCS1				BIT(13)
#define	RRSR_MCS2				BIT(14)
#define	RRSR_MCS3				BIT(15)
#define	RRSR_MCS4				BIT(16)
#define	RRSR_MCS5				BIT(17)
#define	RRSR_MCS6				BIT(18)
#define	RRSR_MCS7				BIT(19)

#define	RRSR_ALL_CCK		(RRSR_1M | RRSR_2M | RRSR_5_5M | RRSR_11M)
#define	RRSR_ALL_OFDM_AG	(RRSR_6M | RRSR_9M | RRSR_12M | RRSR_18M |\
				 RRSR_24M | RRSR_36M | RRSR_48M | RRSR_54M)


/*-----------------------------------------------------
 *
 *	0x0500h ~ 0x05FFh	EDCA Configuration
 *
 *-----------------------------------------------------
 */

#define REG_SIFS_TRX_8822B				(REG_SIFS_8822B+2)	/*0x0516*/


/*-----------------------------------------------------
 *
 *	0x0600h ~ 0x07FFh	WMAC Configuration
 *
 *-----------------------------------------------------
 */


#define	RATR_1M					0x00000001
#define	RATR_2M					0x00000002
#define	RATR_55M				0x00000004
#define	RATR_11M				0x00000008
#define	RATR_6M					0x00000010
#define	RATR_9M					0x00000020
#define	RATR_12M				0x00000040
#define	RATR_18M				0x00000080
#define	RATR_24M				0x00000100
#define	RATR_36M				0x00000200
#define	RATR_48M				0x00000400
#define	RATR_54M				0x00000800
#define	RATR_MCS0				0x00001000
#define	RATR_MCS1				0x00002000
#define	RATR_MCS2				0x00004000
#define	RATR_MCS3				0x00008000
#define	RATR_MCS4				0x00010000
#define	RATR_MCS5				0x00020000
#define	RATR_MCS6				0x00040000
#define	RATR_MCS7				0x00080000
#define	RATR_MCS8				0x00100000
#define	RATR_MCS9				0x00200000
#define	RATR_MCS10				0x00400000
#define	RATR_MCS11				0x00800000
#define	RATR_MCS12				0x01000000
#define	RATR_MCS13				0x02000000
#define	RATR_MCS14				0x04000000
#define	RATR_MCS15				0x08000000

#define RATE_1M					BIT(0)
#define RATE_2M					BIT(1)
#define RATE_5_5M				BIT(2)
#define RATE_11M				BIT(3)
#define RATE_6M					BIT(4)
#define RATE_9M					BIT(5)
#define RATE_12M				BIT(6)
#define RATE_18M				BIT(7)
#define RATE_24M				BIT(8)
#define RATE_36M				BIT(9)
#define RATE_48M				BIT(10)
#define RATE_54M				BIT(11)
#define RATE_MCS0				BIT(12)
#define RATE_MCS1				BIT(13)
#define RATE_MCS2				BIT(14)
#define RATE_MCS3				BIT(15)
#define RATE_MCS4				BIT(16)
#define RATE_MCS5				BIT(17)
#define RATE_MCS6				BIT(18)
#define RATE_MCS7				BIT(19)
#define RATE_MCS8				BIT(20)
#define RATE_MCS9				BIT(21)
#define RATE_MCS10				BIT(22)
#define RATE_MCS11				BIT(23)
#define RATE_MCS12				BIT(24)
#define RATE_MCS13				BIT(25)
#define RATE_MCS14				BIT(26)
#define RATE_MCS15				BIT(27)


/* CAM definition */

#define	CAM_NONE				0x0
#define	CAM_WEP40				0x01
#define	CAM_TKIP				0x02
#define	CAM_AES					0x04
#define	CAM_WEP104				0x05

/*#define	TOTAL_CAM_ENTRY				64*/
/*#define	HALF_CAM_ENTRY				32*/

#define	CAM_WRITE				BIT(16)
#define	CAM_READ				0x00000000
#define	CAM_POLLINIG				BIT(31)


/*********************************************
 *       8822BE IMR/ISR bits
 *********************************************
 */
#define	IMR_DISABLED				0x0
/* IMR DW0(0x0060-0063) Bit 0-31 */
#define	IMR_TIMER2				BIT(31)
#define	IMR_TIMER1				BIT(30)
#define	IMR_PSTIMEOUT				BIT(29)
#define	IMR_GTINT4				BIT(28)
#define	IMR_GTINT3				BIT(27)
#define	IMR_TBDER				BIT(26)
#define	IMR_TBDOK				BIT(25)
#define	IMR_TSF_BIT32_TOGGLE			BIT(24)
#define	IMR_BCNDMAINT0				BIT(20)
#define	IMR_BCNDOK0				BIT(16)
#define IMR_HSISR_IND_ON_INT			BIT(15)
#define	IMR_BCNDMAINT_E				BIT(14)
#define	IMR_ATIMEND				BIT(12)
#define	IMR_HISR1_IND_INT			BIT(11)
#define	IMR_C2HCMD				BIT(10)
#define	IMR_CPWM2				BIT(9)
#define	IMR_CPWM				BIT(8)
#define	IMR_HIGHDOK				BIT(7)
#define	IMR_MGNTDOK				BIT(6)
#define	IMR_BKDOK				BIT(5)
#define	IMR_BEDOK				BIT(4)
#define	IMR_VIDOK				BIT(3)
#define	IMR_VODOK				BIT(2)
#define	IMR_RDU					BIT(1)
#define	IMR_ROK					BIT(0)

/* IMR DW1(0x00B4-00B7) Bit 0-31 */
#define IMR_TXFIFO_TH_INT_8822B		BIT_TXFIFO_TH_INT_8822B
#define IMR_BTON_STS_UPDATE_MASK_8822B	BIT_BTON_STS_UPDATE_MASK_8822B
#define	IMR_MCUERR				BIT(28)
#define	IMR_BCNDMAINT7				BIT(27)
#define	IMR_BCNDMAINT6				BIT(26)
#define	IMR_BCNDMAINT5				BIT(25)
#define	IMR_BCNDMAINT4				BIT(24)
#define	IMR_BCNDMAINT3				BIT(23)
#define	IMR_BCNDMAINT2				BIT(22)
#define	IMR_BCNDMAINT1				BIT(21)
#define	IMR_BCNDOK7				BIT(20)
#define	IMR_BCNDOK6				BIT(19)
#define	IMR_BCNDOK5				BIT(18)
#define	IMR_BCNDOK4				BIT(17)
#define	IMR_BCNDOK3				BIT(16)
#define	IMR_BCNDOK2				BIT(15)
#define	IMR_BCNDOK1				BIT(14)
#define	IMR_ATIMEND_E				BIT(13)
#define	IMR_ATIMEND				BIT(12)
#define	IMR_TXERR				BIT(11)
#define	IMR_RXERR				BIT(10)
#define	IMR_TXFOVW				BIT(9)
#define	IMR_RXFOVW				BIT(8)
#define IMR_CPU_MGQ_TXDONE_MSK_8822B	BIT_CPU_MGQ_TXDONE_MSK_8822B
#define IMR_PS_TIMER_C_MSK_8822B		BIT_PS_TIMER_C_MSK_8822B
#define IMR_PS_TIMER_B_MSK_8822B		BIT_PS_TIMER_B_MSK_8822B
#define IMR_PS_TIMER_A_MSK_8822B		BIT_PS_TIMER_A_MSK_8822B
#define IMR_CPUMGQ_TX_TIMER_MSK_8822B	BIT_CPUMGQ_TX_TIMER_MSK_8822B

/*********************************************
 *       8822BE EFUSE definition
 *********************************************
 */
#define	HWSET_MAX_SIZE				1024
#define EFUSE_MAX_SECTION			64
#define EFUSE_REAL_CONTENT_LEN			1024
#define EFUSE_OOB_PROTECT_BYTES			18

#define	EEPROM_DEFAULT_THERMALMETER		0x12

#define	RTL8822B_EEPROM_ID			0x8129

#define PPG_BB_GAIN_2G_TXA_OFFSET_8822B		0xEE
#define PPG_THERMAL_OFFSET_8822B		0xEF

#define	EEPROM_TX_PWR_INX_8822B			0x10

#define	EEPROM_ChannelPlan_8822B		0xB8
#define	EEPROM_XTAL_8822B			0xB9
#define	EEPROM_THERMAL_METER_8822B		0xBA
#define	EEPROM_IQK_LCK_8822B			0xBB
#define	EEPROM_2G_5G_PA_TYPE_8822B		0xBC
/* PATH A & PATH B */
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_AB_8822B	0xBD
/* PATH C & PATH D */
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_CD_8822B	0xBE
/* PATH A & PATH B */
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_AB_8822B	0xBF
/* PATH C & PATH D */
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_CD_8822B	0xC0

#define	EEPROM_RF_BOARD_OPTION_8822B		0xC1
#define	EEPROM_FEATURE_OPTION_8822B		0xC2
#define	EEPROM_RF_BT_SETTING_8822B		0xC3
#define	EEPROM_VERSION_8822B			0xC4
#define	EEPROM_CustomID_8822B			0xC5
#define	EEPROM_TX_BBSWING_2G_8822B		0xC6
#define	EEPROM_TX_PWR_CALIBRATE_RATE_8822B	0xC8
#define	EEPROM_RF_ANTENNA_OPT_8822B		0xC9
#define	EEPROM_RFE_OPTION_8822B			0xCA
#define EEPROM_COUNTRY_CODE_8822B		0xCB

#define EEPROM_VID				0xD6
#define EEPROM_DID				0xD8
#define EEPROM_SVID				0xDA
#define EEPROM_SMID				0xDC

/* RTL8822BU */
#define EEPROM_MAC_ADDR_8822BU			0x107
#define EEPROM_VID_8822BU			0x100
#define EEPROM_PID_8822BU			0x102
#define EEPROM_USB_OPTIONAL_FUNCTION0_8822BU	0x104
#define EEPROM_USB_MODE_8822BU			0x06

/* RTL8822BS */
#define	EEPROM_MAC_ADDR_8822BS			0x11A

/* RTL8822BE */
#define	EEPROM_MAC_ADDR_8822BE			0xD0

/* ------------------------- */



#define	STOPBECON				BIT(6)
#define	STOPHIGHT				BIT(5)
#define	STOPMGT					BIT(4)
#define	STOPVO					BIT(3)
#define	STOPVI					BIT(2)
#define	STOPBE					BIT(1)
#define	STOPBK					BIT(0)

#define	RCR_APPFCS				BIT(31)
#define	RCR_APP_MIC				BIT(30)
#define	RCR_APP_ICV				BIT(29)
#define	RCR_APP_PHYST_RXFF			BIT(28)
#define	RCR_APP_BA_SSN				BIT(27)
#define RCR_VHT_DACK					BIT(26)
#define	RCR_ENMBID				BIT(24)
#define	RCR_LSIGEN				BIT(23)
#define	RCR_MFBEN				BIT(22)
#define	RCR_HTC_LOC_CTRL			BIT(14)
#define	RCR_AMF					BIT(13)
#define	RCR_ACF					BIT(12)
#define	RCR_ADF					BIT(11)
#define	RCR_AICV				BIT(9)
#define	RCR_ACRC32				BIT(8)
#define	RCR_CBSSID_BCN				BIT(7)
#define	RCR_CBSSID_DATA				BIT(6)
#define	RCR_CBSSID				RCR_CBSSID_DATA
#define	RCR_APWRMGT				BIT(5)
#define	RCR_ADD3				BIT(4)
#define	RCR_AB					BIT(3)
#define	RCR_AM					BIT(2)
#define	RCR_APM					BIT(1)
#define	RCR_AAP					BIT(0)
#define	RCR_MXDMA_OFFSET			8
#define	RCR_FIFO_OFFSET				13

#define RSV_CTRL				0x001C
#define RD_CTRL					0x0524

#define REG_USB_INFO_8822B				0xFE17
#define REG_USB_SPECIAL_OPTION_8822B			0xFE55
#define REG_USB_DMA_AGG_TO_8822B			0xFE5B
#define REG_USB_AGG_TO_8822B				0xFE5C
#define REG_USB_AGG_TH_8822B				0xFE5D

#define REG_USB_VID_8822B				0xFE60
#define REG_USB_PID_8822B				0xFE62
#define REG_USB_OPTIONAL_8822B			0xFE64
#define REG_USB_CHIRP_K_8822B				0xFE65
#define REG_USB_PHY_8822B				0xFE66
#define REG_USB_MAC_ADDR_8822B			0xFE70
#define REG_USB_HRPWM_8822B				0xFE58
#define REG_USB_HCPWM_8822B				0xFE57

#define SW18_FPWM				BIT(3)

#define ISO_MD2PP				BIT(0)
#define ISO_UA2USB				BIT(1)
#define ISO_UD2CORE				BIT(2)
#define ISO_PA2PCIE				BIT(3)
#define ISO_PD2CORE				BIT(4)
#define ISO_IP2MAC				BIT(5)
#define ISO_DIOP				BIT(6)
#define ISO_DIOE				BIT(7)
#define ISO_EB2CORE				BIT(8)
#define ISO_DIOR				BIT(9)

#define PWC_EV25V				BIT(14)
#define PWC_EV12V				BIT(15)

#define FEN_BBRSTB				BIT(0)
#define FEN_BB_GLB_RSTN				BIT(1)
#define FEN_USBA				BIT(2)
#define FEN_UPLL				BIT(3)
#define FEN_USBD				BIT(4)
#define FEN_DIO_PCIE				BIT(5)
#define FEN_PCIEA				BIT(6)
#define FEN_PPLL				BIT(7)
#define FEN_PCIED				BIT(8)
#define FEN_DIOE				BIT(9)
#define FEN_CPUEN				BIT(10)
#define FEN_DCORE				BIT(11)
#define FEN_ELDR				BIT(12)
#define FEN_DIO_RF				BIT(13)
#define FEN_HWPDN				BIT(14)
#define FEN_MREGEN				BIT(15)

#define PFM_LDALL				BIT(0)
#define PFM_ALDN				BIT(1)
#define PFM_LDKP				BIT(2)
#define PFM_WOWL				BIT(3)
#define EnPDN					BIT(4)
#define PDN_PL					BIT(5)
#define APFM_ONMAC				BIT(8)
#define APFM_OFF				BIT(9)
#define APFM_RSM				BIT(10)
#define AFSM_HSUS				BIT(11)
#define AFSM_PCIE				BIT(12)
#define APDM_MAC				BIT(13)
#define APDM_HOST				BIT(14)
#define APDM_HPDN				BIT(15)
#define RDY_MACON				BIT(16)
#define SUS_HOST				BIT(17)
#define ROP_ALD					BIT(20)
#define ROP_PWR					BIT(21)
#define ROP_SPS					BIT(22)
#define SOP_MRST				BIT(25)
#define SOP_FUSE				BIT(26)
#define SOP_ABG					BIT(27)
#define SOP_AMB					BIT(28)
#define SOP_RCK					BIT(29)
#define SOP_A8M					BIT(30)
#define XOP_BTCK				BIT(31)

#define ANAD16V_EN				BIT(0)
#define ANA8M					BIT(1)
#define MACSLP					BIT(4)
#define LOADER_CLK_EN				BIT(5)
#define _80M_SSC_DIS				BIT(7)
#define _80M_SSC_EN_HO				BIT(8)
#define PHY_SSC_RSTB				BIT(9)
#define SEC_CLK_EN				BIT(10)
#define MAC_CLK_EN				BIT(11)
#define SYS_CLK_EN				BIT(12)
#define RING_CLK_EN				BIT(13)

#define	BOOT_FROM_EEPROM			BIT(4)
#define	EEPROM_EN				BIT(5)

#define AFE_BGEN				BIT(0)
#define AFE_MBEN				BIT(1)
#define MAC_ID_EN				BIT(7)

#define WLOCK_ALL				BIT(0)
#define WLOCK_00				BIT(1)
#define WLOCK_04				BIT(2)
#define WLOCK_08				BIT(3)
#define WLOCK_40				BIT(4)
#define R_DIS_PRST_0				BIT(5)
#define R_DIS_PRST_1				BIT(6)
#define LOCK_ALL_EN				BIT(7)

#define RF_EN					BIT(0)
#define RF_RSTB					BIT(1)
#define RF_SDMRSTB				BIT(2)

#define LDA15_EN				BIT(0)
#define LDA15_STBY				BIT(1)
#define LDA15_OBUF				BIT(2)
#define LDA15_REG_VOS				BIT(3)
#define _LDA15_VOADJ(x)				(((x) & 0x7) << 4)

#define LDV12_EN				BIT(0)
#define LDV12_SDBY				BIT(1)
#define LPLDO_HSM				BIT(2)
#define LPLDO_LSM_DIS				BIT(3)
#define _LDV12_VADJ(x)				(((x) & 0xF) << 4)

#define XTAL_EN					BIT(0)
#define XTAL_BSEL				BIT(1)
#define _XTAL_BOSC(x)				(((x) & 0x3) << 2)
#define _XTAL_CADJ(x)				(((x) & 0xF) << 4)
#define XTAL_GATE_USB				BIT(8)
#define _XTAL_USB_DRV(x)			(((x) & 0x3) << 9)
#define XTAL_GATE_AFE				BIT(11)
#define _XTAL_AFE_DRV(x)			(((x) & 0x3) << 12)
#define XTAL_RF_GATE				BIT(14)
#define _XTAL_RF_DRV(x)				(((x) & 0x3) << 15)
#define XTAL_GATE_DIG				BIT(17)
#define _XTAL_DIG_DRV(x)			(((x) & 0x3) << 18)
#define XTAL_BT_GATE				BIT(20)
#define _XTAL_BT_DRV(x)				(((x) & 0x3) << 21)
#define _XTAL_GPIO(x)				(((x) & 0x7) << 23)

#define CKDLY_AFE				BIT(26)
#define CKDLY_USB				BIT(27)
#define CKDLY_DIG				BIT(28)
#define CKDLY_BT				BIT(29)

#define APLL_EN					BIT(0)
#define APLL_320_EN				BIT(1)
#define APLL_FREF_SEL				BIT(2)
#define APLL_EDGE_SEL				BIT(3)
#define APLL_WDOGB				BIT(4)
#define APLL_LPFEN				BIT(5)

#define APLL_REF_CLK_13MHZ			0x1
#define APLL_REF_CLK_19_2MHZ			0x2
#define APLL_REF_CLK_20MHZ			0x3
#define APLL_REF_CLK_25MHZ			0x4
#define APLL_REF_CLK_26MHZ			0x5
#define APLL_REF_CLK_38_4MHZ			0x6
#define APLL_REF_CLK_40MHZ			0x7

#define APLL_320EN				BIT(14)
#define APLL_80EN				BIT(15)
#define APLL_1MEN				BIT(24)

#define ALD_EN					BIT(18)
#define EF_PD					BIT(19)
#define EF_FLAG					BIT(31)

#define EF_TRPT					BIT(7)
#define LDOE25_EN				BIT(31)

#define RSM_EN					BIT(0)
#define Timer_EN				BIT(4)

#define TRSW0EN					BIT(2)
#define TRSW1EN					BIT(3)
#define EROM_EN					BIT(4)
#define EnBT					BIT(5)
#define EnUart					BIT(8)
#define Uart_910				BIT(9)
#define EnPMAC					BIT(10)
#define SIC_SWRST				BIT(11)
#define EnSIC					BIT(12)
#define SIC_23					BIT(13)
#define EnHDP					BIT(14)
#define SIC_LBK					BIT(15)

#define LED0PL					BIT(4)
#define LED1PL					BIT(12)
#define LED0DIS					BIT(7)

#define MCUFWDL_EN				BIT(0)
#define MCUFWDL_RDY				BIT(1)
#define FWDL_ChkSum_rpt				BIT(2)
#define MACINI_RDY				BIT(3)
#define BBINI_RDY				BIT(4)
#define RFINI_RDY				BIT(5)
#define WINTINI_RDY				BIT(6)
#define CPRST					BIT(23)

#define XCLK_VLD				BIT(0)
#define ACLK_VLD				BIT(1)
#define UCLK_VLD				BIT(2)
#define PCLK_VLD				BIT(3)
#define PCIRSTB					BIT(4)
#define V15_VLD					BIT(5)
#define TRP_B15V_EN				BIT(7)
#define SIC_IDLE				BIT(8)
#define BD_MAC2					BIT(9)
#define BD_MAC1					BIT(10)
#define IC_MACPHY_MODE				BIT(11)
#define VENDOR_ID				BIT(19)
#define PAD_HWPD_IDN				BIT(22)
#define TRP_VAUX_EN				BIT(23)
#define TRP_BT_EN				BIT(24)
#define BD_PKG_SEL				BIT(25)
#define BD_HCI_SEL				BIT(26)
#define TYPE_ID					BIT(27)

#define CHIP_VER_RTL_MASK			0xF000
#define CHIP_VER_RTL_SHIFT			12

#define REG_LBMODE_8822B				(REG_CR_8822B + 3)

#define HCI_TXDMA_EN				BIT(0)
#define HCI_RXDMA_EN				BIT(1)
#define TXDMA_EN				BIT(2)
#define RXDMA_EN				BIT(3)
#define PROTOCOL_EN				BIT(4)
#define SCHEDULE_EN				BIT(5)
#define MACTXEN					BIT(6)
#define MACRXEN					BIT(7)
#define ENSWBCN					BIT(8)
#define ENSEC					BIT(9)

#define _NETTYPE(x)				(((x) & 0x3) << 16)
#define MASK_NETTYPE				0x30000
#define NT_NO_LINK				0x0
#define NT_LINK_AD_HOC				0x1
#define NT_LINK_AP				0x2
#define NT_AS_AP				0x3

#define _LBMODE(x)				(((x) & 0xF) << 24)
#define MASK_LBMODE				0xF000000
#define LOOPBACK_NORMAL				0x0
#define LOOPBACK_IMMEDIATELY			0xB
#define LOOPBACK_MAC_DELAY			0x3
#define LOOPBACK_PHY				0x1
#define LOOPBACK_DMA				0x7

#define GET_RX_PAGE_SIZE(value)			((value) & 0xF)
#define GET_TX_PAGE_SIZE(value)			(((value) & 0xF0) >> 4)
#define _PSRX_MASK				0xF
#define _PSTX_MASK				0xF0
#define _PSRX(x)				(x)
#define _PSTX(x)				((x) << 4)

#define PBP_64					0x0
#define PBP_128					0x1
#define PBP_256					0x2
#define PBP_512					0x3
#define PBP_1024				0x4

#define RXDMA_ARBBW_EN				BIT(0)
#define RXSHFT_EN				BIT(1)
#define RXDMA_AGG_EN				BIT(2)
#define QS_VO_QUEUE				BIT(8)
#define QS_VI_QUEUE				BIT(9)
#define QS_BE_QUEUE				BIT(10)
#define QS_BK_QUEUE				BIT(11)
#define QS_MANAGER_QUEUE			BIT(12)
#define QS_HIGH_QUEUE				BIT(13)

#define HQSEL_VOQ				BIT(0)
#define HQSEL_VIQ				BIT(1)
#define HQSEL_BEQ				BIT(2)
#define HQSEL_BKQ				BIT(3)
#define HQSEL_MGTQ				BIT(4)
#define HQSEL_HIQ				BIT(5)

#define _TXDMA_HIQ_MAP(x)			(((x)&0x3) << 14)
#define _TXDMA_MGQ_MAP(x)			(((x)&0x3) << 12)
#define _TXDMA_BKQ_MAP(x)			(((x)&0x3) << 10)
#define _TXDMA_BEQ_MAP(x)			(((x)&0x3) << 8)
#define _TXDMA_VIQ_MAP(x)			(((x)&0x3) << 6)
#define _TXDMA_VOQ_MAP(x)			(((x)&0x3) << 4)

#define QUEUE_LOW				1
#define QUEUE_NORMAL				2
#define QUEUE_HIGH				3

#define _LLT_NO_ACTIVE				0x0
#define _LLT_WRITE_ACCESS			0x1
#define _LLT_READ_ACCESS			0x2

#define _LLT_INIT_DATA(x)			((x) & 0xFF)
#define _LLT_INIT_ADDR(x)			(((x) & 0xFF) << 8)
#define _LLT_OP(x)					(((x) & 0x3) << 30)
#define _LLT_OP_VALUE(x)			(((x) >> 30) & 0x3)

#define BB_WRITE_READ_MASK			(BIT(31) | BIT(30))
#define BB_WRITE_EN				BIT(30)
#define BB_READ_EN				BIT(31)

#define _HPQ(x)					((x) & 0xFF)
#define _LPQ(x)					(((x) & 0xFF) << 8)
#define _PUBQ(x)				(((x) & 0xFF) << 16)
#define _NPQ(x)					((x) & 0xFF)

#define HPQ_PUBLIC_DIS				BIT(24)
#define LPQ_PUBLIC_DIS				BIT(25)
#define LD_RQPN					BIT(31)

#define BCN_VALID				BIT(16)
#define BCN_HEAD(x)				(((x) & 0xFF) << 8)
#define	BCN_HEAD_MASK				0xFF00

#define BLK_DESC_NUM_SHIFT			4
#define BLK_DESC_NUM_MASK			0xF

#define DROP_DATA_EN				BIT(9)

#define EN_AMPDU_RTY_NEW			BIT(7)

#define _INIRTSMCS_SEL(x)			((x) & 0x3F)

#define _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#define _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)

#define RATE_REG_BITMAP_ALL			0xFFFFF

#define _RRSC_BITMAP(x)				((x) & 0xFFFFF)

#define _RRSR_RSC(x)				(((x) & 0x3) << 21)
#define RRSR_RSC_RESERVED			0x0
#define RRSR_RSC_UPPER_SUBCHANNEL		0x1
#define RRSR_RSC_LOWER_SUBCHANNEL		0x2
#define RRSR_RSC_DUPLICATE_MODE			0x3

#define USE_SHORT_G1				BIT(20)

#define _AGGLMT_MCS0(x)				((x) & 0xF)
#define _AGGLMT_MCS1(x)				(((x) & 0xF) << 4)
#define _AGGLMT_MCS2(x)				(((x) & 0xF) << 8)
#define _AGGLMT_MCS3(x)				(((x) & 0xF) << 12)
#define _AGGLMT_MCS4(x)				(((x) & 0xF) << 16)
#define _AGGLMT_MCS5(x)				(((x) & 0xF) << 20)
#define _AGGLMT_MCS6(x)				(((x) & 0xF) << 24)
#define _AGGLMT_MCS7(x)				(((x) & 0xF) << 28)

#define	RETRY_LIMIT_SHORT_SHIFT			8
#define	RETRY_LIMIT_LONG_SHIFT			0

#define _DARF_RC1(x)				((x) & 0x1F)
#define _DARF_RC2(x)				(((x) & 0x1F) << 8)
#define _DARF_RC3(x)				(((x) & 0x1F) << 16)
#define _DARF_RC4(x)				(((x) & 0x1F) << 24)
#define _DARF_RC5(x)				((x) & 0x1F)
#define _DARF_RC6(x)				(((x) & 0x1F) << 8)
#define _DARF_RC7(x)				(((x) & 0x1F) << 16)
#define _DARF_RC8(x)				(((x) & 0x1F) << 24)

#define _RARF_RC1(x)				((x) & 0x1F)
#define _RARF_RC2(x)				(((x) & 0x1F) << 8)
#define _RARF_RC3(x)				(((x) & 0x1F) << 16)
#define _RARF_RC4(x)				(((x) & 0x1F) << 24)
#define _RARF_RC5(x)				((x) & 0x1F)
#define _RARF_RC6(x)				(((x) & 0x1F) << 8)
#define _RARF_RC7(x)				(((x) & 0x1F) << 16)
#define _RARF_RC8(x)				(((x) & 0x1F) << 24)

#define AC_PARAM_TXOP_LIMIT_OFFSET		16
#define AC_PARAM_ECW_MAX_OFFSET			12
#define AC_PARAM_ECW_MIN_OFFSET			8
#define AC_PARAM_AIFS_OFFSET			0

#define _AIFS(x)				(x)
#define _ECW_MAX_MIN(x)				((x) << 8)
#define _TXOP_LIMIT(x)				((x) << 16)

#define _BCNIFS(x)				((x) & 0xFF)
#define _BCNECW(x)				((((x) & 0xF)) << 8)

#define _LRL(x)					((x) & 0x3F)
#define _SRL(x)					(((x) & 0x3F) << 8)

#define _SIFS_CCK_CTX(x)			((x) & 0xFF)
#define _SIFS_CCK_TRX(x)			(((x) & 0xFF) << 8)

#define _SIFS_OFDM_CTX(x)			((x) & 0xFF)
#define _SIFS_OFDM_TRX(x)			(((x) & 0xFF) << 8)

#define _TBTT_PROHIBIT_HOLD(x)			(((x) & 0xFF) << 8)

#define DIS_EDCA_CNT_DWN			BIT(11)

#define EN_MBSSID				BIT(1)
#define EN_TXBCN_RPT				BIT(2)
#define	EN_BCN_FUNCTION				BIT(3)

#define TSFTR_RST				BIT(0)
#define TSFTR1_RST				BIT(1)

#define STOP_BCNQ				BIT(6)

#define	DIS_TSF_UDT0_NORMAL_CHIP		BIT(4)
#define	DIS_TSF_UDT0_TEST_CHIP			BIT(5)

#define	AcmHw_HwEn				BIT(0)
#define	AcmHw_BeqEn				BIT(1)
#define	AcmHw_ViqEn				BIT(2)
#define	AcmHw_VoqEn				BIT(3)
#define	AcmHw_BeqStatus				BIT(4)
#define	AcmHw_ViqStatus				BIT(5)
#define	AcmHw_VoqStatus				BIT(6)

#define APSDOFF					BIT(6)
#define APSDOFF_STATUS				BIT(7)

#define BW_20MHZ				BIT(2)

#define RATE_BITMAP_ALL				0xFFFFF

#define RATE_RRSR_CCK_ONLY_1M			0xFFFF1

#define TSFRST					BIT(0)
#define DIS_GCLK				BIT(1)
#define PAD_SEL					BIT(2)
#define PWR_ST					BIT(6)
#define PWRBIT_OW_EN				BIT(7)
#define ACRC					BIT(8)
#define CFENDFORM				BIT(9)
#define ICV					BIT(10)

#define AAP					BIT(0)
#define APM					BIT(1)
#define AM					BIT(2)
#define AB					BIT(3)
#define ADD3					BIT(4)
#define APWRMGT					BIT(5)
#define CBSSID					BIT(6)
#define CBSSID_DATA				BIT(6)
#define CBSSID_BCN				BIT(7)
#define ACRC32					BIT(8)
#define AICV					BIT(9)
#define ADF					BIT(11)
#define ACF					BIT(12)
#define AMF					BIT(13)
#define HTC_LOC_CTRL				BIT(14)
#define UC_DATA_EN				BIT(16)
#define BM_DATA_EN				BIT(17)
#define MFBEN					BIT(22)
#define LSIGEN					BIT(23)
#define EnMBID					BIT(24)
#define APP_BASSN				BIT(27)
#define APP_PHYSTS				BIT(28)
#define APP_ICV					BIT(29)
#define APP_MIC					BIT(30)
#define APP_FCS					BIT(31)

#define _MIN_SPACE(x)				((x) & 0x7)
#define _SHORT_GI_PADDING(x)			(((x) & 0x1F) << 3)

#define RXERR_TYPE_OFDM_PPDU			0
#define RXERR_TYPE_OFDM_FALSE_ALARM		1
#define	RXERR_TYPE_OFDM_MPDU_OK			2
#define RXERR_TYPE_OFDM_MPDU_FAIL		3
#define RXERR_TYPE_CCK_PPDU			4
#define RXERR_TYPE_CCK_FALSE_ALARM		5
#define RXERR_TYPE_CCK_MPDU_OK			6
#define RXERR_TYPE_CCK_MPDU_FAIL		7
#define RXERR_TYPE_HT_PPDU			8
#define RXERR_TYPE_HT_FALSE_ALARM		9
#define RXERR_TYPE_HT_MPDU_TOTAL		10
#define RXERR_TYPE_HT_MPDU_OK			11
#define RXERR_TYPE_HT_MPDU_FAIL			12
#define RXERR_TYPE_RX_FULL_DROP			15

#define RXERR_COUNTER_MASK			0xFFFFF
#define RXERR_RPT_RST				BIT(27)
#define _RXERR_RPT_SEL(type)			((type) << 28)

#define	SCR_TxUseDK				BIT(0)
#define	SCR_RxUseDK				BIT(1)
#define	SCR_TxEncEnable				BIT(2)
#define	SCR_RxDecEnable				BIT(3)
#define	SCR_SKByA2				BIT(4)
#define	SCR_NoSKMC				BIT(5)
#define SCR_TXBCUSEDK				BIT(6)
#define SCR_RXBCUSEDK				BIT(7)

#define USB_IS_HIGH_SPEED			0
#define USB_IS_FULL_SPEED			1
#define USB_SPEED_MASK				BIT(5)

#define USB_NORMAL_SIE_EP_MASK			0xF
#define USB_NORMAL_SIE_EP_SHIFT			4

#define USB_TEST_EP_MASK			0x30
#define USB_TEST_EP_SHIFT			4

#define USB_AGG_EN				BIT(3)

#define MAC_ADDR_LEN				6
#define LAST_ENTRY_OF_TX_PKT_BUFFER		175

#define POLLING_LLT_THRESHOLD			20
#define POLLING_READY_TIMEOUT_COUNT		3000

#define	MAX_MSS_DENSITY_2T			0x13
#define	MAX_MSS_DENSITY_1T			0x0A

#define EPROM_CMD_OPERATING_MODE_MASK		((1 << 7) | (1 << 6))
#define EPROM_CMD_CONFIG			0x3
#define EPROM_CMD_LOAD				1

#define	HAL_8822B_HW_GPIO_WPS_BIT		BIT(2)

/*-----------------------------------------------------
 * BB / RF register
 *----------------------------------------------------- */

#define	RFPGA0_XA_HSSIPARAMETER1		0x820
#define	RFPGA0_XA_HSSIPARAMETER2		0x824
#define	RFPGA0_XB_HSSIPARAMETER1		0x828
#define	RFPGA0_XB_HSSIPARAMETER2		0x82c
#define		RCCAONSEC					0x838

#define	RFPGA0_XA_LSSIPARAMETER			0x840
#define	RFPGA0_XB_LSSIPARAMETER			0x844
#define	RL1PEAKTH					0x848

#define	RFPGA0_RFWAKEUPPARAMETER		0x850
#define	RFPGA0_RFSLEEPUPPARAMETER		0x854

#define	RFPGA0_XAB_SWITCHCONTROL		0x858
#define	RFPGA0_XCD_SWITCHCONTROL		0x85c

#define	RFPGA0_XA_RFINTERFACEOE			0x860
#define RFC_AREA					0x860
#define	RFPGA0_XB_RFINTERFACEOE			0x864

#define	RFPGA0_XAB_RFINTERFACESW		0x870
#define	RFPGA0_XCD_RFINTERFACESW		0x874

#define	rFPGA0_XAB_RFPARAMETER			0x878
#define	rFPGA0_XCD_RFPARAMETER			0x87c

#define	RFPGA0_ANALOGPARAMETER1			0x880
#define	RFPGA0_ANALOGPARAMETER2			0x884
#define	RFPGA0_ANALOGPARAMETER3			0x888
#define	RFPGA0_ANALOGPARAMETER4			0x88c

#define	RFPGA0_XA_LSSIREADBACK			0x8a0
#define	RFPGA0_XB_LSSIREADBACK			0x8a4
#define	RFPGA0_XC_LSSIREADBACK			0x8a8
/*#define	RFPGA0_XD_LSSIREADBACK			0x8ac*/
#define RRFMOD						0x8ac
#define	RHSSIREAD_8822BE			0x8b0

#define	RFPGA0_PSDREPORT			0x8b4
#define	TRANSCEIVEA_HSPI_READBACK		0x8b8
#define	TRANSCEIVEB_HSPI_READBACK		0x8bc
/*#define	REG_SC_CNT_8822B				0x8c4*/
#define RADC_BUF_CLK				0x8c4
#define	RFPGA0_XAB_RFINTERFACERB		0x8e0
#define	RFPGA0_XCD_RFINTERFACERB		0x8e4

/* PageB(0xB00) */

/*Page C*/

#define	RA_TXPWRTRAING		0xc54
#define	RB_TXPWRTRAING		0xe54

#define RA_LSSIWRITE_8822B			0xc90
#define RB_LSSIWRITE_8822B			0xe90


#define	RA_PIREAD_8822B		0xd04
#define	RB_PIREAD_8822B		0xd44
#define	RA_SIREAD_8822B		0xd08
#define	RB_SIREAD_8822B		0xd48

#define	RZEBRA1_HSSIENABLE			0x0
#define	RZEBRA1_TRXENABLE1			0x1
#define	RZEBRA1_TRXENABLE2			0x2
#define	RZEBRA1_AGC				0x4
#define	RZEBRA1_CHARGEPUMP			0x5
#define	RZEBRA1_CHANNEL				0x7

#define	RZEBRA1_TXGAIN				0x8
#define	RZEBRA1_TXLPF				0x9
#define	RZEBRA1_RXLPF				0xb
#define	RZEBRA1_RXHPFCORNER			0xc

#define	RGLOBALCTRL				0
#define	RRTL8256_TXLPF				19
#define	RRTL8256_RXLPF				11
#define	RRTL8258_TXLPF				0x11
#define	RRTL8258_RXLPF				0x13
#define	RRTL8258_RSSILPF			0xa

#define	RF_AC					0x00

#define	RF_IQADJ_G1				0x01
#define	RF_IQADJ_G2				0x02
#define	RF_POW_TRSW				0x05

#define	RF_GAIN_RX				0x06
#define	RF_GAIN_TX				0x07

#define	RF_TXM_IDAC				0x08
#define	RF_BS_IQGEN				0x0F

#define	RF_MODE1				0x10
#define	RF_MODE2				0x11

#define	RF_RX_AGC_HP				0x12
#define	RF_TX_AGC				0x13
#define	RF_BIAS					0x14
#define	RF_IPA					0x15
#define	RF_POW_ABILITY				0x17
#define	RF_MODE_AG				0x18
#define	RRFCHANNEL				0x18
#define	RF_CHNLBW				0x18
#define	RF_TOP					0x19

#define	RF_RX_G1				0x1A
#define	RF_RX_G2				0x1B

#define	RF_RX_BB2				0x1C
#define	RF_RX_BB1				0x1D

#define	RF_RCK1					0x1E
#define	RF_RCK2					0x1F

#define	RF_TX_G1				0x20
#define	RF_TX_G2				0x21
#define	RF_TX_G3				0x22

#define	RF_TX_BB1				0x23
#define	RF_T_METER				0x42

#define	RF_SYN_G1				0x25
#define	RF_SYN_G2				0x26
#define	RF_SYN_G3				0x27
#define	RF_SYN_G4				0x28
#define	RF_SYN_G5				0x29
#define	RF_SYN_G6				0x2A
#define	RF_SYN_G7				0x2B
#define	RF_SYN_G8				0x2C

#define	RF_RCK_OS				0x30
#define	RF_TXPA_G1				0x31
#define	RF_TXPA_G2				0x32
#define	RF_TXPA_G3				0x33

#define	RF_TX_BIAS_A				0x35
#define	RF_TX_BIAS_D				0x36
#define	RF_LOBF_9				0x38
#define	RF_RXRF_A3				0x3C
#define	RF_TRSW					0x3F

#define	RF_TXRF_A2				0x41
#define	RF_TXPA_G4				0x46
#define	RF_TXPA_A4				0x4B

#define RF_APK						0x63

#define	RF_WE_LUT				0xEF

#define	BBBRESETB				0x100
#define	BGLOBALRESETB				0x200
#define	BOFDMTXSTART				0x4
#define	BCCKTXSTART				0x8
#define	BCRC32DEBUG				0x100
#define	BPMACLOOPBACK				0x10
#define	BTXLSIG					0xffffff
#define	BOFDMTXRATE				0xf
#define	BOFDMTXRESERVED				0x10
#define	BOFDMTXLENGTH				0x1ffe0
#define	BOFDMTXPARITY				0x20000
#define	BTXHTSIG1				0xffffff
#define	BTXHTMCSRATE				0x7f
#define	BTXHTBW					0x80
#define	BTXHTLENGTH				0xffff00
#define	BTXHTSIG2				0xffffff
#define	BTXHTSMOOTHING				0x1
#define	BTXHTSOUNDING				0x2
#define	BTXHTRESERVED				0x4
#define	BTXHTAGGREATION				0x8
#define	BTXHTSTBC				0x30
#define	BTXHTADVANCECODING			0x40
#define	BTXHTSHORTGI				0x80
#define	BTXHTNUMBERHT_LTF			0x300
#define	BTXHTCRC8				0x3fc00
#define	BCOUNTERRESET				0x10000
#define	BNUMOFOFDMTX				0xffff
#define	BNUMOFCCKTX				0xffff0000
#define	BTXIDLEINTERVAL				0xffff
#define	BOFDMSERVICE				0xffff0000
#define	BTXMACHEADER				0xffffffff
#define	BTXDATAINIT				0xff
#define	BTXHTMODE				0x100
#define	BTXDATATYPE				0x30000
#define	BTXRANDOMSEED				0xffffffff
#define	BCCKTXPREAMBLE				0x1
#define	BCCKTXSFD				0xffff0000
#define	BCCKTXSIG				0xff
#define	BCCKTXSERVICE				0xff00
#define	BCCKLENGTHEXT				0x8000
#define	BCCKTXLENGHT				0xffff0000
#define	BCCKTXCRC16				0xffff
#define	BCCKTXSTATUS				0x1
#define	BOFDMTXSTATUS				0x2
#define IS_BB_REG_OFFSET_92S(_Offset)	\
	((_Offset >= 0x800) && (_Offset <= 0xfff))

#define	BRFMOD						0x1
#define	BJAPANMODE					0x2
#define	BCCKTXSC					0x30
/* Block & Path enable*/
#define ROFDMCCKEN					0x808
#define	BCCKEN						0x10000000
#define	BOFDMEN						0x20000000
/* Rx antenna*/
#define	RRXPATH						0x808
#define	BRXPATH						0xff
/* Tx antenna*/
#define	RTXPATH						0x80c
#define	BTXPATH						0x0fffffff
/* for cck rx path selection*/
#define	RCCK_RX						0xa04
#define	BCCK_RX						0x0c000000
/* Use LSIG for VHT length*/
#define	RVHTLEN_USE_LSIG			0x8c3


#define	BOFDMRXADCPHASE				0x10000
#define	BOFDMTXDACPHASE				0x40000
#define	BXATXAGC				0x3f

#define	BXBTXAGC				0xf00
#define	BXCTXAGC				0xf000
#define	BXDTXAGC				0xf0000

#define	BPASTART				0xf0000000
#define	BTRSTART				0x00f00000
#define	BRFSTART				0x0000f000
#define	BBBSTART				0x000000f0
#define	BBBCCKSTART				0x0000000f
#define	BPAEND					0xf
#define	BTREND					0x0f000000
#define	BRFEND					0x000f0000
#define	BCCAMASK				0x000000f0
#define	BR2RCCAMASK				0x00000f00
#define	BHSSI_R2TDELAY				0xf8000000
#define	BHSSI_T2RDELAY				0xf80000
#define	BCONTXHSSI				0x400
#define	BIGFROMCCK				0x200
#define	BAGCADDRESS				0x3f
#define	BRXHPTX					0x7000
#define	BRXHP2RX				0x38000
#define	BRXHPCCKINI				0xc0000
#define	BAGCTXCODE				0xc00000
#define	BAGCRXCODE				0x300000

#define	B3WIREDATALENGTH			0x800
#define	B3WIREADDREAALENGTH			0x400

#define	B3WIRERFPOWERDOWN			0x1
#define	B5GPAPEPOLARITY				0x40000000
#define	B2GPAPEPOLARITY				0x80000000
#define	BRFSW_TXDEFAULTANT			0x3
#define	BRFSW_TXOPTIONANT			0x30
#define	BRFSW_RXDEFAULTANT			0x300
#define	BRFSW_RXOPTIONANT			0x3000
#define	BRFSI_3WIREDATA				0x1
#define	BRFSI_3WIRECLOCK			0x2
#define	BRFSI_3WIRELOAD				0x4
#define	BRFSI_3WIRERW				0x8
#define	BRFSI_3WIRE				0xf

#define	BRFSI_RFENV				0x10

#define	BRFSI_TRSW				0x20
#define	BRFSI_TRSWB				0x40
#define	BRFSI_ANTSW				0x100
#define	BRFSI_ANTSWB				0x200
#define	BRFSI_PAPE				0x400
#define	BRFSI_PAPE5G				0x800
#define	BBANDSELECT				0x1
#define	BHTSIG2_GI				0x80
#define	BHTSIG2_SMOOTHING			0x01
#define	BHTSIG2_SOUNDING			0x02
#define	BHTSIG2_AGGREATON			0x08
#define	BHTSIG2_STBC				0x30
#define	BHTSIG2_ADVCODING			0x40
#define	BHTSIG2_NUMOFHTLTF			0x300
#define	BHTSIG2_CRC8				0x3fc
#define	BHTSIG1_MCS				0x7f
#define	BHTSIG1_BANDWIDTH			0x80
#define	BHTSIG1_HTLENGTH			0xffff
#define	BLSIG_RATE				0xf
#define	BLSIG_RESERVED				0x10
#define	BLSIG_LENGTH				0x1fffe
#define	BLSIG_PARITY				0x20
#define	BCCKRXPHASE				0x4

#define	BLSSIREADADDRESS			0x7f800000
#define	BLSSIREADEDGE				0x80000000

#define	BLSSIREADBACKDATA			0xfffff

#define	BLSSIREADOKFLAG				0x1000
#define	BCCKSAMPLERATE				0x8
#define	BREGULATOR0STANDBY			0x1
#define	BREGULATORPLLSTANDBY			0x2
#define	BREGULATOR1STANDBY			0x4
#define	BPLLPOWERUP				0x8
#define	BDPLLPOWERUP				0x10
#define	BDA10POWERUP				0x20
#define	BAD7POWERUP				0x200
#define	BDA6POWERUP				0x2000
#define	BXTALPOWERUP				0x4000
#define	B40MDCLKPOWERUP				0x8000
#define	BDA6DEBUGMODE				0x20000
#define	BDA6SWING				0x380000

#define	BADCLKPHASE				0x4000000
#define	B80MCLKDELAY				0x18000000
#define	BAFEWATCHDOGENABLE			0x20000000

#define	BXTALCAP01				0xc0000000
#define	BXTALCAP23				0x3
#define	BXTALCAP92X				0x0f000000
#define BXTALCAP				0x0f000000

#define	BINTDIFCLKENABLE			0x400
#define	BEXTSIGCLKENABLE			0x800
#define	BBANDGAP_MBIAS_POWERUP			0x10000
#define	BAD11SH_GAIN				0xc0000
#define	BAD11NPUT_RANGE				0x700000
#define	BAD110P_CURRENT				0x3800000
#define	BLPATH_LOOPBACK				0x4000000
#define	BQPATH_LOOPBACK				0x8000000
#define	BAFE_LOOPBACK				0x10000000
#define	BDA10_SWING				0x7e0
#define	BDA10_REVERSE				0x800
#define	BDA_CLK_SOURCE				0x1000
#define	BDA7INPUT_RANGE				0x6000
#define	BDA7_GAIN				0x38000
#define	BDA7OUTPUT_CM_MODE			0x40000
#define	BDA7INPUT_CM_MODE			0x380000
#define	BDA7CURRENT				0xc00000
#define	BREGULATOR_ADJUST			0x7000000
#define	BAD11POWERUP_ATTX			0x1
#define	BDA10PS_ATTX				0x10
#define	BAD11POWERUP_ATRX			0x100
#define	BDA10PS_ATRX				0x1000
#define	BCCKRX_AGC_FORMAT			0x200
#define	BPSDFFT_SAMPLE_POINT			0xc000
#define	BPSD_AVERAGE_NUM			0x3000
#define	BIQPATH_CONTROL				0xc00
#define	BPSD_FREQ				0x3ff
#define	BPSD_ANTENNA_PATH			0x30
#define	BPSD_IQ_SWITCH				0x40
#define	BPSD_RX_TRIGGER				0x400000
#define	BPSD_TX_TRIGGER				0x80000000
#define	BPSD_SINE_TONE_SCALE			0x7f000000
#define	BPSD_REPORT				0xffff

#define	BOFDM_TXSC				0x30000000
#define	BCCK_TXON				0x1
#define	BOFDM_TXON				0x2
#define	BDEBUG_PAGE				0xfff
#define	BDEBUG_ITEM				0xff
#define	BANTL					0x10
#define	BANT_NONHT				0x100
#define	BANT_HT1				0x1000
#define	BANT_HT2				0x10000
#define	BANT_HT1S1				0x100000
#define	BANT_NONHTS1				0x1000000

#define	BCCK_BBMODE				0x3
#define	BCCK_TXPOWERSAVING			0x80
#define	BCCK_RXPOWERSAVING			0x40

#define	BCCK_SIDEBAND				0x10

#define	BCCK_SCRAMBLE				0x8
#define	BCCK_ANTDIVERSITY			0x8000
#define	BCCK_CARRIER_RECOVERY			0x4000
#define	BCCK_TXRATE				0x3000
#define	BCCK_DCCANCEL				0x0800
#define	BCCK_ISICANCEL				0x0400
#define	BCCK_MATCH_FILTER			0x0200
#define	BCCK_EQUALIZER				0x0100
#define	BCCK_PREAMBLE_DETECT			0x800000
#define	BCCK_FAST_FALSECCA			0x400000
#define	BCCK_CH_ESTSTART			0x300000
#define	BCCK_CCA_COUNT				0x080000
#define	BCCK_CS_LIM				0x070000
#define	BCCK_BIST_MODE				0x80000000
#define	BCCK_CCAMASK				0x40000000
#define	BCCK_TX_DAC_PHASE			0x4
#define	BCCK_RX_ADC_PHASE			0x20000000
#define	BCCKR_CP_MODE				0x0100
#define	BCCK_TXDC_OFFSET			0xf0
#define	BCCK_RXDC_OFFSET			0xf
#define	BCCK_CCA_MODE				0xc000
#define	BCCK_FALSECS_LIM			0x3f00
#define	BCCK_CS_RATIO				0xc00000
#define	BCCK_CORGBIT_SEL			0x300000
#define	BCCK_PD_LIM				0x0f0000
#define	BCCK_NEWCCA				0x80000000
#define	BCCK_RXHP_OF_IG				0x8000
#define	BCCK_RXIG				0x7f00
#define	BCCK_LNA_POLARITY			0x800000
#define	BCCK_RX1ST_BAIN				0x7f0000
#define	BCCK_RF_EXTEND				0x20000000
#define	BCCK_RXAGC_SATLEVEL			0x1f000000
#define	BCCK_RXAGC_SATCOUNT			0xe0
#define	bCCKRxRFSettle				0x1f
#define	BCCK_FIXED_RXAGC			0x8000
#define	BCCK_ANTENNA_POLARITY			0x2000
#define	BCCK_TXFILTER_TYPE			0x0c00
#define	BCCK_RXAGC_REPORTTYPE			0x0300
#define	BCCK_RXDAGC_EN				0x80000000
#define	BCCK_RXDAGC_PERIOD			0x20000000
#define	BCCK_RXDAGC_SATLEVEL			0x1f000000
#define	BCCK_TIMING_RECOVERY			0x800000
#define	BCCK_TXC0				0x3f0000
#define	BCCK_TXC1				0x3f000000
#define	BCCK_TXC2				0x3f
#define	BCCK_TXC3				0x3f00
#define	BCCK_TXC4				0x3f0000
#define	BCCK_TXC5				0x3f000000
#define	BCCK_TXC6				0x3f
#define	BCCK_TXC7				0x3f00
#define	BCCK_DEBUGPORT				0xff0000
#define	BCCK_DAC_DEBUG				0x0f000000
#define	BCCK_FALSEALARM_ENABLE			0x8000
#define	BCCK_FALSEALARM_READ			0x4000
#define	BCCK_TRSSI				0x7f
#define	BCCK_RXAGC_REPORT			0xfe
#define	BCCK_RXREPORT_ANTSEL			0x80000000
#define	BCCK_RXREPORT_MFOFF			0x40000000
#define	BCCK_RXREPORT_SQLOSS			0x20000000
#define	BCCK_RXREPORT_PKTLOSS			0x10000000
#define	BCCK_RXREPORT_LOCKEDBIT			0x08000000
#define	BCCK_RXREPORT_RATEERROR			0x04000000
#define	BCCK_RXREPORT_RXRATE			0x03000000
#define	BCCK_RXFA_COUNTER_LOWER			0xff
#define	BCCK_RXFA_COUNTER_UPPER			0xff000000
#define	BCCK_RXHPAGC_START			0xe000
#define	BCCK_RXHPAGC_FINAL			0x1c00
#define	BCCK_RXFALSEALARM_ENABLE		0x8000
#define	BCCK_FACOUNTER_FREEZE			0x4000
#define	BCCK_TXPATH_SEL				0x10000000
#define	BCCK_DEFAULT_RXPATH			0xc000000
#define	BCCK_OPTION_RXPATH			0x3000000

#define	BNUM_OFSTF				0x3
#define	BSHIFT_L				0xc0
#define	BGI_TH					0xc
#define	BRXPATH_A				0x1
#define	BRXPATH_B				0x2
#define	BRXPATH_C				0x4
#define	BRXPATH_D				0x8
#define	BTXPATH_A				0x1
#define	BTXPATH_B				0x2
#define	BTXPATH_C				0x4
#define	BTXPATH_D				0x8
#define	BTRSSI_FREQ				0x200
#define	BADC_BACKOFF				0x3000
#define	BDFIR_BACKOFF				0xc000
#define	BTRSSI_LATCH_PHASE			0x10000
#define	BRX_LDC_OFFSET				0xff
#define	BRX_QDC_OFFSET				0xff00
#define	BRX_DFIR_MODE				0x1800000
#define	BRX_DCNF_TYPE				0xe000000
#define	BRXIQIMB_A				0x3ff
#define	BRXIQIMB_B				0xfc00
#define	BRXIQIMB_C				0x3f0000
#define	BRXIQIMB_D				0xffc00000
#define	BDC_DC_NOTCH				0x60000
#define	BRXNB_NOTCH				0x1f000000
#define	BPD_TH					0xf
#define	BPD_TH_OPT2				0xc000
#define	BPWED_TH				0x700
#define	BIFMF_WIN_L				0x800
#define	BPD_OPTION				0x1000
#define	BMF_WIN_L				0xe000
#define	BBW_SEARCH_L				0x30000
#define	BWIN_ENH_L				0xc0000
#define	BBW_TH					0x700000
#define	BED_TH2					0x3800000
#define	BBW_OPTION				0x4000000
#define	BRADIO_TH				0x18000000
#define	BWINDOW_L				0xe0000000
#define	BSBD_OPTION				0x1
#define	BFRAME_TH				0x1c
#define	BFS_OPTION				0x60
#define	BDC_SLOPE_CHECK				0x80
#define	BFGUARD_COUNTER_DC_L			0xe00
#define	BFRAME_WEIGHT_SHORT			0x7000
#define	BSUB_TUNE				0xe00000
#define	BFRAME_DC_LENGTH			0xe000000
#define	BSBD_START_OFFSET			0x30000000
#define	BFRAME_TH_2				0x7
#define	BFRAME_GI2_TH				0x38
#define	BGI2_SYNC_EN				0x40
#define	BSARCH_SHORT_EARLY			0x300
#define	BSARCH_SHORT_LATE			0xc00
#define	BSARCH_GI2_LATE				0x70000
#define	BCFOANTSUM				0x1
#define	BCFOACC					0x2
#define	BCFOSTARTOFFSET				0xc
#define	BCFOLOOPBACK				0x70
#define	BCFOSUMWEIGHT				0x80
#define	BDAGCENABLE				0x10000
#define	BTXIQIMB_A				0x3ff
#define	BTXIQIMB_b				0xfc00
#define	BTXIQIMB_C				0x3f0000
#define	BTXIQIMB_D				0xffc00000
#define	BTXIDCOFFSET				0xff
#define	BTXIQDCOFFSET				0xff00
#define	BTXDFIRMODE				0x10000
#define	BTXPESUDO_NOISEON			0x4000000
#define	BTXPESUDO_NOISE_A			0xff
#define	BTXPESUDO_NOISE_B			0xff00
#define	BTXPESUDO_NOISE_C			0xff0000
#define	BTXPESUDO_NOISE_D			0xff000000
#define	BCCA_DROPOPTION				0x20000
#define	BCCA_DROPTHRES				0xfff00000
#define	BEDCCA_H				0xf
#define	BEDCCA_L				0xf0
#define	BLAMBDA_ED				0x300
#define	BRX_INITIALGAIN				0x7f
#define	BRX_ANTDIV_EN				0x80
#define	BRX_AGC_ADDRESS_FOR_LNA			0x7f00
#define	BRX_HIGHPOWER_FLOW			0x8000
#define	BRX_AGC_FREEZE_THRES			0xc0000
#define	BRX_FREEZESTEP_AGC1			0x300000
#define	BRX_FREEZESTEP_AGC2			0xc00000
#define	BRX_FREEZESTEP_AGC3			0x3000000
#define	BRX_FREEZESTEP_AGC0			0xc000000
#define	BRXRSSI_CMP_EN				0x10000000
#define	BRXQUICK_AGCEN				0x20000000
#define	BRXAGC_FREEZE_THRES_MODE		0x40000000
#define	BRX_OVERFLOW_CHECKTYPE			0x80000000
#define	BRX_AGCSHIFT				0x7f
#define	BTRSW_TRI_ONLY				0x80
#define	BPOWER_THRES				0x300
#define	BRXAGC_EN				0x1
#define	BRXAGC_TOGETHER_EN			0x2
#define	BRXAGC_MIN				0x4
#define	BRXHP_INI				0x7
#define	BRXHP_TRLNA				0x70
#define	BRXHP_RSSI				0x700
#define	BRXHP_BBP1				0x7000
#define	BRXHP_BBP2				0x70000
#define	BRXHP_BBP3				0x700000
#define	BRSSI_H					0x7f0000
#define	BRSSI_GEN				0x7f000000
#define	BRXSETTLE_TRSW				0x7
#define	BRXSETTLE_LNA				0x38
#define	BRXSETTLE_RSSI				0x1c0
#define	BRXSETTLE_BBP				0xe00
#define	BRXSETTLE_RXHP				0x7000
#define	BRXSETTLE_ANTSW_RSSI			0x38000
#define	BRXSETTLE_ANTSW				0xc0000
#define	BRXPROCESS_TIME_DAGC			0x300000
#define	BRXSETTLE_HSSI				0x400000
#define	BRXPROCESS_TIME_BBPPW			0x800000
#define	BRXANTENNA_POWER_SHIFT			0x3000000
#define	BRSSI_TABLE_SELECT			0xc000000
#define	BRXHP_FINAL				0x7000000
#define	BRXHPSETTLE_BBP				0x7
#define	BRXHTSETTLE_HSSI			0x8
#define	BRXHTSETTLE_RXHP			0x70
#define	BRXHTSETTLE_BBPPW			0x80
#define	BRXHTSETTLE_IDLE			0x300
#define	BRXHTSETTLE_RESERVED			0x1c00
#define	BRXHT_RXHP_EN				0x8000
#define	BRXAGC_FREEZE_THRES			0x30000
#define	BRXAGC_TOGETHEREN			0x40000
#define	BRXHTAGC_MIN				0x80000
#define	BRXHTAGC_EN				0x100000
#define	BRXHTDAGC_EN				0x200000
#define	BRXHT_RXHP_BBP				0x1c00000
#define	BRXHT_RXHP_FINAL			0xe0000000
#define	BRXPW_RADIO_TH				0x3
#define	BRXPW_RADIO_EN				0x4
#define	BRXMF_HOLD				0x3800
#define	BRXPD_DELAY_TH1				0x38
#define	BRXPD_DELAY_TH2				0x1c0
#define	BRXPD_DC_COUNT_MAX			0x600
#define	BRXPD_DELAY_TH				0x8000
#define	BRXPROCESS_DELAY			0xf0000
#define	BRXSEARCHRANGE_GI2_EARLY		0x700000
#define	BRXFRAME_FUARD_COUNTER_L		0x3800000
#define	BRXSGI_GUARD_L				0xc000000
#define	BRXSGI_SEARCH_L				0x30000000
#define	BRXSGI_TH				0xc0000000
#define	BDFSCNT0				0xff
#define	BDFSCNT1				0xff00
#define	BDFSFLAG				0xf0000
#define	BMF_WEIGHT_SUM				0x300000
#define	BMINIDX_TH				0x7f000000
#define	BDAFORMAT				0x40000
#define	BTXCH_EMU_ENABLE			0x01000000
#define	BTRSW_ISOLATION_A			0x7f
#define	BTRSW_ISOLATION_B			0x7f00
#define	BTRSW_ISOLATION_C			0x7f0000
#define	BTRSW_ISOLATION_D			0x7f000000
#define	BEXT_LNA_GAIN				0x7c00

#define	BSTBC_EN				0x4
#define	BANTENNA_MAPPING			0x10
#define	BNSS					0x20
#define	BCFO_ANTSUM_ID				0x200
#define	BPHY_COUNTER_RESET			0x8000000
#define	BCFO_REPORT_GET				0x4000000
#define	BOFDM_CONTINUE_TX			0x10000000
#define	BOFDM_SINGLE_CARRIER			0x20000000
#define	BOFDM_SINGLE_TONE			0x40000000
#define	BHT_DETECT				0x100
#define	BCFOEN					0x10000
#define	BCFOVALUE				0xfff00000
#define	BSIGTONE_RE				0x3f
#define	BSIGTONE_IM				0x7f00
#define	BCOUNTER_CCA				0xffff
#define	BCOUNTER_PARITYFAIL			0xffff0000
#define	BCOUNTER_RATEILLEGAL			0xffff
#define	BCOUNTER_CRC8FAIL			0xffff0000
#define	BCOUNTER_MCSNOSUPPORT			0xffff
#define	BCOUNTER_FASTSYNC			0xffff
#define	BSHORTCFO				0xfff
#define	BSHORTCFOT_LENGTH			12
#define	BSHORTCFOF_LENGTH			11
#define	BLONGCFO				0x7ff
#define	BLONGCFOT_LENGTH			11
#define	BLONGCFOF_LENGTH			11
#define	BTAILCFO				0x1fff
#define	BTAILCFOT_LENGTH			13
#define	BTAILCFOF_LENGTH			12
#define	BNOISE_EN_PWDB				0xffff
#define	BCC_POWER_DB				0xffff0000
#define	BMOISE_PWDB				0xffff
#define	BPOWERMEAST_LENGTH			10
#define	BPOWERMEASF_LENGTH			3
#define	BRX_HT_BW				0x1
#define	BRXSC					0x6
#define	BRX_HT					0x8
#define	BNB_INTF_DET_ON				0x1
#define	BINTF_WIN_LEN_CFG			0x30
#define	BNB_INTF_TH_CFG				0x1c0
#define	BRFGAIN					0x3f
#define	BTABLESEL				0x40
#define	BTRSW					0x80
#define	BRXSNR_A				0xff
#define	BRXSNR_B				0xff00
#define	BRXSNR_C				0xff0000
#define	BRXSNR_D				0xff000000
#define	BSNR_EVMT_LENGTH			8
#define	BSNR_EVMF_LENGTH			1
#define	BCSI1ST					0xff
#define	BCSI2ND					0xff00
#define	BRXEVM1ST				0xff0000
#define	BRXEVM2ND				0xff000000
#define	BSIGEVM					0xff
#define	BPWDB					0xff00
#define	BSGIEN					0x10000

#define	BSFACTOR_QMA1				0xf
#define	BSFACTOR_QMA2				0xf0
#define	BSFACTOR_QMA3				0xf00
#define	BSFACTOR_QMA4				0xf000
#define	BSFACTOR_QMA5				0xf0000
#define	BSFACTOR_QMA6				0xf0000
#define	BSFACTOR_QMA7				0xf00000
#define	BSFACTOR_QMA8				0xf000000
#define	BSFACTOR_QMA9				0xf0000000
#define	BCSI_SCHEME				0x100000

#define	BNOISE_LVL_TOP_SET			0x3
#define	BCHSMOOTH				0x4
#define	BCHSMOOTH_CFG1				0x38
#define	BCHSMOOTH_CFG2				0x1c0
#define	BCHSMOOTH_CFG3				0xe00
#define	BCHSMOOTH_CFG4				0x7000
#define	BMRCMODE				0x800000
#define	BTHEVMCFG				0x7000000

#define	BLOOP_FIT_TYPE				0x1
#define	BUPD_CFO				0x40
#define	BUPD_CFO_OFFDATA			0x80
#define	BADV_UPD_CFO				0x100
#define	BADV_TIME_CTRL				0x800
#define	BUPD_CLKO				0x1000
#define	BFC					0x6000
#define	BTRACKING_MODE				0x8000
#define	BPHCMP_ENABLE				0x10000
#define	BUPD_CLKO_LTF				0x20000
#define	BCOM_CH_CFO				0x40000
#define	BCSI_ESTI_MODE				0x80000
#define	BADV_UPD_EQZ				0x100000
#define	BUCHCFG					0x7000000
#define	BUPDEQZ					0x8000000

#define	BRX_PESUDO_NOISE_ON			0x20000000
#define	BRX_PESUDO_NOISE_A			0xff
#define	BRX_PESUDO_NOISE_B			0xff00
#define	BRX_PESUDO_NOISE_C			0xff0000
#define	BRX_PESUDO_NOISE_D			0xff000000
#define	BRX_PESUDO_NOISESTATE_A			0xffff
#define	BRX_PESUDO_NOISESTATE_B			0xffff0000
#define	BRX_PESUDO_NOISESTATE_C			0xffff
#define	BRX_PESUDO_NOISESTATE_D			0xffff0000

#define	BZEBRA1_HSSIENABLE			0x8
#define	BZEBRA1_TRXCONTROL			0xc00
#define	BZEBRA1_TRXGAINSETTING			0x07f
#define	BZEBRA1_RXCOUNTER			0xc00
#define	BZEBRA1_TXCHANGEPUMP			0x38
#define	BZEBRA1_RXCHANGEPUMP			0x7
#define	BZEBRA1_CHANNEL_NUM			0xf80
#define	BZEBRA1_TXLPFBW				0x400
#define	BZEBRA1_RXLPFBW				0x600

#define	BRTL8256REG_MODE_CTRL1			0x100
#define	BRTL8256REG_MODE_CTRL0			0x40
#define	BRTL8256REG_TXLPFBW			0x18
#define	BRTL8256REG_RXLPFBW			0x600

#define	BRTL8258_TXLPFBW			0xc
#define	BRTL8258_RXLPFBW			0xc00
#define	BRTL8258_RSSILPFBW			0xc0

#define	BBYTE0					0x1
#define	BBYTE1					0x2
#define	BBYTE2					0x4
#define	BBYTE3					0x8
#define	BWORD0					0x3
#define	BWORD1					0xc
#define	BWORD					0xf

#define	MASKBYTE0				0xff
#define	MASKBYTE1				0xff00
#define	MASKBYTE2				0xff0000
#define	MASKBYTE3				0xff000000
#define	MASKHWORD				0xffff0000
#define	MASKLWORD				0x0000ffff
#define	MASKDWORD				0xffffffff
#define	MASK12BITS				0xfff
#define	MASKH4BITS				0xf0000000
#define MASKOFDM_D				0xffc00000
#define	MASKCCK					0x3f3f3f3f

#define	MASK4BITS				0x0f
#define	MASK20BITS				0xfffff
#define RFREG_OFFSET_MASK			0xfffff

#define	BMASKBYTE0			0xff
#define	BMASKBYTE1			0xff00
#define	BMASKBYTE2			0xff0000
#define	BMASKBYTE3			0xff000000
#define	BMASKHWORD			0xffff0000
#define	BMASKLWORD			0x0000ffff
#define	BMASKDWORD			0xffffffff
#define	BMASK12BITS					0xfff
#define	BMASKH4BITS					0xf0000000
#define BMASKOFDM_D					0xffc00000
#define	BMASKCCK					0x3f3f3f3f

#define BRFREGOFFSETMASK			0xfffff

/* WOL bit information */
#define WOL_REASON_PTK_UPDATE			BIT(0)
#define WOL_REASON_GTK_UPDATE			BIT(1)
#define WOL_REASON_DISASSOC			BIT(2)
#define WOL_REASON_DEAUTH			BIT(3)
#define WOL_REASON_FW_DISCONNECT		BIT(4)




#endif
