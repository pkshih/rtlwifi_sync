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

#ifndef __RTL8822B_TRX_H__
#define __RTL8822B_TRX_H__

#include "../halmac/halmac_hw_cfg.h"
#include "../halmac/halmac_tx_desc_nic.h"
#include "../halmac/halmac_rx_desc_nic.h"


#if (DMA_IS_64BIT == 1)
#if (RTL8822BE_SEG_NUM == 2)
#define TX_BD_DESC_SIZE					128
#elif (RTL8822BE_SEG_NUM == 1)
#define TX_BD_DESC_SIZE					64
#elif (RTL8822BE_SEG_NUM == 0)
#define TX_BD_DESC_SIZE					32
#endif
#else
#if (RTL8822BE_SEG_NUM == 2)
#define TX_BD_DESC_SIZE					64
#elif (RTL8822BE_SEG_NUM == 1)
#define TX_BD_DESC_SIZE					32
#elif (RTL8822BE_SEG_NUM == 0)
#define TX_BD_DESC_SIZE					16
#endif
#endif

#define TX_DESC_SIZE					64

#define RX_DRV_INFO_SIZE_UNIT				8

#define	TX_DESC_NEXT_DESC_OFFSET			48
#define USB_HWDESC_HEADER_LEN				48

#define RX_DESC_SIZE					24
#define MAX_RECEIVE_BUFFER_SIZE				8192

#if 0

/* TX desc */
/* Dword 0 */
#define SET_TX_DESC_DISQSELSEQ(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 31, 1, __Value)
#define GET_TX_DESC_DISQSELSEQ(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 31, 1)
#define SET_TX_DESC_GF(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 30, 1, __Value)
#define GET_TX_DESC_GF(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 30, 1)
#define SET_TX_DESC_NO_ACM(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 29, 1, __Value)
#define GET_TX_DESC_NO_ACM(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 29, 1)
#define SET_TX_DESC_BCNPKT_TSF_CTRL(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 28, 1, __Value)
#define GET_TX_DESC_BCNPKT_TSF_CTRL(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 28, 1)
#define SET_TX_DESC_AMSDU_PAD_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 27, 1, __Value)
#define GET_TX_DESC_AMSDU_PAD_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 27, 1)
#define SET_TX_DESC_LS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 26, 1, __Value)
#define GET_TX_DESC_LS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 26, 1)
#define SET_TX_DESC_HTC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 25, 1, __Value)
#define GET_TX_DESC_HTC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 25, 1)
#define SET_TX_DESC_BMC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 24, 1, __Value)
#define GET_TX_DESC_BMC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 24, 1)
#define SET_TX_DESC_OFFSET(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 16, 8, __Value)
#define GET_TX_DESC_OFFSET(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 16, 8)
#define SET_TX_DESC_TXPKTSIZE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x00, 0, 16, __Value)
#define GET_TX_DESC_TXPKTSIZE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x00, 0, 16)

/* Dword 1 */
#define SET_TX_DESC_MOREDATA(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 29, 1, __Value)
#define GET_TX_DESC_MOREDATA(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 29, 1)
#define SET_TX_DESC_PKT_OFFSET(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 24, 5, __Value)
#define GET_TX_DESC_PKT_OFFSET(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 24, 5)
#define SET_TX_DESC_SEC_TYPE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 22, 2, __Value)
#define GET_TX_DESC_SEC_TYPE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 22, 2)
#define SET_TX_DESC_EN_DESC_ID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 21, 1, __Value)
#define GET_TX_DESC_EN_DESC_ID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 21, 1)
#define SET_TX_DESC_RATE_ID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 16, 5, __Value)
#define GET_TX_DESC_RATE_ID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 16, 5)
#define SET_TX_DESC_PIFS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 15, 1, __Value)
#define GET_TX_DESC_PIFS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 15, 1)
#define SET_TX_DESC_LSIG_TXOP_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 14, 1, __Value)
#define GET_TX_DESC_LSIG_TXOP_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 14, 1)
#define SET_TX_DESC_RD_NAV_EXT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 13, 1, __Value)
#define GET_TX_DESC_RD_NAV_EXT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 13, 1)
#define SET_TX_DESC_QSEL(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 8, 5, __Value)
#define GET_TX_DESC_QSEL(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 8, 5)
#define SET_TX_DESC_MACID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x04, 0, 7, __Value)
#define GET_TX_DESC_MACID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x04, 0, 7)

/* Dword 2 */
#define SET_TX_DESC_HW_AES_IV(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 31, 1, __Value)
#define GET_TX_DESC_HW_AES_IV(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 31, 1)
#define SET_TX_DESC_FTM_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 30, 1, __Value)
#define GET_TX_DESC_FTM_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 30, 1)
#define SET_TX_DESC_G_ID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 24, 6, __Value)
#define GET_TX_DESC_G_ID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 24, 6)
#define SET_TX_DESC_BT_NULL(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 23, 1, __Value)
#define GET_TX_DESC_BT_NULL(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 23, 1)
#define SET_TX_DESC_AMPDU_DENSITY(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 20, 3, __Value)
#define GET_TX_DESC_AMPDU_DENSITY(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 20, 3)
#define SET_TX_DESC_SPE_RPT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 19, 1, __Value)
#define GET_TX_DESC_SPE_RPT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 19, 1)
#define SET_TX_DESC_RAW(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 18, 1, __Value)
#define GET_TX_DESC_RAW(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 18, 1)
#define SET_TX_DESC_MOREFRAG(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 17, 1, __Value)
#define GET_TX_DESC_MOREFRAG(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 17, 1)
#define SET_TX_DESC_BK(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 16, 1, __Value)
#define GET_TX_DESC_BK(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 16, 1)
#define SET_TX_DESC_NULL_1(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 15, 1, __Value)
#define GET_TX_DESC_NULL_1(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 15, 1)
#define SET_TX_DESC_NULL_0(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 14, 1, __Value)
#define GET_TX_DESC_NULL_0(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 14, 1)
#define SET_TX_DESC_RDG_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 13, 1, __Value)
#define GET_TX_DESC_RDG_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 13, 1)
#define SET_TX_DESC_AGG_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 12, 1, __Value)
#define GET_TX_DESC_AGG_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 12, 1)
#define SET_TX_DESC_CCA_RTS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 10, 2, __Value)
#define GET_TX_DESC_CCA_RTS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 10, 2)
#define SET_TX_DESC_TRI_FRAME(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 9, 1, __Value)
#define GET_TX_DESC_TRI_FRAME(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 9, 1)
#define SET_TX_DESC_P_AID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x08, 0, 9, __Value)
#define GET_TX_DESC_P_AID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x08, 0, 9)

/* Dword 3 */
#define SET_TX_DESC_AMPDU_MAX_TIME(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 24, 8, __Value)
#define GET_TX_DESC_AMPDU_MAX_TIME(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 24, 8)
#define SET_TX_DESC_NDPA(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 22, 2, __Value)
#define GET_TX_DESC_NDPA(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 22, 2)
#define SET_TX_DESC_MAX_AGG_NUM(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 17, 5, __Value)
#define GET_TX_DESC_MAX_AGG_NUM(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 17, 5)
#define SET_TX_DESC_USE_MAX_TIME_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 16, 1, __Value)
#define GET_TX_DESC_USE_MAX_TIME_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 16, 1)
#define SET_TX_DESC_NAVUSEHDR(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 15, 1, __Value)
#define GET_TX_DESC_NAVUSEHDR(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 15, 1)
#define SET_TX_DESC_CHK_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 14, 1, __Value)
#define GET_TX_DESC_CHK_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 14, 1)
#define SET_TX_DESC_HW_RTS_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 13, 1, __Value)
#define GET_TX_DESC_HW_RTS_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 13, 1)
#define SET_TX_DESC_RTSEN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 12, 1, __Value)
#define GET_TX_DESC_RTSEN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 12, 1)
#define SET_TX_DESC_CTS2SELF(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 11, 1, __Value)
#define GET_TX_DESC_CTS2SELF(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 11, 1)
#define SET_TX_DESC_DISDATAFB(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 10, 1, __Value)
#define GET_TX_DESC_DISDATAFB(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 10, 1)
#define SET_TX_DESC_DISRTSFB(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 9, 1, __Value)
#define GET_TX_DESC_DISRTSFB(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 9, 1)
#define SET_TX_DESC_USE_RATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 8, 1, __Value)
#define GET_TX_DESC_USE_RATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 8, 1)
#define SET_TX_DESC_HW_SSN_SEL(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 6, 2, __Value)
#define GET_TX_DESC_HW_SSN_SEL(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 6, 2)
#define SET_TX_DESC_WHEADER_LEN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x0C, 0, 5, __Value)
#define GET_TX_DESC_WHEADER_LEN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x0C, 0, 5)



/* Dword 4 */
#define SET_TX_DESC_PCTS_MASK_IDX(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 30, 2, __Value)
#define GET_TX_DESC_PCTS_MASK_IDX(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 30, 2)
#define SET_TX_DESC_PCTS_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 29, 1, __Value)
#define GET_TX_DESC_PCTS_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 29, 1)
#define SET_TX_DESC_RTSRATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 24, 5, __Value)
#define GET_TX_DESC_RTSRATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 24, 5)
#define SET_TX_DESC_RTS_DATA_RTY_LMT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 18, 6, __Value)
#define GET_TX_DESC_RTS_DATA_RTY_LMT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 18, 6)
#define SET_TX_DESC_RTY_LMT_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 17, 1, __Value)
#define GET_TX_DESC_RTY_LMT_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 17, 1)
#define SET_TX_DESC_RTS_RTY_LOWEST_RATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 13, 4, __Value)
#define GET_TX_DESC_RTS_RTY_LOWEST_RATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 13, 4)
#define SET_TX_DESC_DATA_RTY_LOWEST_RATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 8, 5, __Value)
#define GET_TX_DESC_DATA_RTY_LOWEST_RATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 8, 5)
#define SET_TX_DESC_TRY_RATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 7, 1, __Value)
#define GET_TX_DESC_TRY_RATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 7, 1)
#define SET_TX_DESC_DATARATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x10, 0, 7, __Value)
#define GET_TX_DESC_DATARATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x10, 0, 7)


/* Dword 5 */
#define SET_TX_DESC_POLLUTED(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 31, 1, __Value)
#define GET_TX_DESC_POLLUTED(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 31, 1)
#define SET_TX_DESC_TXPWR_OFSET(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 28, 3, __Value)
#define GET_TX_DESC_TXPWR_OFSET(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 28, 3)
#define SET_TX_DESC_TX_ANT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 24, 4, __Value)
#define GET_TX_DESC_TX_ANT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 24, 4)
#define SET_TX_DESC_PORT_ID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 21, 3, __Value)
#define GET_TX_DESC_PORT_ID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 21, 3)
#define SET_TX_DESC_MULTIPLE_PORT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 18, 3, __Value)
#define GET_TX_DESC_MULTIPLE_PORT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 18, 3)
#define SET_TX_DESC_SIGNALING_TAPKT_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 17, 1, __Value)
#define GET_TX_DESC_SIGNALING_TAPKT_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 17, 1)
#define SET_TX_DESC_RTS_SC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 13, 4, __Value)
#define GET_TX_DESC_RTS_SC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 13, 4)
#define SET_TX_DESC_RTS_SHORT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 12, 1, __Value)
#define GET_TX_DESC_RTS_SHORT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 12, 1)
#define SET_TX_DESC_VCS_STBC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 10, 2, __Value)
#define GET_TX_DESC_VCS_STBC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 10, 2)
#define SET_TX_DESC_DATA_STBC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 8, 2, __Value)
#define GET_TX_DESC_DATA_STBC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 8, 2)
#define SET_TX_DESC_DATA_LDPC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 7, 1, __Value)
#define GET_TX_DESC_DATA_LDPC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 7, 1)
#define SET_TX_DESC_DATA_BW(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 5, 2, __Value)
#define GET_TX_DESC_DATA_BW(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 5, 2)
#define SET_TX_DESC_DATA_SHORT(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 4, 1, __Value)
#define GET_TX_DESC_DATA_SHORT(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 4, 1)
#define SET_TX_DESC_DATA_SC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x14, 0, 4, __Value)
#define GET_TX_DESC_DATA_SC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x14, 0, 4)

/* Dword 6 */
#define SET_TX_DESC_ANTSEL_D(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 30, 2, __Value)
#define GET_TX_DESC_ANTSEL_D(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 30, 2)
#define SET_TX_DESC_ANT_MAPD(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 28, 2, __Value)
#define GET_TX_DESC_ANT_MAPD(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 28, 2)
#define SET_TX_DESC_ANT_MAPC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 26, 2, __Value)
#define GET_TX_DESC_ANT_MAPC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 26, 2)
#define SET_TX_DESC_ANT_MAPB(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 24, 2, __Value)
#define GET_TX_DESC_ANT_MAPB(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 24, 2)
#define SET_TX_DESC_ANT_MAPA(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 22, 2, __Value)
#define GET_TX_DESC_ANT_MAPA(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 22, 2)
#define SET_TX_DESC_ANTSEL_C(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 20, 2, __Value)
#define GET_TX_DESC_ANTSEL_C(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 20, 2)
#define SET_TX_DESC_ANTSEL_B(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 18, 2, __Value)
#define GET_TX_DESC_ANTSEL_B(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 18, 2)
#define SET_TX_DESC_ANTSEL_A(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 16, 2, __Value)
#define GET_TX_DESC_ANTSEL_A(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 16, 2)
#define SET_TX_DESC_MBSSID(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 12, 4, __Value)
#define GET_TX_DESC_MBSSID(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 12, 4)
#define SET_TX_DESC_SW_DEFINE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x18, 0, 12, __Value)
#define GET_TX_DESC_SW_DEFINE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x18, 0, 12)


/* Dword 7 */
#define SET_TX_DESC_DMA_TXAGG_NUM(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 24, 8, __Value)
#define GET_TX_DESC_DMA_TXAGG_NUM(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 24, 8)
#define SET_TX_DESC_FINAL_DATA_RATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 24, 8, __Value)
#define GET_TX_DESC_FINAL_DATA_RATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 24, 8)
#define SET_TX_DESC_NTX_MAP(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 20, 4, __Value)
#define GET_TX_DESC_NTX_MAP(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 20, 4)
#define SET_TX_DESC_TX_BUFF_SIZE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 0, 16, __Value)
#define GET_TX_DESC_TX_BUFF_SIZE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 0, 16)
#define SET_TX_DESC_TXDESC_CHECKSUM(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 0, 16, __Value)
#define GET_TX_DESC_TXDESC_CHECKSUM(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 0, 16)
#define SET_TX_DESC_TIMESTAMP(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x1C, 0, 16, __Value)
#define GET_TX_DESC_TIMESTAMP(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x1C, 0, 16)


/* Dword 8 */
#define SET_TX_DESC_TXWIFI_CP(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 31, 1, __Value)
#define GET_TX_DESC_TXWIFI_CP(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 31, 1)
#define SET_TX_DESC_MAC_CP(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 30, 1, __Value)
#define GET_TX_DESC_MAC_CP(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 30, 1)
#define SET_TX_DESC_STW_PKTRE_DIS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 29, 1, __Value)
#define GET_TX_DESC_STW_PKTRE_DIS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 29, 1)
#define SET_TX_DESC_STW_RB_DIS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 28, 1, __Value)
#define GET_TX_DESC_STW_RB_DIS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 28, 1)
#define SET_TX_DESC_STW_RATE_DIS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 27, 1, __Value)
#define GET_TX_DESC_STW_RATE_DIS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 27, 1)
#define SET_TX_DESC_STW_ANT_DIS(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 26, 1, __Value)
#define GET_TX_DESC_STW_ANT_DIS(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 26, 1)
#define SET_TX_DESC_STW_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 25, 1, __Value)
#define GET_TX_DESC_STW_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 25, 1)
#define SET_TX_DESC_SMH_EN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 24, 1, __Value)
#define GET_TX_DESC_SMH_EN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 24, 1)
#define SET_TX_DESC_TAILPAGE_L(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 24, 8, __Value)
#define GET_TX_DESC_TAILPAGE_L(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 24, 8)
#define SET_TX_DESC_SDIO_DMASEQ(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 16, 8, __Value)
#define GET_TX_DESC_SDIO_DMASEQ(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 16, 8)
#define SET_TX_DESC_NEXTHEADPAGE_L(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 16, 8, __Value)
#define GET_TX_DESC_NEXTHEADPAGE_L(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 16, 8)
#define SET_TX_DESC_EN_HWSEQ(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 15, 1, __Value)
#define GET_TX_DESC_EN_HWSEQ(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 15, 1)
#define SET_TX_DESC_EN_HWEXSEQ(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 14, 1, __Value)
#define GET_TX_DESC_EN_HWEXSEQ(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 14, 1)
#define SET_TX_DESC_DATA_RC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 8, 6, __Value)
#define GET_TX_DESC_DATA_RC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 8, 6)
#define SET_TX_DESC_BAR_RTY_TH(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 6, 2, __Value)
#define GET_TX_DESC_BAR_RTY_TH(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 6, 2)
#define SET_TX_DESC_RTS_RC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x20, 0, 6, __Value)
#define GET_TX_DESC_RTS_RC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x20, 0, 6)


/* Dword 9 */
#define SET_TX_DESC_TAILPAGE_H(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 28, 4, __Value)
#define GET_TX_DESC_TAILPAGE_H(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 28, 4)
#define SET_TX_DESC_NEXTHEADPAGE_H(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 24, 4, __Value)
#define GET_TX_DESC_NEXTHEADPAGE_H(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 24, 4)
#define SET_TX_DESC_SW_SEQ(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 12, 12, __Value)
#define GET_TX_DESC_SW_SEQ(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 12, 12)
#define SET_TX_DESC_TXBF_PATH(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 11, 1, __Value)
#define GET_TX_DESC_TXBF_PATH(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 11, 1)
#define SET_TX_DESC_PADDING_LEN(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 0, 11, __Value)
#define GET_TX_DESC_PADDING_LEN(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 0, 11)
#define SET_TX_DESC_GROUP_BIT_IE_OFFSET(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x24, 0, 8, __Value)
#define GET_TX_DESC_GROUP_BIT_IE_OFFSET(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x24, 0, 8)


/* Dword 10 */
#define SET_TX_DESC_MU_DATARATE(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x28, 8, 8, __Value)
#define GET_TX_DESC_MU_DATARATE(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x28, 8, 8)
#define SET_TX_DESC_MU_RC(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x28, 4, 4, __Value)
#define GET_TX_DESC_MU_RC(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x28, 4, 4)
#define SET_TX_DESC_SND_PKT_SEL(__pTxDesc, __Value)    SET_BITS_TO_LE_4BYTE(__pTxDesc + 0x28, 0, 2, __Value)
#define GET_TX_DESC_SND_PKT_SEL(__pTxDesc)    LE_BITS_TO_4BYTE(__pTxDesc + 0x28, 0, 2)

#endif

#define SET_EARLYMODE_PKTNUM(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr , 0 , 4 , __val)
#define SET_EARLYMODE_LEN0(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr , 4 , 15 , __val)
#define SET_EARLYMODE_LEN1(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr , 16 , 2 , __val)
#define SET_EARLYMODE_LEN1_1(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr , 19 , 13 , __val)
#define SET_EARLYMODE_LEN1_2(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr+4 , 0 , 2 , __val)
#define SET_EARLYMODE_LEN2(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr+4 , 2 , 15 ,  __val)
#define SET_EARLYMODE_LEN2_1(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr , 2 , 4 ,  __val)
#define SET_EARLYMODE_LEN2_2(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr+4 , 0 , 8 ,  __val)
#define SET_EARLYMODE_LEN3(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr+4 , 17 , 15, __val)
#define SET_EARLYMODE_LEN4(__paddr , __val)		\
	SET_BITS_TO_LE_4BYTE(__paddr+4 , 20 , 12 , __val)


/* TX/RX buffer descriptor */

/* for Txfilldescroptor8822be, fill the desc content. */
#if (DMA_IS_64BIT == 1)
#define SET_TXBUFFER_DESC_LEN_WITH_OFFSET(__pdesc, __offset, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*16), 0, 16, __val)
#define SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(__pdesc, __offset, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*16), 31, 1, __val)
#define SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(__pdesc, __offset, __val) \
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*16)+4, 0, 32, __val)
#define SET_TXBUFFER_DESC_ADD_HIGH_WITH_OFFSET(__pdesc, __offset, __val)\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*16)+8, 0, 32, __val)
#define GET_TXBUFFER_DESC_ADDR_LOW(__pdesc, __offset)			\
	LE_BITS_TO_4BYTE(__pdesc+(__offset*16)+4, 0, 32)
#define GET_TXBUFFER_DESC_ADDR_HIGH(__pdesc, __offset)			\
	LE_BITS_TO_4BYTE(__pdesc+(__offset*16)+8, 0, 32)
#else
#define SET_TXBUFFER_DESC_LEN_WITH_OFFSET(__pdesc, __offset, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*8), 0, 16, __val)
#define SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(__pdesc, __offset, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*8), 31, 1, __val)
#define SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(__pdesc, __offset, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+(__offset*8)+4, 0, 32, __val)
#define SET_TXBUFFER_DESC_ADD_HIGH_WITH_OFFSET(__pdesc, __offset, __val)
#define GET_TXBUFFER_DESC_ADDR_LOW(__pdesc, __offset)			\
	LE_BITS_TO_4BYTE(__pdesc+(__offset*8)+4, 0, 32)
#endif

/* Dword 0 */
#define SET_TX_BUFF_DESC_LEN_0(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc, 0, 14, __val)
#define SET_TX_BUFF_DESC_PSB(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc, 16, 15, __val)
#define SET_TX_BUFF_DESC_OWN(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc, 31, 1, __val)

/* Dword 1 */
#define SET_TX_BUFF_DESC_ADDR_LOW_0(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+4, 0, 32, __val)
#if (DMA_IS_64BIT == 1)
/* Dword 2 */
#define SET_TX_BUFF_DESC_ADDR_HIGH_0(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+8, 0, 32, __val)
/* Dword 3 / RESERVED 0 */
/* Dword 4 */
#define SET_TX_BUFF_DESC_LEN_1(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+16, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_1(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+16, 31, 1, __val)
/* Dword 5 */
#define SET_TX_BUFF_DESC_ADDR_LOW_1(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+20, 0, 32, __val)
/* Dword 6 */
#define SET_TX_BUFF_DESC_ADDR_HIGH_1(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+24, 0, 32, __val)
/* Dword 7 / RESERVED 0 */
/* Dword 8 */
#define SET_TX_BUFF_DESC_LEN_2(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+32, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_2(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+32, 31, 1, __val)
/* Dword 9 */
#define SET_TX_BUFF_DESC_ADDR_LOW_2(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+36, 0, 32, __val)
/* Dword 10 */
#define SET_TX_BUFF_DESC_ADDR_HIGH_2(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+40, 0, 32, __val)
/* Dword 11 / RESERVED 0 */
/* Dword 12 */
#define SET_TX_BUFF_DESC_LEN_3(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+48, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_3(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+48, 31, 1, __val)
/* Dword 13 */
#define SET_TX_BUFF_DESC_ADDR_LOW_3(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+52, 0, 32, __val)
/* Dword 14 */
#define SET_TX_BUFF_DESC_ADDR_HIGH_3(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+56, 0, 32, __val)
/* Dword 15 / RESERVED 0 */
#else
#define SET_TX_BUFF_DESC_ADDR_HIGH_0(__pdesc, __val)
/* Dword 2 */
#define SET_TX_BUFF_DESC_LEN_1(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+8, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_1(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+8, 31, 1, __val)
/* Dword 3 */
#define SET_TX_BUFF_DESC_ADDR_LOW_1(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+12, 0, 32, __val)
#define SET_TX_BUFF_DESC_ADDR_HIGH_1(__pdesc, __val)
/* Dword 4 */
#define SET_TX_BUFF_DESC_LEN_2(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+16, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_2(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+16, 31, 1, __val)
/* Dword 5 */
#define SET_TX_BUFF_DESC_ADDR_LOW_2(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+20, 0, 32, __val)
#define SET_TX_BUFF_DESC_ADDR_HIGH_2(__pdesc, __val)
/* Dword 6 */
#define SET_TX_BUFF_DESC_LEN_3(__pdesc, __val)		\
	SET_BITS_TO_LE_4BYTE(__pdesc+24, 0, 16, __val)
#define SET_TX_BUFF_DESC_AMSDU_3(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+24, 31, 1, __val)
/* Dword 7 */
#define SET_TX_BUFF_DESC_ADDR_LOW_3(__pdesc, __val)	\
	SET_BITS_TO_LE_4BYTE(__pdesc+28, 0, 32, __val)
#define SET_TX_BUFF_DESC_ADDR_HIGH_3(__pdesc, __val)
#endif

/* RX buffer  */

/* DWORD 0 */
#define SET_RX_BUFFER_DESC_DATA_LENGTH(__pRxStatusDesc , __val)	\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc , 0, 14, __val)
#define SET_RX_BUFFER_DESC_LS(__pRxStatusDesc , __val)		\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc , 15, 1, __val)
#define SET_RX_BUFFER_DESC_FS(__pRxStatusDesc , __val)		\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc , 16, 1, __val)
#define SET_RX_BUFFER_DESC_TOTAL_LENGTH(__pRxStatusDesc , __val)	\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc , 16, 15, __val)

#define GET_RX_BUFFER_DESC_OWN(__pRxStatusDesc)			\
	LE_BITS_TO_4BYTE(__pRxStatusDesc , 31, 1)
#define GET_RX_BUFFER_DESC_LS(__pRxStatusDesc)			\
	LE_BITS_TO_4BYTE(__pRxStatusDesc , 15, 1)
#define GET_RX_BUFFER_DESC_FS(__pRxStatusDesc)			\
	LE_BITS_TO_4BYTE(__pRxStatusDesc , 16, 1)
#define GET_RX_BUFFER_DESC_TOTAL_LENGTH(__pRxStatusDesc)	\
	LE_BITS_TO_4BYTE(__pRxStatusDesc , 16, 15)


/* DWORD 1 */
#define SET_RX_BUFFER_PHYSICAL_LOW(__pRxStatusDesc , __val)	\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc+4, 0, 32, __val)

/* DWORD 2 */
#define SET_RX_BUFFER_PHYSICAL_HIGH(__pRxStatusDesc , __val)	\
	SET_BITS_TO_LE_4BYTE(__pRxStatusDesc+8, 0, 32, __val)


#if 0
/* RX desc */
/* Dword 0 */
#define GET_RX_DESC_EOR(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 30, 1)
#define GET_RX_DESC_PHYPKTIDC(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 28, 1)
#define GET_RX_DESC_SWDEC(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 27, 1)
#define GET_RX_DESC_PHYST(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 26, 1)
#define GET_RX_DESC_SHIFT(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 24, 2)
#define GET_RX_DESC_QOS(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 23, 1)
#define GET_RX_DESC_SECURITY(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 20, 3)
#define GET_RX_DESC_DRV_INFO_SIZE(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 16, 4)
#define GET_RX_DESC_ICV_ERR(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 15, 1)
#define GET_RX_DESC_CRC32(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 14, 1)
#define GET_RX_DESC_PKT_LEN(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x00, 0, 14)

/* Dword 1 */
#define GET_RX_DESC_BC(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 31, 1)
#define GET_RX_DESC_MC(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 30, 1)
#define GET_RX_DESC_TY_PE(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 28, 2)
#define GET_RX_DESC_MF(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 27, 1)
#define GET_RX_DESC_MD(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 26, 1)
#define GET_RX_DESC_PWR(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 25, 1)
#define GET_RX_DESC_PAM(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 24, 1)
#define GET_RX_DESC_CHK_VLD(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 23, 1)
#define GET_RX_DESC_RX_IS_TCP_UDP(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 22, 1)
#define GET_RX_DESC_RX_IPV(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 21, 1)
#define GET_RX_DESC_CHKERR(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 20, 1)
#define GET_RX_DESC_PAGGR(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 15, 1)
#define GET_RX_DESC_RXID_MATCH(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 14, 1)
#define GET_RX_DESC_AMSDU(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 13, 1)
#define GET_RX_DESC_MACID_VLD(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 12, 1)
#define GET_RX_DESC_TID(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 8, 4)
#define GET_RX_DESC_MACID(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x04, 0, 7)

/* Dword 2 */
#define GET_RX_DESC_FCS_OK(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 31, 1)
#define GET_RX_DESC_C2H(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 28, 1)
#define GET_RX_DESC_HWRSVD(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 24, 4)
#define GET_RX_DESC_WLANHD_IV_LEN(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 18, 6)
#define GET_RX_DESC_RX_IS_QOS(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 16, 1)
#define GET_RX_DESC_FRAG(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 12, 4)
#define GET_RX_DESC_SEQ(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x08, 0, 12)


/* Dword 3 */
#define GET_RX_DESC_MAGIC_WAKE(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 31, 1)
#define GET_RX_DESC_UNICAST_WAKE(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 30, 1)
#define GET_RX_DESC_PATTERN_MATCH(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 29, 1)
#define GET_RX_DESC_DMA_AGG_NUM(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 16, 8)
#define GET_RX_DESC_BSSID_FIT_1_0(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 12, 2)
#define GET_RX_DESC_EOSP(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 11, 1)
#define GET_RX_DESC_HTC(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 10, 1)
#define GET_RX_DESC_BSSID_FIT_4_2(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 7, 3)
#define GET_RX_DESC_RX_RATE(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x0C, 0, 7)

/* Dword 4 */

#define GET_RX_DESC_A1_FIT(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 24, 5)
#define GET_RX_DESC_MACID_RPT_BUFF(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 17, 7)
#define GET_RX_DESC_RX_PRE_NDP_VLD(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 16, 1)
#define GET_RX_DESC_RX_SCRAMBLER(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 9, 7)
#define GET_RX_DESC_RX_EOF(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 8, 1)
#define GET_RX_DESC_PATTERN_IDX(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x10, 0, 8)

/* Dword 5 */
#define GET_RX_DESC_TSFL(__pRxDesc)    LE_BITS_TO_4BYTE(__pRxDesc + 0x14, 0, 32)

#endif

#define CLEAR_PCI_TX_DESC_CONTENT(__pdesc, _size)		\
do {								\
	if (_size > TX_DESC_NEXT_DESC_OFFSET)			\
		memset(__pdesc, 0, TX_DESC_NEXT_DESC_OFFSET);	\
	else							\
		memset(__pdesc, 0, _size);			\
} while (0)

#if 0

struct tx_desc {
	u32 pktsize:16;
	u32 offset:8;
	u32 bmc:1;
	u32 htc:1;
	u32 lastseg:1;
	u32 firstseg:1;
	u32 linip:1;
	u32 noacm:1;
	u32 gf:1;
	u32 own:1;

	u32 macid:6;
	u32 rsvd0:2;
	u32 queuesel:5;
	u32 rd_nav_ext:1;
	u32 lsig_txop_en:1;
	u32 pifs:1;
	u32 rateid:4;
	u32 nav_usehdr:1;
	u32 en_descid:1;
	u32 sectype:2;
	u32 pktoffset:8;

	u32 rts_rc:6;
	u32 data_rc:6;
	u32 agg_en:1;
	u32 rdg_en:1;
	u32 bar_retryht:2;
	u32 agg_break:1;
	u32 morefrag:1;
	u32 raw:1;
	u32 ccx:1;
	u32 ampdudensity:3;
	u32 bt_int:1;
	u32 ant_sela:1;
	u32 ant_selb:1;
	u32 txant_cck:2;
	u32 txant_l:2;
	u32 txant_ht:2;

	u32 nextheadpage:8;
	u32 tailpage:8;
	u32 seq:12;
	u32 cpu_handle:1;
	u32 tag1:1;
	u32 trigger_int:1;
	u32 hwseq_en:1;

	u32 rtsrate:5;
	u32 apdcfe:1;
	u32 qos:1;
	u32 hwseq_ssn:1;
	u32 userrate:1;
	u32 dis_rtsfb:1;
	u32 dis_datafb:1;
	u32 cts2self:1;
	u32 rts_en:1;
	u32 hwrts_en:1;
	u32 portid:1;
	u32 pwr_status:3;
	u32 waitdcts:1;
	u32 cts2ap_en:1;
	u32 txsc:2;
	u32 stbc:2;
	u32 txshort:1;
	u32 txbw:1;
	u32 rtsshort:1;
	u32 rtsbw:1;
	u32 rtssc:2;
	u32 rtsstbc:2;

	u32 txrate:6;
	u32 shortgi:1;
	u32 ccxt:1;
	u32 txrate_fb_lmt:5;
	u32 rtsrate_fb_lmt:4;
	u32 retrylmt_en:1;
	u32 txretrylmt:6;
	u32 usb_txaggnum:8;

	u32 txagca:5;
	u32 txagcb:5;
	u32 usemaxlen:1;
	u32 maxaggnum:5;
	u32 mcsg1maxlen:4;
	u32 mcsg2maxlen:4;
	u32 mcsg3maxlen:4;
	u32 mcs7sgimaxlen:4;

	u32 txbuffersize:16;
	u32 sw_offset30:8;
	u32 sw_offset31:4;
	u32 rsvd1:1;
	u32 antsel_c:1;
	u32 null_0:1;
	u32 null_1:1;

	u32 txbuffaddr;
	u32 txbufferaddr64;
	u32 nextdescaddress;
	u32 nextdescaddress64;

	u32 reserve_pass_pcie_mm_limit[4];
} __packed;

struct rx_desc {
	u32 length:14;
	u32 crc32:1;
	u32 icverror:1;
	u32 drv_infosize:4;
	u32 security:3;
	u32 qos:1;
	u32 shift:2;
	u32 phystatus:1;
	u32 swdec:1;
	u32 lastseg:1;
	u32 firstseg:1;
	u32 eor:1;
	u32 own:1;

	u32 macid:6;
	u32 tid:4;
	u32 hwrsvd:5;
	u32 paggr:1;
	u32 faggr:1;
	u32 a1_fit:4;
	u32 a2_fit:4;
	u32 pam:1;
	u32 pwr:1;
	u32 moredata:1;
	u32 morefrag:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 frag:4;
	u32 nextpktlen:14;
	u32 nextind:1;
	u32 rsvd:1;

	u32 rxmcs:6;
	u32 rxht:1;
	u32 amsdu:1;
	u32 splcp:1;
	u32 bandwidth:1;
	u32 htc:1;
	u32 tcpchk_rpt:1;
	u32 ipcchk_rpt:1;
	u32 tcpchk_valid:1;
	u32 hwpcerr:1;
	u32 hwpcind:1;
	u32 iv0:16;

	u32 iv1;

	u32 tsfl;

	u32 bufferaddress;
	u32 bufferaddress64;

} __packed;

#endif

void rtl8822be_rx_check_dma_ok(struct ieee80211_hw *hw, u8 *header_desc,
			     u8 queue_index);
u16	rtl8822be_rx_desc_buff_remained_cnt(struct ieee80211_hw *hw,
					  u8 queue_index);
u16 rtl8822be_get_available_desc(struct ieee80211_hw *hw , u8 queue_index);
void rtl8822be_pre_fill_tx_bd_desc(struct ieee80211_hw *hw,
				 u8 *tx_bd_desc, u8 *desc, u8 queue_index,
				 struct sk_buff *skb, dma_addr_t addr);


void rtl8822be_tx_fill_desc(struct ieee80211_hw *hw,
			  struct ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *pbd_desc_tx,
			  struct ieee80211_tx_info *info,
			  struct ieee80211_sta *sta,
			  struct sk_buff *skb,
			  u8 hw_queue, struct rtl_tcb_desc *ptcb_desc);
void rtl8822be_tx_fill_special_desc(struct ieee80211_hw *hw,
				u8 *pdesc, u8 *pbd_desc,
				struct sk_buff *skb, u8 hw_queue);
bool rtl8822be_rx_query_desc(struct ieee80211_hw *hw,
			   struct rtl_stats *status,
			   struct ieee80211_rx_status *rx_status,
			   u8 *pdesc, struct sk_buff *skb);
void rtl8822be_set_desc(struct ieee80211_hw *hw, u8 *pdesc, bool istx,
		      u8 desc_name, u8 *val);

u32 rtl8822be_get_desc(u8 *pdesc, bool istx, u8 desc_name);
bool rtl8822be_is_tx_desc_closed(struct ieee80211_hw *hw, u8 hw_queue,
				 u16 index);
void rtl8822be_tx_polling(struct ieee80211_hw *hw, u8 hw_queue);
void rtl8822be_tx_fill_cmddesc(struct ieee80211_hw *hw, u8 *pdesc,
			     bool firstseg, bool lastseg,
			     struct sk_buff *skb);
u32 rtl8822be_rx_command_packet(struct ieee80211_hw *hw,
			      const struct rtl_stats *status,
			      struct sk_buff *skb);
#endif
