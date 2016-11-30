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
/* ************************************************************
 * Description:
 *
 * This file is for RTL8822B Co-exist mechanism
 *
 * History
 * 2012/11/15 Cosa first check in.
 *
 * *************************************************************/

/* ************************************************************
 * include files
 * *************************************************************/
#include "halbt_precomp.h"

/* ************************************************************
 * Global variables, these are static variables
 * *************************************************************/
static struct coex_dm_8822b_2ant glcoex_dm_8822b_2ant;
static struct coex_dm_8822b_2ant *coex_dm = &glcoex_dm_8822b_2ant;
static struct coex_sta_8822b_2ant glcoex_sta_8822b_2ant;
static struct coex_sta_8822b_2ant *coex_sta = &glcoex_sta_8822b_2ant;
static struct psdscan_sta_8822b_2ant gl_psd_scan_8822b_2ant;
static struct psdscan_sta_8822b_2ant *psd_scan = &gl_psd_scan_8822b_2ant;
static struct rfe_type_8822b_2ant gl_rfe_type_8822b_2ant;
static struct rfe_type_8822b_2ant *rfe_type = &gl_rfe_type_8822b_2ant;

static const char *const glbt_info_src_8822b_2ant[] = {
	"BT Info[wifi fw]", "BT Info[bt rsp]", "BT Info[bt auto report]",
};

static u32 glcoex_ver_date_8822b_2ant = 20161116;
static u32 glcoex_ver_8822b_2ant = 0x3d;
static u32 glcoex_ver_btdesired_8822b_2ant = 0x28;

/* ************************************************************
 * local function proto type if needed
 * ************************************************************
 * ************************************************************
 * local function start with halbtc8822b2ant_
 * *************************************************************/
static u8 halbtc8822b2ant_bt_rssi_state(struct btc_coexist *btcoexist,
					u8 *ppre_bt_rssi_state, u8 level_num,
					u8 rssi_thresh, u8 rssi_thresh1)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	s32 bt_rssi = 0;
	u8 bt_rssi_state = *ppre_bt_rssi_state;

	bt_rssi = coex_sta->bt_rssi;

	if (level_num == 2) {
		if ((*ppre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*ppre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (bt_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
			else
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else {
			if (bt_rssi < rssi_thresh)
				bt_rssi_state = BTC_RSSI_STATE_LOW;
			else
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	} else if (level_num == 3) {
		if (rssi_thresh > rssi_thresh1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT Rssi thresh error!!\n");
			return *ppre_bt_rssi_state;
		}

		if ((*ppre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*ppre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (bt_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else if ((*ppre_bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
			   (*ppre_bt_rssi_state ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) {
			if (bt_rssi >= (rssi_thresh1 +
					BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
			else if (bt_rssi < rssi_thresh)
				bt_rssi_state = BTC_RSSI_STATE_LOW;
			else
				bt_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
		} else {
			if (bt_rssi < rssi_thresh1)
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	}

	*ppre_bt_rssi_state = bt_rssi_state;

	return bt_rssi_state;
}

static u8 halbtc8822b2ant_wifi_rssi_state(struct btc_coexist *btcoexist,
					  u8 *pprewifi_rssi_state, u8 level_num,
					  u8 rssi_thresh, u8 rssi_thresh1)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	s32 wifi_rssi = 0;
	u8 wifi_rssi_state = *pprewifi_rssi_state;

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);

	if (level_num == 2) {
		if ((*pprewifi_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*pprewifi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else {
			if (wifi_rssi < rssi_thresh)
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	} else if (level_num == 3) {
		if (rssi_thresh > rssi_thresh1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], wifi RSSI thresh error!!\n");
			return *pprewifi_rssi_state;
		}

		if ((*pprewifi_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*pprewifi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else if ((*pprewifi_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
			   (*pprewifi_rssi_state ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) {
			if (wifi_rssi >= (rssi_thresh1 +
					  BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
			else if (wifi_rssi < rssi_thresh)
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
		} else {
			if (wifi_rssi < rssi_thresh1)
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	}

	*pprewifi_rssi_state = wifi_rssi_state;

	return wifi_rssi_state;
}

static void halbtc8822b2ant_coex_switch_threshold(struct btc_coexist *btcoexist,
						  u8 isolation_measuared)
{
	s8 interference_wl_tx = 0, interference_bt_tx = 0;

	interference_wl_tx =
		BT_8822B_2ANT_WIFI_MAX_TX_POWER - isolation_measuared;
	interference_bt_tx =
		BT_8822B_2ANT_BT_MAX_TX_POWER - isolation_measuared;

	coex_sta->wifi_coex_thres = BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES1;
	coex_sta->wifi_coex_thres2 = BT_8822B_2ANT_WIFI_RSSI_COEXSWITCH_THRES2;

	coex_sta->bt_coex_thres = BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES1;
	coex_sta->bt_coex_thres2 = BT_8822B_2ANT_BT_RSSI_COEXSWITCH_THRES2;
}

static void halbtc8822b2ant_query_bt_info(struct btc_coexist *btcoexist)
{
	u8 h2c_parameter[1] = {0};
	bool RTL97F_8822B = false;

	if (RTL97F_8822B)
		return;

	coex_sta->c2h_bt_info_req_sent = true;

	h2c_parameter[0] |= BIT(0); /* trigger */

	btcoexist->btc_fill_h2c(btcoexist, 0x61, 1, h2c_parameter);
}

static void halbtc8822b2ant_monitor_bt_ctr(struct btc_coexist *btcoexist)
{
	u32 reg_hp_txrx, reg_lp_txrx, u32tmp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;
	static u8 num_of_bt_counter_chk, cnt_slave;

	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;

	u32tmp = btcoexist->btc_read_4byte(btcoexist, reg_hp_txrx);
	reg_hp_tx = u32tmp & MASKLWORD;
	reg_hp_rx = (u32tmp & MASKHWORD) >> 16;

	u32tmp = btcoexist->btc_read_4byte(btcoexist, reg_lp_txrx);
	reg_lp_tx = u32tmp & MASKLWORD;
	reg_lp_rx = (u32tmp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	/* reset counter */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0xc);

	if ((coex_sta->low_priority_tx > 1050) &&
	    (!coex_sta->c2h_bt_inquiry_page))
		coex_sta->pop_event_cnt++;

	if ((coex_sta->low_priority_rx >= 950) &&
	    (coex_sta->low_priority_rx >= coex_sta->low_priority_tx) &&
	    (!coex_sta->under_ips) && (!coex_sta->c2h_bt_inquiry_page) &&
	    (coex_sta->bt_link_exist)) {
		if (cnt_slave >= 2) {
			bt_link_info->slave_role = true;
			cnt_slave = 2;
		} else {
			cnt_slave++;
		}
	} else {
		if (cnt_slave == 0) {
			bt_link_info->slave_role = false;
			cnt_slave = 0;
		} else {
			cnt_slave--;
		}
	}

	if ((coex_sta->high_priority_tx == 0) &&
	    (coex_sta->high_priority_rx == 0) &&
	    (coex_sta->low_priority_tx == 0) &&
	    (coex_sta->low_priority_rx == 0)) {
		num_of_bt_counter_chk++;
		if (num_of_bt_counter_chk >= 3) {
			halbtc8822b2ant_query_bt_info(btcoexist);
			num_of_bt_counter_chk = 0;
		}
	}
}

static void halbtc8822b2ant_monitor_wifi_ctr(struct btc_coexist *btcoexist) {}

static bool
halbtc8822b2ant_is_wifibt_status_changed(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static bool pre_wifi_busy, pre_under_4way, pre_bt_hs_on, pre_bt_off;
	static u8 pre_hid_busy_num;
	bool wifi_busy = false, under_4way = false, bt_hs_on = false;
	bool wifi_connected = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (coex_sta->bt_disabled != pre_bt_off) {
		pre_bt_off = coex_sta->bt_disabled;

		if (coex_sta->bt_disabled)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT is disabled !!\n");
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT is enabled !!\n");

		coex_sta->bt_coex_supported_feature = 0;
		coex_sta->bt_coex_supported_version = 0;
		coex_sta->bt_ble_scan_type = 0;
		coex_sta->bt_ble_scan_para[0] = 0;
		coex_sta->bt_ble_scan_para[1] = 0;
		coex_sta->bt_ble_scan_para[2] = 0;
		coex_sta->bt_reg_vendor_ac = 0xffff;
		coex_sta->bt_reg_vendor_ae = 0xffff;
		return true;
	}

	if (wifi_connected) {
		if (wifi_busy != pre_wifi_busy) {
			pre_wifi_busy = wifi_busy;
			return true;
		}
		if (under_4way != pre_under_4way) {
			pre_under_4way = under_4way;
			return true;
		}
		if (bt_hs_on != pre_bt_hs_on) {
			pre_bt_hs_on = bt_hs_on;
			return true;
		}

		if (!coex_sta->bt_disabled) {
			if (coex_sta->hid_busy_num != pre_hid_busy_num) {
				pre_hid_busy_num = coex_sta->hid_busy_num;
				return true;
			}
		}
	}

	return false;
}

static void halbtc8822b2ant_update_bt_link_info(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	bool bt_busy = false;

	coex_sta->num_of_profile = 0;

	/* set link exist status */
	if (!(coex_sta->bt_info & BT_INFO_8822B_1ANT_B_CONNECTION)) {
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	} else { /* connection exists */
		coex_sta->bt_link_exist = true;
		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_FTP) {
			coex_sta->pan_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->pan_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_A2DP) {
			coex_sta->a2dp_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->a2dp_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_HID) {
			coex_sta->hid_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->hid_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_ESCO) {
			coex_sta->sco_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->sco_exist = false;
		}
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	bt_link_info->bt_link_exist = coex_sta->bt_link_exist;
	bt_link_info->sco_exist = coex_sta->sco_exist;
	bt_link_info->a2dp_exist = coex_sta->a2dp_exist;
	bt_link_info->pan_exist = coex_sta->pan_exist;
	bt_link_info->hid_exist = coex_sta->hid_exist;
	bt_link_info->acl_busy = coex_sta->acl_busy;

	/* work around for HS mode. */
	if (bt_hs_on) {
		bt_link_info->pan_exist = true;
		bt_link_info->bt_link_exist = true;
	}

	/* check if Sco only */
	if (bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->sco_only = true;
	else
		bt_link_info->sco_only = false;

	/* check if A2dp only */
	if (!bt_link_info->sco_exist && bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->a2dp_only = true;
	else
		bt_link_info->a2dp_only = false;

	/* check if Pan only */
	if (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->pan_only = true;
	else
		bt_link_info->pan_only = false;

	/* check if Hid only */
	if (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && bt_link_info->hid_exist)
		bt_link_info->hid_only = true;
	else
		bt_link_info->hid_only = false;

	if (!(coex_sta->bt_info & BT_INFO_8822B_2ANT_B_CONNECTION)) {
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE;
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	} else if (coex_sta->bt_info == BT_INFO_8822B_2ANT_B_CONNECTION) {
		/* connection exists but no busy */
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_CONNECTED_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	} else if (((coex_sta->bt_info & BT_INFO_8822B_2ANT_B_SCO_ESCO) ||
		    (coex_sta->bt_info & BT_INFO_8822B_2ANT_B_SCO_BUSY)) &&
		   (coex_sta->bt_info & BT_INFO_8822B_2ANT_B_ACL_BUSY)) {
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_ACL_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT ACL SCO busy!!!\n");
	} else if ((coex_sta->bt_info & BT_INFO_8822B_2ANT_B_SCO_ESCO) ||
		   (coex_sta->bt_info & BT_INFO_8822B_2ANT_B_SCO_BUSY)) {
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	} else if (coex_sta->bt_info & BT_INFO_8822B_2ANT_B_ACL_BUSY) {
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_ACL_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	} else {
		coex_dm->bt_status = BT_8822B_2ANT_BT_STATUS_MAX;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	}

	if ((coex_dm->bt_status == BT_8822B_2ANT_BT_STATUS_ACL_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_2ANT_BT_STATUS_SCO_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_2ANT_BT_STATUS_ACL_SCO_BUSY))
		bt_busy = true;
	else
		bt_busy = false;

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);
}

static void
halbtc8822b2ant_update_wifi_channel_info(struct btc_coexist *btcoexist, u8 type)
{
	u8 h2c_parameter[3] = {0};
	u32 wifi_bw;
	u8 wifi_central_chnl;
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	/* only 2.4G we need to inform bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wifi_central_chnl);
	if ((type == BTC_MEDIA_CONNECT) && (wifi_central_chnl <= 14)) {
		/* enable BT AFH skip WL channel for 8822b
		 * because BT Rx LO interference
		 */
		h2c_parameter[0] = 0x1;
		h2c_parameter[1] = wifi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
		if (wifi_bw == BTC_WIFI_BW_HT40)
			h2c_parameter[2] = 0x30;
		else
			h2c_parameter[2] = 0x20;
	}

	coex_dm->wifi_chnl_info[0] = h2c_parameter[0];
	coex_dm->wifi_chnl_info[1] = h2c_parameter[1];
	coex_dm->wifi_chnl_info[2] = h2c_parameter[2];

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
}

static void
halbtc8822b2ant_set_fw_dac_swing_level(struct btc_coexist *btcoexist,
				       u8 dac_swing_lvl)
{
	u8 h2c_parameter[1] = {0};
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	/* There are several type of dacswing */
	/* 0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6 */
	h2c_parameter[0] = dac_swing_lvl;

	btcoexist->btc_fill_h2c(btcoexist, 0x64, 1, h2c_parameter);
}

static void halbtc8822b2ant_fw_dac_swing_lvl(struct btc_coexist *btcoexist,
					     bool force_exec,
					     u8 fw_dac_swing_lvl)
{
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	if (!force_exec) {
		if (coex_dm->pre_fw_dac_swing_lvl ==
		    coex_dm->cur_fw_dac_swing_lvl)
			return;
	}

	halbtc8822b2ant_set_fw_dac_swing_level(btcoexist,
					       coex_dm->cur_fw_dac_swing_lvl);

	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
}

static void halbtc8822b2ant_set_fw_dec_bt_pwr(struct btc_coexist *btcoexist,
					      u8 dec_bt_pwr_lvl)
{
	u32 RTL97F_8822B = 0;
	u8 h2c_parameter[1] = {0};

	if (RTL97F_8822B)
		return;

	h2c_parameter[0] = dec_bt_pwr_lvl;

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
}

static void halbtc8822b2ant_dec_bt_pwr(struct btc_coexist *btcoexist,
				       bool force_exec, u8 dec_bt_pwr_lvl)
{
	coex_dm->cur_bt_dec_pwr_lvl = dec_bt_pwr_lvl;

	if (!force_exec) {
		if (coex_dm->pre_bt_dec_pwr_lvl == coex_dm->cur_bt_dec_pwr_lvl)
			return;
	}
	halbtc8822b2ant_set_fw_dec_bt_pwr(btcoexist,
					  coex_dm->cur_bt_dec_pwr_lvl);

	coex_dm->pre_bt_dec_pwr_lvl = coex_dm->cur_bt_dec_pwr_lvl;
}

static void halbtc8822b2ant_low_penalty_ra(struct btc_coexist *btcoexist,
					   bool force_exec, bool low_penalty_ra)
{
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	if (!force_exec) {
		if (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			return;
	}

	if (low_penalty_ra)
		btcoexist->btc_phydm_modify_ra_pcr_threshold(btcoexist, 0, 50);
	else
		btcoexist->btc_phydm_modify_ra_pcr_threshold(btcoexist, 0, 0);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
}

static void halbtc8822b2ant_write_score_board(struct btc_coexist *btcoexist,
					      u16 bitpos, bool state)
{
	static u16 originalval = 0x8002;

	if (state)
		originalval = originalval | bitpos;
	else
		originalval = originalval & (~bitpos);

	btcoexist->btc_write_2byte(btcoexist, 0xaa, originalval);
}

static void halbtc8822b2ant_read_score_board(struct btc_coexist *btcoexist,
					     u16 *score_board_val)
{
	*score_board_val =
		(btcoexist->btc_read_2byte(btcoexist, 0xaa)) & 0x7fff;
}

static void halbtc8822b2ant_post_state_to_bt(struct btc_coexist *btcoexist,
					     u16 type, bool state)
{
	halbtc8822b2ant_write_score_board(btcoexist, (u16)type, state);
}

static void
halbtc8822b2ant_monitor_bt_enable_disable(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u32 bt_disable_cnt;
	bool bt_active = true, bt_disabled = false, wifi_under_5g = false;
	u16 u16tmp;

	/* This function check if bt is disabled */

	/* Read BT on/off status from scoreboard[1],
	 * enable this only if BT patch support this feature
	 */
	halbtc8822b2ant_read_score_board(btcoexist, &u16tmp);

	bt_active = u16tmp & BIT(1);

	if (bt_active) {
		bt_disable_cnt = 0;
		bt_disabled = false;
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
	} else {
		bt_disable_cnt++;
		if (bt_disable_cnt >= 10) {
			bt_disabled = true;
			bt_disable_cnt = 10;
		}

		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if ((wifi_under_5g) || (bt_disabled))
		halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, false);
	else
		halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, true);

	if (coex_sta->bt_disabled != bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is from %s to %s!!\n",
			 (coex_sta->bt_disabled ? "disabled" : "enabled"),
			 (bt_disabled ? "disabled" : "enabled"));
		coex_sta->bt_disabled = bt_disabled;
	}
}

static void halbtc8822b2ant_enable_gnt_to_gpio(struct btc_coexist *btcoexist,
					       bool isenable)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
#if BT_8822B_2ANT_COEX_DBG
	static u8 bit_val[5] = {0, 0, 0, 0, 0};

	if (isenable) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], enable_gnt_to_gpio!!\n");

		/* enable GNT_WL, GNT_BT to GPIO for debug */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x8, 0x1);

		/* store original value */
		bit_val[0] =
			(btcoexist->btc_read_1byte(btcoexist, 0x66) & BIT(4)) >>
			4; /*0x66[4] */
		bit_val[1] = (btcoexist->btc_read_1byte(btcoexist, 0x67) &
			      BIT(0)); /*0x66[8] */
		bit_val[2] =
			(btcoexist->btc_read_1byte(btcoexist, 0x42) & BIT(3)) >>
			3; /*0x40[19] */
		bit_val[3] =
			(btcoexist->btc_read_1byte(btcoexist, 0x65) & BIT(7)) >>
			7; /*0x64[15] */
		bit_val[4] =
			(btcoexist->btc_read_1byte(btcoexist, 0x72) & BIT(2)) >>
			2; /*0x70[18] */

		/*  switch GPIO Mux */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x66, BIT(4),
						   0x0); /*0x66[4] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, BIT(0),
						   0x0); /*0x66[8] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x42, BIT(3),
						   0x0); /*0x40[19] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x65, BIT(7),
						   0x0); /*0x64[15] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x72, BIT(2),
						   0x0); /*0x70[18] = 0 */

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], disable_gnt_to_gpio!!\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x8, 0x0);

		/*  Restore original value  */
		/*  switch GPIO Mux */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x66, BIT(4),
						   bit_val[0]); /*0x66[4] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, BIT(0),
						   bit_val[1]); /*0x66[8] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x42, BIT(3), bit_val[2]); /*0x40[19] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x65, BIT(7), bit_val[3]); /*0x64[15] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x72, BIT(2), bit_val[4]); /*0x70[18] = 0 */
	}

#endif
}

static u32
halbtc8822b2ant_ltecoex_indirect_read_reg(struct btc_coexist *btcoexist,
					  u16 reg_addr)
{
	u32 j = 0;

	/* wait for ready bit before access 0x1700		 */
	btcoexist->btc_write_4byte(btcoexist, 0x1700, 0x800F0000 | reg_addr);

	do {
		j++;
	} while (((btcoexist->btc_read_1byte(btcoexist, 0x1703) & BIT(5)) ==
		  0) &&
		 (j < BT_8822B_2ANT_LTECOEX_INDIRECTREG_ACCESS_TIMEOUT));

	return btcoexist->btc_read_4byte(btcoexist, 0x1708); /* get read data */
}

static void
halbtc8822b2ant_ltecoex_indirect_write_reg(struct btc_coexist *btcoexist,
					   u16 reg_addr, u32 bit_mask,
					   u32 reg_value)
{
	u32 val, i = 0, j = 0, bitpos = 0;

	if (bit_mask == 0x0)
		return;
	if (bit_mask == 0xffffffff) {
		btcoexist->btc_write_4byte(btcoexist, 0x1704,
					   reg_value); /* put write data */

		/* wait for ready bit before access 0x1700 */
		do {
			j++;
		} while (
			((btcoexist->btc_read_1byte(btcoexist, 0x1703) &
			  BIT(5)) == 0) &&
			(j < BT_8822B_2ANT_LTECOEX_INDIRECTREG_ACCESS_TIMEOUT));

		btcoexist->btc_write_4byte(btcoexist, 0x1700,
					   0xc00F0000 | reg_addr);
	} else {
		for (i = 0; i <= 31; i++) {
			if (((bit_mask >> i) & 0x1) == 0x1) {
				bitpos = i;
				break;
			}
		}

		/* read back register value before write */
		val = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								reg_addr);
		val = (val & (~bit_mask)) | (reg_value << bitpos);

		btcoexist->btc_write_4byte(btcoexist, 0x1704,
					   val); /* put write data */

		/* wait for ready bit before access 0x7c0		 */
		do {
			j++;
		} while (
			((btcoexist->btc_read_1byte(btcoexist, 0x1703) &
			  BIT(5)) == 0) &&
			(j < BT_8822B_2ANT_LTECOEX_INDIRECTREG_ACCESS_TIMEOUT));

		btcoexist->btc_write_4byte(btcoexist, 0x1700,
					   0xc00F0000 | reg_addr);
	}
}

static void halbtc8822b2ant_ltecoex_enable(struct btc_coexist *btcoexist,
					   bool enable)
{
	u8 val;

	val = (enable) ? 1 : 0;
	halbtc8822b2ant_ltecoex_indirect_write_reg(btcoexist, 0x38, 0x80,
						   val); /* 0x38[7] */
}

static void
halbtc8822b2ant_ltecoex_pathcontrol_owner(struct btc_coexist *btcoexist,
					  bool wifi_control)
{
	u8 val;

	val = (wifi_control) ? 1 : 0;
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x4,
					   val); /* 0x70[26] */
}

static void halbtc8822b2ant_ltecoex_set_gnt_bt(struct btc_coexist *btcoexist,
					       u8 control_block,
					       bool sw_control, u8 state)
{
	u32 val = 0, bit_mask;

	state = state & 0x1;
	val = (sw_control) ? ((state << 1) | 0x1) : 0;

	switch (control_block) {
	case BT_8822B_2ANT_GNT_BLOCK_RFC_BB:
	default:
		bit_mask = 0xc000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[15:14] */
		bit_mask = 0x0c00;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[11:10] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_RFC:
		bit_mask = 0xc000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[15:14] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_BB:
		bit_mask = 0x0c00;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[11:10] */
		break;
	}
}

static void halbtc8822b2ant_ltecoex_set_gnt_wl(struct btc_coexist *btcoexist,
					       u8 control_block,
					       bool sw_control, u8 state)
{
	u32 val = 0, bit_mask;

	state = state & 0x1;
	val = (sw_control) ? ((state << 1) | 0x1) : 0;

	switch (control_block) {
	case BT_8822B_2ANT_GNT_BLOCK_RFC_BB:
	default:
		bit_mask = 0x3000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[13:12] */
		bit_mask = 0x0300;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[9:8] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_RFC:
		bit_mask = 0x3000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[13:12] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_BB:
		bit_mask = 0x0300;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[9:8] */
		break;
	}
}

static void
halbtc8822b2ant_ltecoex_set_coex_table(struct btc_coexist *btcoexist,
				       u8 table_type, u16 table_content)
{
	u16 reg_addr = 0x0000;

	switch (table_type) {
	case BT_8822B_2ANT_CTT_WL_VS_LTE:
		reg_addr = 0xa0;
		break;
	case BT_8822B_2ANT_CTT_BT_VS_LTE:
		reg_addr = 0xa4;
		break;
	}

	if (reg_addr != 0x0000)
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, reg_addr, 0xffff,
			table_content); /* 0xa0[15:0] or 0xa4[15:0] */
}

static void halbtc8822b2ant_set_coex_table(struct btc_coexist *btcoexist,
					   u32 val0x6c0, u32 val0x6c4,
					   u32 val0x6c8, u8 val0x6cc)
{
	btcoexist->btc_write_4byte(btcoexist, 0x6c0, val0x6c0);

	btcoexist->btc_write_4byte(btcoexist, 0x6c4, val0x6c4);

	btcoexist->btc_write_4byte(btcoexist, 0x6c8, val0x6c8);

	btcoexist->btc_write_1byte(btcoexist, 0x6cc, val0x6cc);
}

static void halbtc8822b2ant_coex_table(struct btc_coexist *btcoexist,
				       bool force_exec, u32 val0x6c0,
				       u32 val0x6c4, u32 val0x6c8, u8 val0x6cc)
{
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	if (!force_exec) {
		if ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			return;
	}
	halbtc8822b2ant_set_coex_table(btcoexist, val0x6c0, val0x6c4, val0x6c8,
				       val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
}

static void halbtc8822b2ant_coex_table_with_type(struct btc_coexist *btcoexist,
						 bool force_exec, u8 type)
{
	u32 break_table;
	u8 select_table;

	coex_sta->coex_table_type = type;

	if (coex_sta->concurrent_rx_mode_on) {
		break_table = 0xf0ffffff; /* set WL hi-pri can break BT */
		/* 0xb/0x3,set Tx response = Hi-Pri/LO-Pri
		 * (ex: Transmitting ACK,BA,CTS)
		 */
		select_table = 0x3;
	} else {
		break_table = 0xffffff;
		select_table = 0x3;
	}

	switch (type) {
	case 0:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x55555555, break_table,
					   select_table);
		break;
	case 1:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 2:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x5a5a5a5a,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 3:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x5a5a5a5a,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 4:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 5:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 6:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0xaaaa5aaa, break_table,
					   select_table);
		break;
	case 7:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0xa5555555,
					   0xaa5a5a5a, break_table,
					   select_table);
		break;
	case 8:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 9:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0xaaaa555a, break_table,
					   select_table);
		break;
	case 10:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0xaaaa5aaa, break_table,
					   select_table);
		break;
	case 11:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0xaaaaa5aa, break_table,
					   select_table);
		break;
	case 12:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0xaaaa55aa, break_table,
					   select_table);
		break;
	default:
		break;
	}
}

static void
halbtc8822b2ant_set_fw_ignore_wlan_act(struct btc_coexist *btcoexist,
				       bool enable)
{
	u8 h2c_parameter[1] = {0};
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	if (enable)
		h2c_parameter[0] |= BIT(0); /* function enable */

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
}

static void halbtc8822b2ant_ignore_wlan_act(struct btc_coexist *btcoexist,
					    bool force_exec, bool enable)
{
	coex_dm->cur_ignore_wlan_act = enable;

	if (!force_exec) {
		if (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act)
			return;
	}
	halbtc8822b2ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
}

static void halbtc8822b2ant_set_lps_rpwm(struct btc_coexist *btcoexist,
					 u8 lps_val, u8 rpwm_val)
{
	u8 lps = lps_val;
	u8 rpwm = rpwm_val;

	btcoexist->btc_set(btcoexist, BTC_SET_U1_LPS_VAL, &lps);
	btcoexist->btc_set(btcoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
}

static void halbtc8822b2ant_lps_rpwm(struct btc_coexist *btcoexist,
				     bool force_exec, u8 lps_val, u8 rpwm_val)
{
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	if (!force_exec) {
		if ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm))
			return;
	}
	halbtc8822b2ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
}

static void halbtc8822b2ant_ps_tdma_check_for_power_save_state(
	struct btc_coexist *btcoexist, bool new_ps_state)
{
	u8 lps_mode = 0x0;
	u8 h2c_parameter[5] = {0, 0, 0, 0x40, 0};
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	if (lps_mode) { /* already under LPS state */
		if (new_ps_state) {
			/* keep state under LPS, do nothing. */
		} else {
			/* will leave LPS state, turn off psTdma first */
			btcoexist->btc_fill_h2c(btcoexist, 0x60, 5,
						h2c_parameter);
		}
	} else { /* NO PS state */
		if (new_ps_state) {
			/* will enter LPS state, turn off psTdma first */
			btcoexist->btc_fill_h2c(btcoexist, 0x60, 5,
						h2c_parameter);
		} else {
			/* keep state under NO PS state, do nothing. */
		}
	}
}

static void halbtc8822b2ant_power_save_state(struct btc_coexist *btcoexist,
					     u8 ps_type, u8 lps_val,
					     u8 rpwm_val)
{
	bool low_pwr_disable = false;

	switch (ps_type) {
	case BTC_PS_WIFI_NATIVE:
		/* recover to original 32k low power setting */
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_NORMAL_LPS, NULL);
		coex_sta->force_lps_on = false;
		break;
	case BTC_PS_LPS_ON:
		halbtc8822b2ant_ps_tdma_check_for_power_save_state(btcoexist,
								   true);
		halbtc8822b2ant_lps_rpwm(btcoexist, NORMAL_EXEC, lps_val,
					 rpwm_val);
		/* when coex force to enter LPS, do not enter 32k low power. */
		low_pwr_disable = true;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		/* power save must executed before psTdma. */
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ENTER_LPS, NULL);
		coex_sta->force_lps_on = true;
		break;
	case BTC_PS_LPS_OFF:
		halbtc8822b2ant_ps_tdma_check_for_power_save_state(btcoexist,
								   false);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS, NULL);
		coex_sta->force_lps_on = false;
		break;
	default:
		break;
	}
}

static void halbtc8822b2ant_set_fw_pstdma(struct btc_coexist *btcoexist,
					  u8 byte1, u8 byte2, u8 byte3,
					  u8 byte4, u8 byte5)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[5] = {0};
	u8 real_byte1 = byte1, real_byte5 = byte5;
	bool ap_enable = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);

	if (ap_enable) {
		if (byte1 & BIT(4) && !(byte1 & BIT(5))) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], FW for AP mode\n");
			real_byte1 &= ~BIT(4);
			real_byte1 |= BIT(5);

			real_byte5 |= BIT(5);
			real_byte5 &= ~BIT(6);

			halbtc8822b2ant_power_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		}
	} else if (byte1 & BIT(4) && !(byte1 & BIT(5))) {
		halbtc8822b2ant_power_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
						 0x4);
	} else {
		halbtc8822b2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
	}

	h2c_parameter[0] = real_byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = real_byte5;

	coex_dm->ps_tdma_para[0] = real_byte1;
	coex_dm->ps_tdma_para[1] = byte2;
	coex_dm->ps_tdma_para[2] = byte3;
	coex_dm->ps_tdma_para[3] = byte4;
	coex_dm->ps_tdma_para[4] = real_byte5;

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
}

static void halbtc8822b2ant_ps_tdma(struct btc_coexist *btcoexist,
				    bool force_exec, bool turn_on, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 ps_tdma_byte4_modify, pre_ps_tdma_byte4_modify;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	/* 0x778 = 0x1 at wifi slot (no blocking BT Low-Pri pkts) */
	if ((bt_link_info->slave_role) && (bt_link_info->a2dp_exist))
		ps_tdma_byte4_modify = 0x1;
	else
		ps_tdma_byte4_modify = 0x0;

	if (pre_ps_tdma_byte4_modify != ps_tdma_byte4_modify) {
		force_exec = true;
		pre_ps_tdma_byte4_modify = ps_tdma_byte4_modify;
	}

	if (!force_exec) {
		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			return;
	}

	if (coex_dm->cur_ps_tdma_on) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** TDMA(on, %d) **********\n",
			 coex_dm->cur_ps_tdma);

		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x550, 0x8, 0x1); /* enable TBTT nterrupt */
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** TDMA(off, %d) **********\n",
			 coex_dm->cur_ps_tdma);
	}

	if (turn_on) {
		switch (type) {
		case 1:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x10, 0x03, 0xf1,
				0x54 | ps_tdma_byte4_modify);
			break;
		case 2:
		default:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x35, 0x03, 0x71,
				0x11 | ps_tdma_byte4_modify);
			break;
		case 3:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x3a, 0x3, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 4:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x21, 0x3, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 5:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x25, 0x3, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 6:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x10, 0x3, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 7:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x20, 0x3, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 11:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x30, 0x03, 0x71,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 12:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x21, 0x03, 0x71,
				0x11 | ps_tdma_byte4_modify);
			break;
		case 13:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x1c, 0x03, 0x71,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 14:
			halbtc8822b2ant_set_fw_pstdma(btcoexist, 0xe3, 0x30,
						      0x03, 0x71, 0x11);
			break;
		case 51:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x10, 0x03, 0xf1,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 101:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x10, 0x03, 0x70,
				0x54 | ps_tdma_byte4_modify);
			break;
		case 102:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xe3, 0x35, 0x03, 0x71,
				0x11 | ps_tdma_byte4_modify);
			break;
		case 103:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x3a, 0x3, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 104:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x21, 0x3, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 105:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x25, 0x3, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 106:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x10, 0x3, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 107:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x20, 0x3, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 151:
			halbtc8822b2ant_set_fw_pstdma(
				btcoexist, 0xd3, 0x10, 0x03, 0x70,
				0x50 | ps_tdma_byte4_modify);
			break;
		}
	} else {
		/* disable PS tdma */
		switch (type) {
		case 0:
			halbtc8822b2ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x40, 0x0);
			break;
		case 1:
			halbtc8822b2ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x48, 0x0);
			break;
		default:
			halbtc8822b2ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x40, 0x0);
			break;
		}
	}

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
}

/*anttenna control by bb mac bt antdiv pta to write 0x4c 0xcb4,0xcbd*/
static void halbtc8822b2ant_set_ext_ant_switch(struct btc_coexist *btcoexist,
					       bool force_exec, u8 ctrl_type,
					       u8 pos_type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool switch_polatiry_inverse = false;
	u8 regval_0xcbc = 0, regval_0x64;
	u32 u32tmp1 = 0, u32tmp2 = 0, u32tmp3 = 0;

	if (!rfe_type->ext_ant_switch_exist)
		return;

	coex_dm->cur_ext_ant_switch_status = (ctrl_type << 8) + pos_type;

	if (!force_exec) {
		if (coex_dm->pre_ext_ant_switch_status ==
		    coex_dm->cur_ext_ant_switch_status)
			return;
	}
	coex_dm->pre_ext_ant_switch_status = coex_dm->cur_ext_ant_switch_status;

	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);

	switch (ctrl_type) {
	default:
	case BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BBSW:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /*  0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x1); /* 0x4c[24] = 1 */
		/* BB SW, DPDT use RFE_ctrl8 and RFE_ctrl9 as conctrol pin */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4, 0xff,
						   0x77);

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x03, 01);

		break;
	case BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_PTA:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /* 0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x1); /* 0x4c[24] = 1 */
		/* PTA,  DPDT use RFE_ctrl8 and RFE_ctrl9 as conctrol pin */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4, 0xff,
						   0x66);

		/* 0xcb4[29:28] = 2b'10 for no switch_polatiry_inverse,
		 * DPDT_SEL_N =1, DPDT_SEL_P =0  @ GNT_BT=1
		 */
		regval_0xcbc = (!switch_polatiry_inverse ? 0x2 : 0x1);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbc, 0x03,
						   regval_0xcbc);

		break;
	case BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_ANTDIV:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /* 0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x1); /* 0x4c[24] = 1 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4, 0xff,
						   0x88);
		break;
	case BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_MAC:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x1); /*  0x4c[23] = 1 */

		/* 0x64[0] = 1b'0 for no switch_polatiry_inverse,
		 * DPDT_SEL_N =1, DPDT_SEL_P =0
		 */
		regval_0x64 = (!switch_polatiry_inverse ? 0x0 : 0x1);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x64, 0x1,
						   regval_0x64);
		break;
	case BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BT:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /* 0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x0); /* 0x4c[24] = 0 */

		/* no setup required, because  antenna switch control value by
		 * BT vendor 0x1c[1:0]
		 */
		break;
	}

	/* PAPE, LNA_ON control by BT while WLAN off for current leakage issue*/
	if (ctrl_type == BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BT) {
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x67, 0x20, 0x0); /* PAPE   0x64[29] = 0 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x67, 0x10, 0x0); /* LNA_ON 0x64[28] = 0 */
	} else {
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x67, 0x20, 0x1); /* PAPE   0x64[29] = 1 */
		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x67, 0x10, 0x1); /* LNA_ON 0x64[28] = 1 */
	}

#if BT_8822B_2ANT_COEX_DBG

	u32tmp1 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
	u32tmp2 = btcoexist->btc_read_4byte(btcoexist, 0x4c);
	u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0x64) & 0xff;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], (After Ext Ant switch setup) 0xcb4 = 0x%08x, 0x4c = 0x%08x, 0x64= 0x%02x\n",
		u32tmp1, u32tmp2, u32tmp3);
#endif
}

/* rf4 type by efuse, and for ant at main aux inverse use,
 * because is 2x2, and control types are the same, does not need
 */
static void halbtc8822b2ant_set_rfe_type(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;

	rfe_type->ext_band_switch_exist = false;
	rfe_type->ext_band_switch_type =
		BT_8822B_2ANT_EXT_BAND_SWITCH_USE_SPDT; /* SPDT; */
	rfe_type->ext_band_switch_ctrl_polarity = 0;
	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);

	if (rfe_type->ext_band_switch_exist) {
		/* band switch use RFE_ctrl1 (pin name: PAPE_A) and
		 * RFE_ctrl3 (pin name: LNAON_A)
		 */

		/* set RFE_ctrl1 as software control */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb0, 0xf0, 0x7);

		/* set RFE_ctrl3 as software control */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb1, 0xf0, 0x7);
	}

	/* the following setup should be got from Efuse in the future */
	rfe_type->rfe_module_type = board_info->rfe_type;

	rfe_type->ext_ant_switch_ctrl_polarity = 0;

	switch (rfe_type->rfe_module_type) {
	case 0:
	default:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 1:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 2:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 3:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 4:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 5:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 6:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 7:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_2ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	}
}

/* set gnt_wl gnt_bt control by sw high low, or hwpta while in
 * power on, ini, wlan off, wlan only, wl2g non-currrent, wl2g current, wl5g
 */
static void halbtc8822b2ant_set_ant_path(struct btc_coexist *btcoexist,
					 u8 ant_pos_type, bool force_exec,
					 u8 phase)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u8tmp = 0;
	u32 u32tmp1 = 0, u32tmp2 = 0, u32tmp3 = 0;

	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
					   0x0); /*  0x4c[23] = 0 */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
					   0x1); /* 0x4c[24] = 1 */

	coex_dm->cur_ant_pos_type = (ant_pos_type << 8) + phase;

	if (!force_exec) {
		if (coex_dm->cur_ant_pos_type == coex_dm->pre_ant_pos_type)
			return;
	}

	coex_dm->pre_ant_pos_type = coex_dm->cur_ant_pos_type;

#if BT_8822B_2ANT_COEX_DBG
	u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);
	u32tmp2 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x54);
	u8tmp = btcoexist->btc_read_1byte(btcoexist, 0x73);

	u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], (Before Ant Setup) 0xcb4 = 0x%x, 0x73 = 0x%x, 0x38= 0x%x, 0x54= 0x%x\n",
		u32tmp3, u8tmp, u32tmp1, u32tmp2);
#endif

	switch (phase) {
	case BT_8822B_2ANT_PHASE_COEX_POWERON:

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_BTSIDE);

		/* set GNT_BT to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_COEX_INIT:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /*  0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x1); /* 0x4c[24] = 1 */
		/* Disable LTE Coex Function in WiFi side
		 * (this should be on if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* GNT_WL_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_WL_VS_LTE, 0xffff);

		/* GNT_BT_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_BT_VS_LTE, 0xffff);

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_WLANONLY_INIT:
		/* Disable LTE Coex Function in WiFi side
		 * (this should be on if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* GNT_WL_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_WL_VS_LTE, 0xffff);

		/* GNT_BT_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_BT_VS_LTE, 0xffff);

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Low */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_LOW);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_WLAN_OFF:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /* 0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x0); /* 0x4c[24] = 0 */
		/* Disable LTE Coex Function in WiFi side */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* set Path control owner to BT */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_BTSIDE);

		/* Set Ext Ant Switch to BT control at wifi off step */
		halbtc8822b2ant_set_ext_ant_switch(
			btcoexist, FORCE_EXEC,
			BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BT,
			BT_8822B_2ANT_EXT_ANT_SWITCH_MAIN_TO_NOCARE);
		coex_sta->run_time_state = false;
		break;
	case BT_8822B_2ANT_PHASE_2G_RUNTIME:
	case BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT:

		/* set Path control owner to WL at runtime step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		if (phase == BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT) {
			/* set GNT_BT to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_bt(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);

			/* Set GNT_WL to SW High */
			halbtc8822b2ant_ltecoex_set_gnt_wl(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
				BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ************* under2g 0xcbd setting =2 *************\n");

			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd,
							   0x03, 02);
		} else {
			/* set GNT_BT to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_bt(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);

			/* Set GNT_WL to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_wl(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);
		}
		coex_sta->run_time_state = true;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ************* under2g 0xcbd setting =2 *************\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x03, 02);
		break;
	case BT_8822B_2ANT_PHASE_5G_RUNTIME:

		/* set Path control owner to WL at runtime step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		coex_sta->run_time_state = true;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ************* under5g 0xcbd setting =1 *************\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x03, 01);

		break;
	case BT_8822B_2ANT_PHASE_BTMPMODE:
		/* Disable LTE Coex Function in WiFi side */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* set Path control owner to WL */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		/* Set GNT_WL to SW Lo */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_LOW);

		coex_sta->run_time_state = false;
		break;
	}
#if BT_8822B_2ANT_COEX_DBG
	u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);
	u32tmp2 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x54);
	u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
	u8tmp = btcoexist->btc_read_1byte(btcoexist, 0x73);

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], (After Ant-Setup phase---%d) 0xcb4 = 0x%x, 0x73 = 0x%x, 0x38= 0x%x, 0x54= 0x%x\n",
		phase, u32tmp3, u8tmp, u32tmp1, u32tmp2);

#endif
}

static u8 halbtc8822b2ant_action_algorithm(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8822B_2ANT_COEX_ALGO_UNDEFINED;
	u8 num_of_diff_profile = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	if (!bt_link_info->bt_link_exist) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], No BT link exists!!!\n");
		return algorithm;
	}

	if (bt_link_info->sco_exist)
		num_of_diff_profile++;
	if (bt_link_info->hid_exist)
		num_of_diff_profile++;
	if (bt_link_info->pan_exist)
		num_of_diff_profile++;
	if (bt_link_info->a2dp_exist)
		num_of_diff_profile++;

	if (num_of_diff_profile == 0) {
		if (bt_link_info->acl_busy) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], No-Profile busy\n");
			algorithm = BT_8822B_2ANT_COEX_ALGO_NOPROFILEBUSY;
		}
	} else if (num_of_diff_profile == 1) {
		if (bt_link_info->sco_exist) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], SCO only\n");
			algorithm = BT_8822B_2ANT_COEX_ALGO_SCO;
		} else {
			if (bt_link_info->hid_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], HID only\n");
				algorithm = BT_8822B_2ANT_COEX_ALGO_HID;
			} else if (bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], A2DP only\n");
				algorithm = BT_8822B_2ANT_COEX_ALGO_A2DP;
			} else if (bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], PAN(HS) only\n");
					algorithm =
						BT_8822B_2ANT_COEX_ALGO_PANHS;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], PAN(EDR) only\n");
					algorithm =
						BT_8822B_2ANT_COEX_ALGO_PANEDR;
				}
			}
		}
	} else if (num_of_diff_profile == 2) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], SCO + HID\n");
				algorithm = BT_8822B_2ANT_COEX_ALGO_SCO;
			} else if (bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], SCO + A2DP ==> A2DP\n");
				algorithm = BT_8822B_2ANT_COEX_ALGO_A2DP;
			} else if (bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], SCO + PAN(HS)\n");
					algorithm = BT_8822B_2ANT_COEX_ALGO_SCO;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], SCO + PAN(EDR)\n");
					algorithm =
						BT_8822B_2ANT_COEX_ALGO_PANEDR;
				}
			}
		} else {
			if (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) {
				{
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], HID + A2DP\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_HID_A2DP;
				}
			} else if (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], HID + PAN(HS)\n");
					algorithm = BT_8822B_2ANT_COEX_ALGO_HID;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], HID + PAN(EDR)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], A2DP + PAN(HS)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_A2DP_PANHS;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], A2DP + PAN(EDR)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_PANEDR_A2DP;
				}
			}
		}
	} else if (num_of_diff_profile == 3) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) {
				RT_TRACE(
					rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + HID + A2DP ==> HID + A2DP\n");
				algorithm = BT_8822B_2ANT_COEX_ALGO_HID_A2DP;
			} else if (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(HS)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_PANEDR_HID;
				} else {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(EDR)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(HS)\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_A2DP_PANHS;
				} else {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(EDR) ==> HID\n");
					algorithm =
					    BT_8822B_2ANT_COEX_ALGO_PANEDR_A2DP;
				}
			}
		} else {
			if (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + A2DP + PAN(HS)\n");
					algorithm =
					BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				} else {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + A2DP + PAN(EDR)\n");
					algorithm =
					BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				}
			}
		}
	} else if (num_of_diff_profile >= 3) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], Error!!! SCO + HID + A2DP + PAN(HS)\n");
					algorithm =
					BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				} else {
					RT_TRACE(
						rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + A2DP + PAN(EDR)==>PAN(EDR)+HID\n");
					algorithm =
					BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				}
			}
		}
	}

	return algorithm;
}

static void halbtc8822b2ant_action_coex_all_off(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

	/* fw all off */
	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
}

static void halbtc8822b2ant_action_wifi_under5g(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	/* fw all off */
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ************* under5g *************\n");
	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				     BT_8822B_2ANT_PHASE_5G_RUNTIME);
}

static void halbtc8822b2ant_action_bt_inquiry(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool scan = false, link = false, roam = false;
	bool wifi_busy = false;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	if (link || roam || coex_sta->wifi_is_high_pri_task) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi link/roam/hi-pri-task process + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 11);

	} else if (scan) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi scan process + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

		if (coex_sta->bt_create_connection)
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						12);
		else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						11);

	} else if (wifi_connected) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi connected + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

		if (wifi_busy) {
			if ((bt_link_info->a2dp_exist) &&
			    (bt_link_info->acl_busy))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 13);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 11);

		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						13);

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi no-link + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	}

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
}

static void
halbtc8822b2ant_action_wifi_link_process(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);

	if ((bt_link_info->a2dp_exist) && (bt_link_info->acl_busy))
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
	else
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 11);
}

static void
halbtc8822b2ant_action_wifi_nonconnected(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

	/* fw all off */
	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
}

static void halbtc8822b2ant_action_bt_idle(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;

	bool wifi_connected = false;
	bool scan = false, link = false, roam = false;
	bool wifi_busy = false;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	if (scan || link || roam) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi link process + BT Idle!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 11);
	} else if (wifi_connected) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi connected + BT Idle!!\n");

		if (wifi_busy) {
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 0);
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);
		} else {
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 0);
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);
		}

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi no-link + BT Idle!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	}

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
}

/* SCO only or SCO+PAN(HS) */
static void halbtc8822b2ant_action_sco(struct btc_coexist *btcoexist)
{
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	}
}

static void halbtc8822b2ant_action_hid(struct btc_coexist *btcoexist)
{
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;
		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	}
}

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
static void halbtc8822b2ant_action_a2dp(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false, wifi_turbo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "############# [BTCoex],  scan_ap_num = %d\n",
		 coex_sta->scan_ap_num);

	if ((wifi_busy) && (coex_sta->scan_ap_num <= 4))
		wifi_turbo = true;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			if (coex_sta->is_setup_link)
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 51);
			else {
				halbtc8822b2ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 12);
				halbtc8822b2ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					NORMAL_EXEC,
				    BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 1);
			}
		} else

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						2);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		if (wifi_turbo)
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
		else
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 7);

		if (wifi_busy) {
			if (coex_sta->is_setup_link)
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 151);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 101);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						102);
	}
}

static void halbtc8822b2ant_action_pan_edr(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false, wifi_turbo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "############# [BTCoex],  scan_ap_num = %d\n",
		 coex_sta->scan_ap_num);

	if ((wifi_busy) && (coex_sta->scan_ap_num <= 4))
		wifi_turbo = true;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 0);
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						3);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						4);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		if (wifi_turbo)
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
		else
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 7);

		if (wifi_busy)
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						103);
		else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						104);
	}
}

/* PAN(HS) only */
static void halbtc8822b2ant_action_pan_hs(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false, wifi_turbo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "############# [BTCoex],  scan_ap_num = %d\n",
		 coex_sta->scan_ap_num);

	if ((wifi_busy) && (coex_sta->scan_ap_num <= 4))
		wifi_turbo = true;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	}
}

static void halbtc8822b2ant_action_hid_a2dp(struct btc_coexist *btcoexist)
{
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			if (coex_sta->is_setup_link)
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 51);
			else
				halbtc8822b2ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 12);
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						2);

	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		if ((wifi_busy) && (coex_sta->hid_busy_num >= 2))
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
		else
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);

		if (wifi_busy) {
			if (coex_sta->is_setup_link)
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 151);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 101);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						102);
	}
}

static void halbtc8822b2ant_action_a2dp_pan_hs(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false, wifi_turbo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "############# [BTCoex],  scan_ap_num = %d\n",
		 coex_sta->scan_ap_num);

	if ((wifi_busy) && (coex_sta->scan_ap_num <= 4))
		wifi_turbo = true;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			if ((coex_sta->a2dp_bit_pool > 40) &&
			    (coex_sta->a2dp_bit_pool < 255))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 7);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 5);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						6);

	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		if (wifi_turbo)
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
		else
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 7);

		if (wifi_busy) {
			if ((coex_sta->a2dp_bit_pool > 40) &&
			    (coex_sta->a2dp_bit_pool < 255))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 107);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 105);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						106);
	}
}

/* PAN(EDR)+A2DP */
static void halbtc8822b2ant_action_pan_edr_a2dp(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false, wifi_turbo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "############# [BTCoex],  scan_ap_num = %d\n",
		 coex_sta->scan_ap_num);

	if ((wifi_busy) && (coex_sta->scan_ap_num <= 4))
		wifi_turbo = true;

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			if (((coex_sta->a2dp_bit_pool > 40) &&
			     (coex_sta->a2dp_bit_pool < 255)) ||
			    (!coex_sta->is_A2DP_3M))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 7);
			else
				halbtc8822b2ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 0);
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						5);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						6);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		if (wifi_turbo)
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
		else
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 7);

		if (wifi_busy) {
			if ((coex_sta->a2dp_bit_pool > 40) &&
			    (coex_sta->a2dp_bit_pool < 255))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 107);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 105);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						106);
	}
}

static void halbtc8822b2ant_action_pan_edr_hid(struct btc_coexist *btcoexist)
{
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy)

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						3);
		else

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						4);

	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);

		if (wifi_busy)

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						103);
		else

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						104);
	}
}

/* HID+A2DP+PAN(EDR) */
static void
halbtc8822b2ant_action_hid_a2dp_pan_edr(struct btc_coexist *btcoexist)
{
	static u8 prewifi_rssi_state = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state, bt_rssi_state;

	static u8 prewifi_rssi_state2 = BTC_RSSI_STATE_LOW;
	static u8 pre_bt_rssi_state2 = BTC_RSSI_STATE_LOW;
	u8 wifi_rssi_state2, bt_rssi_state2;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	wifi_rssi_state = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state, 2, coex_sta->wifi_coex_thres,
		0);

	wifi_rssi_state2 = halbtc8822b2ant_wifi_rssi_state(
		btcoexist, &prewifi_rssi_state2, 2, coex_sta->wifi_coex_thres2,
		0);

	bt_rssi_state = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state, 2, coex_sta->bt_coex_thres, 0);

	bt_rssi_state2 = halbtc8822b2ant_bt_rssi_state(
		btcoexist, &pre_bt_rssi_state2, 2, coex_sta->bt_coex_thres2, 0);

	if (BTC_RSSI_HIGH(wifi_rssi_state) && BTC_RSSI_HIGH(bt_rssi_state)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		halbtc8822b2ant_set_ant_path(
			btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
			BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (BTC_RSSI_HIGH(wifi_rssi_state2) &&
		   BTC_RSSI_HIGH(bt_rssi_state2)) {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xc8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		coex_dm->is_switch_to_1dot5_ant = false;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

		if (wifi_busy) {
			if (((coex_sta->a2dp_bit_pool > 40) &&
			     (coex_sta->a2dp_bit_pool < 255)) ||
			    (!coex_sta->is_A2DP_3M))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 7);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 5);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						6);
	} else {
		halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
		halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		coex_dm->is_switch_to_1dot5_ant = true;

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);

		if (wifi_busy) {
			if ((coex_sta->a2dp_bit_pool > 40) &&
			    (coex_sta->a2dp_bit_pool < 255))
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 107);
			else
				halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 105);
		} else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						106);
	}
}

static void halbtc8822b2ant_action_bt_whck_test(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
}

static void
halbtc8822b2ant_action_wifi_multi_port(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* hw all off */
	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
}

static void halbtc8822b2ant_run_coexist_mechanism(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;
	u32 num_of_wifi_link = 0;
	u32 wifi_link_status = 0;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool miracast_plus_bt = false;
	bool scan = false, link = false, roam = false, wifi_connected = false,
	     wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], RunCoexistMechanism()===>\n");

	if (btcoexist->manual_control) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n");
		return;
	}

	if (btcoexist->stop_coex_dm) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Stop Coex DM <===\n");
		return;
	}

	if (coex_sta->under_ips) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], wifi is under IPS !!!\n");
		return;
	}

	if (!coex_sta->run_time_state) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], return for run_time_state = false !!!\n");
		return;
	}

	if (coex_sta->freeze_coexrun_by_btinfo) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), return for freeze_coexrun_by_btinfo\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (wifi_under_5g) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under 5G!!!\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);
		return;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], WiFi is under 2G!!!\n");

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME);

	if (coex_sta->bt_whck_test) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under WHCK TEST!!!\n");
		halbtc8822b2ant_action_bt_whck_test(btcoexist);
		return;
	}

	if (coex_sta->bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is disabled!!!\n");
		halbtc8822b2ant_action_coex_all_off(btcoexist);
		return;
	}

	if (coex_sta->c2h_bt_inquiry_page) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under inquiry/page scan !!\n");
		halbtc8822b2ant_action_bt_inquiry(btcoexist);
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	if (scan || link || roam) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under Link Process !!\n");
		halbtc8822b2ant_action_wifi_link_process(btcoexist);
		return;
	}

	/* for P2P */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status >> 16;

	if ((num_of_wifi_link >= 2) ||
	    (wifi_link_status & WIFI_P2P_GO_CONNECTED)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex],  Multi-Port num_of_wifi_link = %d, wifi_link_status = 0x%x\n",
			num_of_wifi_link, wifi_link_status);

		if (bt_link_info->bt_link_exist)
			miracast_plus_bt = true;
		else
			miracast_plus_bt = false;

		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);
		halbtc8822b2ant_action_wifi_multi_port(btcoexist);

		return;
	}

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	algorithm = halbtc8822b2ant_action_algorithm(btcoexist);
	coex_dm->cur_algorithm = algorithm;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	if (!wifi_connected) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, wifi non-connected!!.\n");
		halbtc8822b2ant_action_wifi_nonconnected(btcoexist);

	} else if ((BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status) ||
		   (BT_8822B_2ANT_BT_STATUS_CONNECTED_IDLE ==
		    coex_dm->bt_status)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, bt idle!!.\n");

		halbtc8822b2ant_action_bt_idle(btcoexist);

	} else {
		if (coex_dm->cur_algorithm != coex_dm->pre_algorithm) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], pre_algorithm=%d, cur_algorithm=%d\n",
				coex_dm->pre_algorithm, coex_dm->cur_algorithm);
		}

		switch (coex_dm->cur_algorithm) {
		case BT_8822B_2ANT_COEX_ALGO_SCO:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = SCO.\n");
			halbtc8822b2ant_action_sco(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = HID.\n");
			halbtc8822b2ant_action_hid(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = A2DP.\n");
			halbtc8822b2ant_action_a2dp(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_A2DP_PANHS:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS).\n");
			halbtc8822b2ant_action_a2dp_pan_hs(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_PANEDR:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR).\n");
			halbtc8822b2ant_action_pan_edr(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_PANHS:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HS mode.\n");
			halbtc8822b2ant_action_pan_hs(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_PANEDR_A2DP:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN+A2DP.\n");
			halbtc8822b2ant_action_pan_edr_a2dp(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_PANEDR_HID:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID.\n");
			halbtc8822b2ant_action_pan_edr_hid(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN.\n");
			halbtc8822b2ant_action_hid_a2dp_pan_edr(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_HID_A2DP:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP.\n");
			halbtc8822b2ant_action_hid_a2dp(btcoexist);
			break;
		case BT_8822B_2ANT_COEX_ALGO_NOPROFILEBUSY:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = No-Profile busy.\n");
			halbtc8822b2ant_action_bt_idle(btcoexist);
			break;
		default:
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n");
			halbtc8822b2ant_action_coex_all_off(btcoexist);
			break;
		}
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	}
}

static void halbtc8822b2ant_init_coex_dm(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Coex Mechanism Init!!\n");

	halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, false);

	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT);

	/* fw all off */
	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);
	halbtc8822b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	coex_sta->pop_event_cnt = 0;
	coex_sta->cnt_remote_name_req = 0;
	coex_sta->cnt_reinit = 0;
	coex_sta->cnt_setup_link = 0;
	coex_sta->cnt_ign_wlan_act = 0;
	coex_sta->cnt_page = 0;

	halbtc8822b2ant_query_bt_info(btcoexist);
}

static void halbtc8822b2ant_init_hw_config(struct btc_coexist *btcoexist,
					   bool wifi_only)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32tmp1 = 0, u32tmp2 = 0, u32tmp3 = 0;
	u32 RTL97F_8822B = 0;

	u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
	u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);
	u32tmp2 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x54);

	if (RTL97F_8822B) {
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x66, 0x04, 0x0);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x41, 0x02, 0x0);

		/* set GNT_BT to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		return;
	}

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], (Before Init HW config) 0xcb4 = 0x%x, 0x38= 0x%x, 0x54= 0x%x\n",
		u32tmp3, u32tmp1, u32tmp2);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], 2Ant Init HW Config!!\n");

	coex_sta->bt_coex_supported_feature = 0;
	coex_sta->bt_coex_supported_version = 0;
	coex_sta->bt_ble_scan_type = 0;
	coex_sta->bt_ble_scan_para[0] = 0;
	coex_sta->bt_ble_scan_para[1] = 0;
	coex_sta->bt_ble_scan_para[2] = 0;
	coex_sta->bt_reg_vendor_ac = 0xffff;
	coex_sta->bt_reg_vendor_ae = 0xffff;
	coex_sta->isolation_btween_wb = BT_8822B_2ANT_DEFAULT_ISOLATION;

	/* 0xf0[15:12] --> Chip Cut information */
	coex_sta->cut_version =
		(btcoexist->btc_read_1byte(btcoexist, 0xf1) & 0xf0) >> 4;

	coex_sta->dis_ver_info_cnt = 0;

	halbtc8822b2ant_coex_switch_threshold(btcoexist,
					      coex_sta->isolation_btween_wb);

	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x550, 0x8,
					   0x1); /* enable TBTT nterrupt */

	/* BT report packet sample rate	 */
	btcoexist->btc_write_1byte(btcoexist, 0x790, 0x5);

	/* Init 0x778 = 0x1 for 2-Ant */
	btcoexist->btc_write_1byte(btcoexist, 0x778, 0x1);

	/* Enable PTA (3-wire function form BT side) */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x40, 0x20, 0x1);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x41, 0x02, 0x1);

	/* Enable PTA (tx/rx signal form WiFi side) */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4c6, 0x10, 0x1);

	halbtc8822b2ant_enable_gnt_to_gpio(btcoexist, true);

	/*GNT_BT=1 while select both */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x763, 0x10, 0x1);

	/* check if WL firmware download ok */
	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ONOFF, true);

	/* Enable counter statistics */
	btcoexist->btc_write_1byte(
		btcoexist, 0x76e,
		0x4); /* 0x76e[3] =1, WLAN_Act control by PTA */

	halbtc8822b2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	halbtc8822b2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);

	psd_scan->ant_det_is_ant_det_available = true;

	if (wifi_only) {
		coex_sta->concurrent_rx_mode_on = false;
		/* Path config	 */
		/* Set Antenna Path */
		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_WLANONLY_INIT);

		btcoexist->stop_coex_dm = true;
	} else {
		/* Set BT polluted packet on for Tx rate adaptive not including
		 * Tx retry break by PTA, 0x45c[19] =1
		 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x45e, 0x8, 0x1);

		coex_sta->concurrent_rx_mode_on = true;

		/* RF 0x1[1] = 0->Set GNT_WL_RF_Rx always = 1 for
		 * con-current Rx, mask Tx only
		 */
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0x2, 0x0);

		/* Set Antenna Path */
		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_COEX_INIT);

		btcoexist->stop_coex_dm = false;
	}
}

/* ************************************************************
 * work around function start with wa_halbtc8822b2ant_
 * ************************************************************
 * ************************************************************
 * extern function start with ex_halbtc8822b2ant_
 * *************************************************************/
void ex_halbtc8822b2ant_power_on_setting(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x0;
	u16 u16tmp = 0x0;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"xxxxxxxxxxxxxxxx Execute 8822b 2-Ant PowerOn Setting xxxxxxxxxxxxxxxx!!\n");

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "Ant Det Finish = %s, Ant Det Number  = %d\n",
		 (board_info->btdm_ant_det_finish ? "Yes" : "No"),
		 board_info->btdm_ant_num_by_ant_det);

	btcoexist->stop_coex_dm = true;
	psd_scan->ant_det_is_ant_det_available = false;

	/* enable BB, REG_SYS_FUNC_EN such that we can write BB Reg correctly */
	u16tmp = btcoexist->btc_read_2byte(btcoexist, 0x2);
	btcoexist->btc_write_2byte(btcoexist, 0x2, u16tmp | BIT(0) | BIT(1));

	/* Local setting bit define */
	/*	BIT0: "0" for no antenna inverse; "1" for antenna inverse  */
	/*	BIT1: "0" for internal switch; "1" for external switch */
	/*	BIT2: "0" for one antenna; "1" for two antenna */
	/* NOTE: here default all internal switch and 1-antenna ==>
	 * BIT1=0 and BIT2=0
	 */

	/* Check efuse 0xc3[6] for Single Antenna Path */
	if (board_info->single_ant_path == 0) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], **********  Single Antenna, Antenna at Aux Port\n");

		board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;

		u8tmp = 7;
	} else if (board_info->single_ant_path == 1) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], **********  Single Antenna, Antenna at Main Port\n");

		board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;

		u8tmp = 6;
	}

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ********** (Power On) single_ant_path  = %d, btdm_ant_pos = %d\n",
		board_info->single_ant_path, board_info->btdm_ant_pos);

	/* Setup RF front end type */
	halbtc8822b2ant_set_rfe_type(btcoexist);

	/* Set Antenna Path to BT side */
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				     BT_8822B_2ANT_PHASE_COEX_POWERON);

	/* Save"single antenna position" info in Local register setting for
	 * FW reading, because FW may not ready at power on
	 */
	if (btcoexist->chip_interface == BTC_INTF_PCI)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0x3e0, u8tmp);
	else if (btcoexist->chip_interface == BTC_INTF_USB)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);
	else if (btcoexist->chip_interface == BTC_INTF_SDIO)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60, u8tmp);

	/* enable GNT_WL/GNT_BT debug signal to GPIO14/15 */
	halbtc8822b2ant_enable_gnt_to_gpio(btcoexist, true);

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], **********  LTE coex Reg 0x38 (Power-On) = 0x%x**********\n",
		halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38));

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], **********  MAC Reg 0x70/ BB Reg 0xcb4 (Power-On) = 0x%x / 0x%x\n",
		btcoexist->btc_read_4byte(btcoexist, 0x70),
		btcoexist->btc_read_4byte(btcoexist, 0xcb4));
}

void ex_halbtc8822b2ant_pre_load_firmware(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x4; /* Set BIT2 by default since it's 2ant case */

	/* */
	/* S0 or S1 setting and Local register setting
	 * (By the setting fw can get ant number, S0/S1, ... info)
	 */
	/* Local setting bit define */
	/*	BIT0: "0" for no antenna inverse; "1" for antenna inverse  */
	/*	BIT1: "0" for internal switch; "1" for external switch */
	/*	BIT2: "0" for one antenna; "1" for two antenna */
	/* NOTE: here default all internal switch and 1-antenna ==>
	 *       BIT1=0 and BIT2=0
	 */
	if (btcoexist->chip_interface == BTC_INTF_USB) {
		/* fixed at S0 for USB interface */
		u8tmp |= 0x1; /* antenna inverse */
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);
	} else {
		/* for PCIE and SDIO interface, we check efuse 0xc3[6] */
		if (board_info->single_ant_path == 0) {
		} else if (board_info->single_ant_path == 1) {
			/* set to S0 */
			u8tmp |= 0x1; /* antenna inverse */
		}

		if (btcoexist->chip_interface == BTC_INTF_PCI)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x3e0,
							     u8tmp);
		else if (btcoexist->chip_interface == BTC_INTF_SDIO)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60,
							     u8tmp);
	}
}

void ex_halbtc8822b2ant_init_hw_config(struct btc_coexist *btcoexist,
				       bool wifi_only)
{
	halbtc8822b2ant_init_hw_config(btcoexist, wifi_only);
}

void ex_halbtc8822b2ant_init_coex_dm(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_init_coex_dm(btcoexist);
}

void ex_halbtc8822b2ant_display_coex_info(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	u8 *cli_buf = btcoexist->cli_buf;
	u8 u8tmp[4], i, ps_tdma_case = 0;
	u32 u32tmp[4];
	u16 u16tmp[4];
	u32 fa_ofdm, fa_cck, cca_ofdm, cca_cck;
	u32 fw_ver = 0, bt_patch_ver = 0, bt_coex_ver = 0;
	static u8 pop_report_in_10s;
	u32 phyver = 0;
	bool lte_coex_on = false;

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n ============[BT Coexist info]============");
	CL_PRINTF(cli_buf);

	if (btcoexist->manual_control) {
		CL_SPRINTF(
			cli_buf, BT_TMP_BUF_SIZE,
			"\r\n ============[Under Manual Control]============");
		CL_PRINTF(cli_buf);
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
			   "\r\n ==========================================");
		CL_PRINTF(cli_buf);
	}

	if (psd_scan->ant_det_try_count == 0) {
		CL_SPRINTF(
			cli_buf, BT_TMP_BUF_SIZE,
			"\r\n %-35s = %d/ %d/ %s / %d",
			"Ant PG Num/ Mech/ Pos/ RFE", board_info->pg_ant_num,
			board_info->btdm_ant_num,
			(board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT ?
				 "Main" :
				 "Aux"),
			rfe_type->rfe_module_type);
		CL_PRINTF(cli_buf);
	} else {
		CL_SPRINTF(
			cli_buf, BT_TMP_BUF_SIZE,
			"\r\n %-35s = %d/ %d/ %s/ %d  (%d/%d/%d)",
			"Ant PG Num/ Mech(Ant_Det)/ Pos/ RFE",
			board_info->pg_ant_num,
			board_info->btdm_ant_num_by_ant_det,
			(board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT ?
				 "Main" :
				 "Aux"),
			rfe_type->rfe_module_type, psd_scan->ant_det_try_count,
			psd_scan->ant_det_fail_count, psd_scan->ant_det_result);
		CL_PRINTF(cli_buf);

		if (board_info->btdm_ant_det_finish) {
			if (psd_scan->ant_det_result != 12)
				CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
					   "\r\n %-35s = %s",
					   "Ant Det PSD Value",
					   psd_scan->ant_det_peak_val);
			else
				CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
					   "\r\n %-35s = %d",
					   "Ant Det PSD Value",
					   psd_scan->ant_det_psd_scan_peak_val /
						   100);
			CL_PRINTF(cli_buf);
		}
	}

	/*bt_patch_ver = btcoexist->bt_info.bt_get_fw_ver;*/
	bt_patch_ver = btcoexist->bt_info.bt_get_fw_ver;
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	phyver = btcoexist->btc_get_bt_phydm_version(btcoexist);

	bt_coex_ver = (coex_sta->bt_coex_supported_version & 0xff);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = %d_%02x/ 0x%02x/ 0x%02x (%s)",
		   "CoexVer WL/  BT_Desired/ BT_Report",
		   glcoex_ver_date_8822b_2ant, glcoex_ver_8822b_2ant,
		   glcoex_ver_btdesired_8822b_2ant, bt_coex_ver,
		   (bt_coex_ver == 0xff ?
			    "Unknown" :
			    (bt_coex_ver >= glcoex_ver_btdesired_8822b_2ant ?
				     "Match" :
				     "Mis-Match")));
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/ 0x%x/ v%d/ %c",
		   "W_FW/ B_FW/ Phy/ Kt", fw_ver, bt_patch_ver, phyver,
		   coex_sta->cut_version + 65);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %02x %02x %02x ",
		   "AFH Map to BT", coex_dm->wifi_chnl_info[0],
		   coex_dm->wifi_chnl_info[1], coex_dm->wifi_chnl_info[2]);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d / %d / %d ",
		   "Isolation/WL_Thres/BT_Thres", coex_sta->isolation_btween_wb,
		   coex_sta->wifi_coex_thres, coex_sta->bt_coex_thres);
	CL_PRINTF(cli_buf);

	/* wifi status */
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s",
		   "============[Wifi Status]============");
	CL_PRINTF(cli_buf);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_WIFI_STATUS);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s",
		   "============[BT Status]============");
	CL_PRINTF(cli_buf);

	pop_report_in_10s++;
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = [%s/ %d dBm/ %d/ %d] ",
		   "BT [status/ rssi/ retryCnt/ popCnt]",
		   ((coex_sta->bt_disabled) ?
		       ("disabled") :
		       ((coex_sta->c2h_bt_inquiry_page) ?
			   ("inquiry/page") :
			   ((BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
				coex_dm->bt_status) ?
				   "non-connected idle" :
				   ((BT_8822B_2ANT_BT_STATUS_CONNECTED_IDLE ==
				       coex_dm->bt_status) ?
					   "connected-idle" :
					   "busy")))),
		   coex_sta->bt_rssi - 100, coex_sta->bt_retry_cnt,
		   coex_sta->pop_event_cnt);
	CL_PRINTF(cli_buf);

	if (pop_report_in_10s >= 5) {
		coex_sta->pop_event_cnt = 0;
		pop_report_in_10s = 0;
	}

	if (coex_sta->num_of_profile != 0)
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s%s%s%s%s",
			   "Profiles",
			   ((bt_link_info->a2dp_exist) ? "A2DP," : ""),
			   ((bt_link_info->sco_exist) ? "SCO," : ""),
			   ((bt_link_info->hid_exist) ?
				    ((coex_sta->hid_busy_num >= 2) ?
					     "HID(4/18)," :
					     "HID(2/18),") :
				    ""),
			   ((bt_link_info->pan_exist) ? "PAN," : ""),
			   ((coex_sta->voice_over_HOGP) ? "Voice" : ""));
	else
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = None",
			   "Profiles");

	CL_PRINTF(cli_buf);

	if (bt_link_info->a2dp_exist) {
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s/ %d/ %s",
			   "A2DP Rate/Bitpool/Auto_Slot",
			   ((coex_sta->is_A2DP_3M) ? "3M" : "No_3M"),
			   coex_sta->a2dp_bit_pool,
			   ((coex_sta->is_autoslot) ? "On" : "Off"));
		CL_PRINTF(cli_buf);
	}

	if (bt_link_info->hid_exist) {
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d",
			   "HID PairNum/Forbid_Slot", coex_sta->hid_pair_cnt,
			   coex_sta->forbidden_slot);
		CL_PRINTF(cli_buf);
	}

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s / %s/ 0x%x",
		   "Role/IgnWlanAct/Feature",
		   ((bt_link_info->slave_role) ? "Slave" : "Master"),
		   ((coex_dm->cur_ignore_wlan_act) ? "Yes" : "No"),
		   coex_sta->bt_coex_supported_feature);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d/ %d/ %d/ %d",
		   "ReInit/ReLink/IgnWlact/Page/NameReq", coex_sta->cnt_reinit,
		   coex_sta->cnt_setup_link, coex_sta->cnt_ign_wlan_act,
		   coex_sta->cnt_page, coex_sta->cnt_remote_name_req);
	CL_PRINTF(cli_buf);

	halbtc8822b2ant_read_score_board(btcoexist, &u16tmp[0]);

	if ((coex_sta->bt_reg_vendor_ae == 0xffff) ||
	    (coex_sta->bt_reg_vendor_ac == 0xffff))
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = x/ x/ %04x",
			   "0xae[4]/0xac[1:0]/Scoreboard", u16tmp[0]);
	else
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
			   "\r\n %-35s = 0x%x/ 0x%x/ %04x",
			   "0xae[4]/0xac[1:0]/Scoreboard",
			   (int)((coex_sta->bt_reg_vendor_ae & BIT(4)) >> 4),
			   coex_sta->bt_reg_vendor_ac & 0x3, u16tmp[0]);
	CL_PRINTF(cli_buf);

	for (i = 0; i < BT_INFO_SRC_8822B_2ANT_MAX; i++) {
		if (coex_sta->bt_info_c2h_cnt[i]) {
			CL_SPRINTF(
				cli_buf, BT_TMP_BUF_SIZE,
				"\r\n %-35s = %02x %02x %02x %02x %02x %02x %02x(%d)",
				glbt_info_src_8822b_2ant[i],
				coex_sta->bt_info_c2h[i][0],
				coex_sta->bt_info_c2h[i][1],
				coex_sta->bt_info_c2h[i][2],
				coex_sta->bt_info_c2h[i][3],
				coex_sta->bt_info_c2h[i][4],
				coex_sta->bt_info_c2h[i][5],
				coex_sta->bt_info_c2h[i][6],
				coex_sta->bt_info_c2h_cnt[i]);
			CL_PRINTF(cli_buf);
		}
	}

	/* Sw mechanism	 */
	if (btcoexist->manual_control)
		CL_SPRINTF(
			cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s",
			"============[mechanism] (before Manual)============");
	else
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s",
			   "============[Mechanism]============");

	CL_PRINTF(cli_buf);

	ps_tdma_case = coex_dm->cur_ps_tdma;

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = %02x %02x %02x %02x %02x (case-%d, %s, %s)",
		   "TDMA", coex_dm->ps_tdma_para[0], coex_dm->ps_tdma_para[1],
		   coex_dm->ps_tdma_para[2], coex_dm->ps_tdma_para[3],
		   coex_dm->ps_tdma_para[4], ps_tdma_case,
		   (coex_dm->cur_ps_tdma_on ? "TDMA On" : "TDMA Off"),
		   (coex_dm->is_switch_to_1dot5_ant ? "1.5Ant" : "2Ant"));
	CL_PRINTF(cli_buf);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x6c0);
	u32tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0x6c4);
	u32tmp[2] = btcoexist->btc_read_4byte(btcoexist, 0x6c8);
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = %d/ 0x%x/ 0x%x/ 0x%x",
		   "Table/0x6c0/0x6c4/0x6c8", coex_sta->coex_table_type,
		   u32tmp[0], u32tmp[1], u32tmp[2]);
	CL_PRINTF(cli_buf);

	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x778);
	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x6cc);
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/ 0x%x",
		   "0x778/0x6cc", u8tmp[0], u32tmp[0]);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s/ %s/ %s",
		   "AntDiv/ForceLPS/LPRA",
		   ((board_info->ant_div_cfg) ? "On" : "Off"),
		   ((coex_sta->force_lps_on) ? "On" : "Off"),
		   ((coex_dm->cur_low_penalty_ra) ? "On" : "Off"));
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/ 0x%x",
		   "WL_DACSwing/ BT_Dec_Pwr", coex_dm->cur_fw_dac_swing_lvl,
		   coex_dm->cur_bt_dec_pwr_lvl);
	CL_PRINTF(cli_buf);

	u32tmp[0] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);
	lte_coex_on = ((u32tmp[0] & BIT(7)) >> 7) ? true : false;

	if (lte_coex_on) {
		u32tmp[0] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xa0);
		u32tmp[1] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xa4);
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/ 0x%x",
			   "LTE Coex Table W_L/B_L", u32tmp[0] & 0xffff,
			   u32tmp[1] & 0xffff);
		CL_PRINTF(cli_buf);

		u32tmp[0] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xa8);
		u32tmp[1] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xac);
		u32tmp[2] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xb0);
		u32tmp[3] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								      0xb4);
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
			   "\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
			   "LTE Break Table W_L/B_L/L_W/L_B",
			   u32tmp[0] & 0xffff, u32tmp[1] & 0xffff,
			   u32tmp[2] & 0xffff, u32tmp[3] & 0xffff);
		CL_PRINTF(cli_buf);
	}

	/* Hw setting		 */
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s",
		   "============[Hw setting]============");
	CL_PRINTF(cli_buf);
	u32tmp[0] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);
	u32tmp[1] = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x54);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x73);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s/ %s",
		   "LTE Coex/Path Owner", ((lte_coex_on) ? "On" : "Off"),
		   ((u8tmp[0] & BIT(2)) ? "WL" : "BT"));
	CL_PRINTF(cli_buf);

	if (lte_coex_on) {
		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
			   "\r\n %-35s = %d/ %d/ %d/ %d",
			   "LTE 3Wire/OPMode/UART/UARTMode",
			   (int)((u32tmp[0] & BIT(6)) >> 6),
			   (int)((u32tmp[0] & (BIT(5) | BIT(4))) >> 4),
			   (int)((u32tmp[0] & BIT(3)) >> 3),
			   (int)(u32tmp[0] & (BIT(2) | BIT(1) | BIT(0))));
		CL_PRINTF(cli_buf);

		CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d",
			   "LTE_Busy/UART_Busy",
			   (int)((u32tmp[1] & BIT(1)) >> 1),
			   (int)(u32tmp[1] & BIT(0)));
		CL_PRINTF(cli_buf);
	}
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = %s (BB:%s)/ %s (BB:%s)/ %s",
		   "GNT_WL_Ctrl/GNT_BT_Ctrl/Dbg",
		   ((u32tmp[0] & BIT(12)) ? "SW" : "HW"),
		   ((u32tmp[0] & BIT(8)) ? "SW" : "HW"),
		   ((u32tmp[0] & BIT(14)) ? "SW" : "HW"),
		   ((u32tmp[0] & BIT(10)) ? "SW" : "HW"),
		   ((u8tmp[0] & BIT(3)) ? "On" : "Off"));
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d",
		   "GNT_WL/GNT_BT", (int)((u32tmp[1] & BIT(2)) >> 2),
		   (int)((u32tmp[1] & BIT(3)) >> 3));
	CL_PRINTF(cli_buf);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0xcb0);
	u32tmp[1] = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0xcbd);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = 0x%04x/ 0x%04x/ 0x%x", "0xcb0/0xcb4/0xcbd",
		   u32tmp[0], u32tmp[1], u8tmp[0]);
	CL_PRINTF(cli_buf);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x4c);
	u8tmp[2] = btcoexist->btc_read_1byte(btcoexist, 0x64);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x4c6);
	u8tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0x40);
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x4c[24:23]/0x64[0]/x4c6[4]/0x40[5]",
		   (int)(u32tmp[0] & (BIT(24) | BIT(23))) >> 23, u8tmp[2] & 0x1,
		   (int)((u8tmp[0] & BIT(4)) >> 4),
		   (int)((u8tmp[1] & BIT(5)) >> 5));
	CL_PRINTF(cli_buf);

	u32tmp[0] = btcoexist->btc_read_4byte(btcoexist, 0x550);
	u8tmp[0] = btcoexist->btc_read_1byte(btcoexist, 0x522);
	u8tmp[1] = btcoexist->btc_read_1byte(btcoexist, 0x953);
	u8tmp[2] = btcoexist->btc_read_1byte(btcoexist, 0xc50);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = 0x%x/ 0x%x/ %s/ 0x%x",
		   "0x550/0x522/4-RxAGC/0xc50", u32tmp[0], u8tmp[0],
		   (u8tmp[1] & 0x2) ? "On" : "Off", u8tmp[2]);
	CL_PRINTF(cli_buf);

	fa_ofdm = btcoexist->btc_phydm_query_phy_counter(btcoexist,
							 "PHYDM_INFO_FA_OFDM");
	fa_cck = btcoexist->btc_phydm_query_phy_counter(btcoexist,
							"PHYDM_INFO_FA_CCK");
	cca_ofdm = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CCA_OFDM");
	cca_cck = btcoexist->btc_phydm_query_phy_counter(btcoexist,
							 "PHYDM_INFO_CCA_CCK");

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE,
		   "\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "CCK-CCA/CCK-FA/OFDM-CCA/OFDM-FA", cca_cck, fa_cck, cca_ofdm,
		   fa_ofdm);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d/ %d/ %d",
		   "CRC_OK CCK/11g/11n/11ac", coex_sta->crc_ok_cck,
		   coex_sta->crc_ok_11g, coex_sta->crc_ok_11n,
		   coex_sta->crc_ok_11n_vht);
	CL_PRINTF(cli_buf);

	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d/ %d/ %d",
		   "CRC_Err CCK/11g/11n/11ac", coex_sta->crc_err_cck,
		   coex_sta->crc_err_11g, coex_sta->crc_err_11n,
		   coex_sta->crc_err_11n_vht);
	CL_PRINTF(cli_buf);
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d",
		   "0x770(Hi-pri rx/tx)", coex_sta->high_priority_rx,
		   coex_sta->high_priority_tx);
	CL_PRINTF(cli_buf);
	CL_SPRINTF(cli_buf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d/ %d",
		   "0x774(Lo-pri rx/tx)", coex_sta->low_priority_rx,
		   coex_sta->low_priority_tx);
	CL_PRINTF(cli_buf);

	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS);
}

void ex_halbtc8822b2ant_ips_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_IPS_ENTER) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		coex_sta->under_lps = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, false);

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_WLAN_OFF);

		halbtc8822b2ant_action_coex_all_off(btcoexist);
	} else if (type == BTC_IPS_LEAVE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, true);
		halbtc8822b2ant_init_hw_config(btcoexist, false);
		halbtc8822b2ant_init_coex_dm(btcoexist);
		halbtc8822b2ant_query_bt_info(btcoexist);
	}
}

void ex_halbtc8822b2ant_lps_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_LPS_ENABLE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], LPS ENABLE notify\n");
		coex_sta->under_lps = true;
		coex_sta->under_ips = false;

		if (coex_sta->force_lps_on) { /* LPS No-32K */
			/* Write WL "Active" in Score-board for PS-TDMA */
			halbtc8822b2ant_post_state_to_bt(
				btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE,
				true);

		} else { /* LPS-32K, need check if this h2c 0x71 can work?? */
			/* Write WL "Non-Active" in Score-board for Native-PS */
			halbtc8822b2ant_post_state_to_bt(
				btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE,
				false);
		}

	} else if (type == BTC_LPS_DISABLE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], LPS DISABLE notify\n");
		coex_sta->under_lps = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
	}
}

void ex_halbtc8822b2ant_scan_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], SCAN notify()\n");

	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	/* this can't be removed for RF off_on event, or BT would dis-connect */
	halbtc8822b2ant_query_bt_info(btcoexist);

	if (type == BTC_SCAN_START) {
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G,
				   &wifi_under_5g);

		if (wifi_under_5g) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** SCAN START notify (5g)\n");

			halbtc8822b2ant_action_wifi_under5g(btcoexist);
			return;
		}

		coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** SCAN START notify (2g)\n");

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

		return;
	}

	if (type == BTC_SCAN_START_2G) {
		if (!wifi_connected)
			coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN START notify (2G)\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_SCAN, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_2G_RUNTIME);

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

	} else if (type == BTC_SCAN_FINISH) {
		coex_sta->wifi_is_high_pri_task = false;

		btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
				   &coex_sta->scan_ap_num);

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN FINISH notify  (Scan-AP = %d)\n",
			 coex_sta->scan_ap_num);

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_SCAN, false);

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
	}
}

void ex_halbtc8822b2ant_switchband_notify(struct btc_coexist *btcoexist,
					  u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_SWITCH_TO_5G) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], switchband_notify ---  switch to 5G\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);

	} else if (type == BTC_SWITCH_TO_24G_NOFORSCAN) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** switchband_notify BTC_SWITCH_TO_2G (no for scan)\n");

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], switchband_notify ---  switch to 2G\n");

		ex_halbtc8822b2ant_scan_notify(btcoexist, BTC_SCAN_START_2G);
	}
}

void ex_halbtc8822b2ant_connect_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if ((type == BTC_ASSOCIATE_5G_START) ||
	    (type == BTC_ASSOCIATE_5G_FINISH)) {
		if (type == BTC_ASSOCIATE_5G_START)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], connect_notify ---  5G start\n");
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], connect_notify ---  5G finish\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);
		return;
	}

	if (type == BTC_ASSOCIATE_START) {
		coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT START notify (2G)\n");

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_2G_RUNTIME);

		halbtc8822b2ant_action_wifi_link_process(btcoexist);

		/* To keep TDMA case during connect process,
		 * to avoid changed by Btinfo and runcoexmechanism
		 */
		coex_sta->freeze_coexrun_by_btinfo = true;

		coex_dm->arp_cnt = 0;

	} else if (type == BTC_ASSOCIATE_FINISH) {
		coex_sta->wifi_is_high_pri_task = false;
		coex_sta->freeze_coexrun_by_btinfo = false;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT FINISH notify	(2G)\n");

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
	}
}

void ex_halbtc8822b2ant_media_status_notify(struct btc_coexist *btcoexist,
					    u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_b_mode = false, wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (type == BTC_MEDIA_CONNECT) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], MEDIA connect notify\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

		if (wifi_under_5g) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], WiFi is under 5G!!!\n");

			halbtc8822b2ant_action_wifi_under5g(btcoexist);
			return;
		}

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_2G_RUNTIME);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
				   &wifi_under_b_mode);

		/* Set CCK Tx/Rx high Pri except 11b mode */
		if (wifi_under_b_mode) {
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x00); /* CCK Rx */
		} else {
			btcoexist->btc_write_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_write_1byte(btcoexist, 0x6cf,
						   0x10); /* CCK Rx */
		}

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], MEDIA disconnect notify\n");

		btcoexist->btc_write_1byte(btcoexist, 0x6cd, 0x0); /* CCK Tx */
		btcoexist->btc_write_1byte(btcoexist, 0x6cf, 0x0); /* CCK Rx */

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
	}

	halbtc8822b2ant_update_wifi_channel_info(btcoexist, type);
}

void ex_halbtc8822b2ant_specific_packet_notify(struct btc_coexist *btcoexist,
					       u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool under_4way = false, wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (wifi_under_5g) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under 5G!!!\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (under_4way) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], specific Packet ---- under_4way!!\n");

		coex_sta->wifi_is_high_pri_task = true;
		coex_sta->specific_pkt_period_cnt = 2;

	} else if (type == BTC_PACKET_ARP) {
		coex_dm->arp_cnt++;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], specific Packet ARP notify -cnt = %d\n",
			 coex_dm->arp_cnt);

	} else {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], specific Packet DHCP or EAPOL notify [Type = %d]\n",
			type);

		coex_sta->wifi_is_high_pri_task = true;
		coex_sta->specific_pkt_period_cnt = 2;
	}

	if (coex_sta->wifi_is_high_pri_task)
		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
}

void ex_halbtc8822b2ant_bt_info_notify(struct btc_coexist *btcoexist,
				       u8 *tmp_buf, u8 length)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 i, rsp_source = 0;
	bool wifi_connected = false;
	u8 media_type;

	if (psd_scan->is_ant_det_running) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt_info_notify return for AntDet is running\n");
		return;
	}

	rsp_source = tmp_buf[0] & 0xf;
	if (rsp_source >= BT_INFO_SRC_8822B_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8822B_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Bt_info[%d], len=%d, data=[", rsp_source, length);

	for (i = 0; i < length; i++) {
		coex_sta->bt_info_c2h[rsp_source][i] = tmp_buf[i];

		if (i == length - 1) {
			/* last one */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x]\n", tmp_buf[i]);
		} else {
			/* normal */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "0x%02x, ",
				 tmp_buf[i]);
		}
	}

	coex_sta->bt_info = coex_sta->bt_info_c2h[rsp_source][1];
	coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];
	coex_sta->bt_info_ext2 = coex_sta->bt_info_c2h[rsp_source][5];

	if (rsp_source != BT_INFO_SRC_8822B_2ANT_WIFI_FW) {
		/* if 0xff, it means BT is under WHCK test */
		coex_sta->bt_whck_test =
			((coex_sta->bt_info == 0xff) ? true : false);

		coex_sta->bt_create_connection =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x80) ? true :
									 false);

		/* unit: %, value-100 to translate to unit: dBm */
		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->c2h_bt_remote_name_req =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x20) ? true :
									 false);

		coex_sta->is_A2DP_3M =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x10) ? true :
									 false);

		coex_sta->acl_busy =
			((coex_sta->bt_info_c2h[rsp_source][1] & 0x9) ? true :
									false);

		coex_sta->voice_over_HOGP =
			((coex_sta->bt_info_ext & 0x10) ? true : false);

		coex_sta->c2h_bt_inquiry_page =
			((coex_sta->bt_info & BT_INFO_8822B_2ANT_B_INQ_PAGE) ?
				 true :
				 false);

		coex_sta->a2dp_bit_pool =
			(((coex_sta->bt_info_c2h[rsp_source][1] & 0x49) ==
			  0x49) ?
				 coex_sta->bt_info_c2h[rsp_source][6] :
				 0);

		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		coex_sta->is_autoslot = coex_sta->bt_info_ext2 & 0x8;

		coex_sta->forbidden_slot = coex_sta->bt_info_ext2 & 0x7;

		coex_sta->hid_busy_num = (coex_sta->bt_info_ext2 & 0x30) >> 4;

		coex_sta->hid_pair_cnt = (coex_sta->bt_info_ext2 & 0xc0) >> 6;

		if (coex_sta->bt_retry_cnt >= 1)
			coex_sta->pop_event_cnt++;

		if (coex_sta->c2h_bt_remote_name_req)
			coex_sta->cnt_remote_name_req++;

		if (coex_sta->bt_info_ext & BIT(1))
			coex_sta->cnt_reinit++;

		if (coex_sta->bt_info_ext & BIT(2)) {
			coex_sta->cnt_setup_link++;
			coex_sta->is_setup_link = true;
		} else {
			coex_sta->is_setup_link = false;
		}

		if (coex_sta->bt_info_ext & BIT(3))
			coex_sta->cnt_ign_wlan_act++;

		if (coex_sta->bt_create_connection)
			coex_sta->cnt_page++;

		/* Here we need to resend some wifi info to BT */
		/* because bt is reset and loss of the info. */

		if ((!btcoexist->manual_control) &&
		    (!btcoexist->stop_coex_dm)) {
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wifi_connected);

			/*  Re-Init */
			if ((coex_sta->bt_info_ext & BIT(1))) {
				RT_TRACE(
					rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n");
				if (wifi_connected)
					media_type = BTC_MEDIA_CONNECT;
				else
					media_type = BTC_MEDIA_DISCONNECT;

				halbtc8822b2ant_update_wifi_channel_info(
					btcoexist, media_type);
			}

			/*  If Ignore_WLanAct && not SetUp_Link */
			if ((coex_sta->bt_info_ext & BIT(3)) &&
			    (!(coex_sta->bt_info_ext & BIT(2)))) {
				RT_TRACE(
					rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
				halbtc8822b2ant_ignore_wlan_act(
					btcoexist, FORCE_EXEC, false);
			}
		}
	}

	halbtc8822b2ant_update_bt_link_info(btcoexist);

	if (btcoexist->manual_control) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), No run_coexist_mechanism for Manual CTRL\n");
		return;
	}

	if (btcoexist->stop_coex_dm) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(),  No run_coexist_mechanism for Stop Coex DM\n");
		return;
	}

	coex_sta->c2h_bt_info_req_sent = false;

	halbtc8822b2ant_run_coexist_mechanism(btcoexist);
}

void ex_halbtc8822b2ant_rf_status_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], RF Status notify\n");

	if (type == BTC_RF_ON) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RF is turned ON!!\n");

		coex_sta->wl_rf_off_on_event = true;
		btcoexist->stop_coex_dm = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, true);
	} else if (type == BTC_RF_OFF) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RF is turned OFF!!\n");

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_WLAN_OFF);

		halbtc8822b2ant_action_coex_all_off(btcoexist);

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, false);
		btcoexist->stop_coex_dm = true;
		coex_sta->wl_rf_off_on_event = false;
	}
}

void ex_halbtc8822b2ant_halt_notify(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				     BT_8822B_2ANT_PHASE_WLAN_OFF);

	ex_halbtc8822b2ant_media_status_notify(btcoexist, BTC_MEDIA_DISCONNECT);

	halbtc8822b2ant_post_state_to_bt(
		btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ONOFF, false);
}

void ex_halbtc8822b2ant_pnp_notify(struct btc_coexist *btcoexist, u8 pnp_state)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if ((pnp_state == BTC_WIFI_PNP_SLEEP) ||
	    (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to SLEEP\n");

		/* Sinda 20150819, workaround for driver skip leave IPS/LPS to
		 * speed up sleep time.
		 * Driver do not leave IPS/LPS when driver is going to sleep,
		 * so BTCoexistence think wifi is still under IPS/LPS.
		 * BT should clear UnderIPS/UnderLPS state to avoid mismatch
		 * state after wakeup.
		 */
		coex_sta->under_ips = false;
		coex_sta->under_lps = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, false);

		if (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT) {
			if (wifi_under_5g)
				halbtc8822b2ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_2ANT_PHASE_5G_RUNTIME);
			else
				halbtc8822b2ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_2ANT_PHASE_2G_RUNTIME);
		} else {
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				BT_8822B_2ANT_PHASE_WLAN_OFF);
		}
	} else if (pnp_state == BTC_WIFI_PNP_WAKE_UP) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to WAKE UP\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, true);
	}
}

void ex_halbtc8822b2ant_periodical(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_busy = false;
	u32 bt_patch_ver;
	u16 bt_scoreboard_val = 0;
	bool bt_relink_finish = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ************* Periodical *************\n");

#if (BT_AUTO_REPORT_ONLY_8822B_2ANT == 0)
	halbtc8822b2ant_query_bt_info(btcoexist);
#endif

	halbtc8822b2ant_monitor_bt_ctr(btcoexist);
	halbtc8822b2ant_monitor_wifi_ctr(btcoexist);
	halbtc8822b2ant_monitor_bt_enable_disable(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	halbtc8822b2ant_read_score_board(btcoexist, &bt_scoreboard_val);

	if (wifi_busy) {
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_UNDERTEST, true);
		/*for bt lps32 clock offset*/
		if (bt_scoreboard_val & BIT(6))
			halbtc8822b2ant_query_bt_info(btcoexist);
	} else {
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_UNDERTEST, false);
	}

	if (coex_sta->bt_relink_downcount != 0) {
		coex_sta->bt_relink_downcount--;

		if (coex_sta->bt_relink_downcount == 0)
			bt_relink_finish = true;
	}

	/* for 4-way, DHCP, EAPOL packet */
	if (coex_sta->specific_pkt_period_cnt > 0) {
		coex_sta->specific_pkt_period_cnt--;

		if ((coex_sta->specific_pkt_period_cnt == 0) &&
		    (coex_sta->wifi_is_high_pri_task))
			coex_sta->wifi_is_high_pri_task = false;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ***************** Hi-Pri Task = %s*****************\n",
			(coex_sta->wifi_is_high_pri_task ? "Yes" : "No"));
	}

	if (!coex_sta->bt_disabled) {
		if (coex_sta->bt_coex_supported_feature == 0)
			btcoexist->btc_get(
				btcoexist, BTC_GET_U4_SUPPORTED_FEATURE,
				&coex_sta->bt_coex_supported_feature);

		if ((coex_sta->bt_coex_supported_version == 0) ||
		    (coex_sta->bt_coex_supported_version == 0xffff))
			btcoexist->btc_get(
				btcoexist, BTC_GET_U4_SUPPORTED_VERSION,
				&coex_sta->bt_coex_supported_version);

		btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER,
				   &bt_patch_ver);
		btcoexist->bt_info.bt_get_fw_ver = bt_patch_ver;

		if (coex_sta->bt_reg_vendor_ac == 0xffff)
			coex_sta->bt_reg_vendor_ac = (u16)(
				btcoexist->btc_get_bt_reg(btcoexist, 3, 0xac) &
				0xffff);

		if (coex_sta->bt_reg_vendor_ae == 0xffff)
			coex_sta->bt_reg_vendor_ae = (u16)(
				btcoexist->btc_get_bt_reg(btcoexist, 3, 0xae) &
				0xffff);
	}
	if (halbtc8822b2ant_is_wifibt_status_changed(btcoexist))
		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
}

void ex_halbtc8822b2ant_antenna_detection(struct btc_coexist *btcoexist,
					  u32 cent_freq, u32 offset, u32 span,
					  u32 seconds)
{
}

void ex_halbtc8822b2ant_display_ant_detection(struct btc_coexist *btcoexist) {}
