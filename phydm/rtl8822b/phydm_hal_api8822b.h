/******************************************************************************
 *
 * Copyright(c) 2007 - 2016  Realtek Corporation.
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
#ifndef __INC_PHYDM_API_H_8822B__
#define __INC_PHYDM_API_H_8822B__

/*2016.08.01 (HW user guide version: R27, SW user guide version: R05,
 *            Modification: R31)
 */
#define PHY_CONFIG_VERSION_8822B "27.5.31"

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define config_phydm_read_rf_check_8822b(data) (data != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8822b(data) (data != INVALID_TXAGC_DATA)

u32 config_phydm_read_rf_reg_8822b(struct phy_dm_struct *dm,
				   enum odm_rf_radio_path_e rf_path,
				   u32 reg_addr, u32 bit_mask);

bool config_phydm_write_rf_reg_8822b(struct phy_dm_struct *dm,
				     enum odm_rf_radio_path_e rf_path,
				     u32 reg_addr, u32 bit_mask, u32 data);

bool config_phydm_write_txagc_8822b(struct phy_dm_struct *dm, u32 power_index,
				    enum odm_rf_radio_path_e path, u8 hw_rate);

u8 config_phydm_read_txagc_8822b(struct phy_dm_struct *dm,
				 enum odm_rf_radio_path_e path, u8 hw_rate);

bool config_phydm_switch_band_8822b(struct phy_dm_struct *dm, u8 central_ch);

bool config_phydm_switch_channel_8822b(struct phy_dm_struct *dm, u8 central_ch);

bool config_phydm_switch_bandwidth_8822b(struct phy_dm_struct *dm,
					 u8 primary_ch_idx,
					 enum odm_bw_e bandwidth);

bool config_phydm_switch_channel_bw_8822b(struct phy_dm_struct *dm,
					  u8 central_ch, u8 primary_ch_idx,
					  enum odm_bw_e bandwidth);

bool config_phydm_trx_mode_8822b(struct phy_dm_struct *dm,
				 enum odm_rf_path_e tx_path,
				 enum odm_rf_path_e rx_path, bool is_tx2_path);

bool config_phydm_parameter_init(struct phy_dm_struct *dm,
				 enum odm_parameter_init_e type);

/* ======================================================================== */
/* These following functions can be used for PHY DM only*/

bool phydm_write_txagc_1byte_8822b(struct phy_dm_struct *dm, u32 power_index,
				   enum odm_rf_radio_path_e path, u8 hw_rate);

void phydm_init_hw_info_by_rfe_type_8822b(struct phy_dm_struct *dm);

s32 phydm_get_condition_number_8822B(struct phy_dm_struct *dm);

/* ======================================================================== */

#endif /*  __INC_PHYDM_API_H_8822B__ */
