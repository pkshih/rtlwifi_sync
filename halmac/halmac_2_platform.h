/******************************************************************************
 *
 * Copyright(c) 2016  Realtek Corporation.
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
#ifndef _HALMAC_2_PLATFORM_H_
#define _HALMAC_2_PLATFORM_H_

/*[Driver] always set BUILD_TEST =0*/
#define BUILD_TEST	0

#if BUILD_TEST
#include "../Platform/App/Test/halmac_2_platformapi.h"
#else
/*[Driver] use their own header files*/
#include "../wifi.h"
#include <asm/byteorder.h>
#include "halmac_hw_cfg.h"
#endif

/*[Driver] config if the operating platform*/
#define HALMAC_PLATFORM_WINDOWS		0
#define HALMAC_PLATFORM_LINUX		1
#define HALMAC_PLATFORM_AP		0
/*[Driver] must set HALMAC_PLATFORM_TESTPROGRAM = 0*/
#define HALMAC_PLATFORM_TESTPROGRAM	0

/*[Driver] config if enable the dbg msg or notl*/
#define HALMAC_DBG_MSG_ENABLE		1

/* define the Platform SDIO Bus CLK */
#define PLATFORM_SD_CLK 50000000 /*50MHz*/

/* define the Rx FIFO expanding mode packet size unit for 8821C and 8822B */
/* Should be 8 Byte alignment */
#define HALMAC_RX_FIFO_EXPANDING_MODE_PKT_SIZE 16 /*Bytes*/

/*[Driver] provide the type mutex*/
/* Mutex type */
typedef	spinlock_t	HALMAC_MUTEX;

#define CONFIG_PCIE_HCI	1

#endif /* _HALMAC_2_PLATFORM_H_ */
