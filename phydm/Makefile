ccflags-y += -I$(src)/

ccflags-y += -DDM_ODM_CE_MAC80211
ccflags-y += -DDM_ODM_SUPPORT_TYPE=0x04
ccflags-y += -DDBG=1
ccflags-y += -DMP_DRIVER=0
ccflags-y += -DDISABLE_BB_RF=0
# support list
ccflags-y += -DRTL8881A_SUPPORT=0
ccflags-y += -DRTL8188E_SUPPORT=0
ccflags-y += -DRTL8812A_SUPPORT=0
ccflags-y += -DRTL8821A_SUPPORT=0
ccflags-y += -DRTL8723B_SUPPORT=0
ccflags-y += -DRTL8723D_SUPPORT=0
ccflags-y += -DRTL8192E_SUPPORT=0
ccflags-y += -DRTL8814A_SUPPORT=0
ccflags-y += -DRTL8195A_SUPPORT=0
ccflags-y += -DRTL8197F_SUPPORT=0
ccflags-y += -DRTL8703B_SUPPORT=0
ccflags-y += -DRTL8188F_SUPPORT=0
ccflags-y += -DRTL8822B_SUPPORT=1
ccflags-y += -DRTL8821B_SUPPORT=0
ccflags-y += -DRTL8821C_SUPPORT=0
# bt
ccflags-y += -DCONFIG_BT_COEXIST=1
ccflags-y += -DBT_SUPPORT=1

phydm_mod-objs := \
		phydm_debug.o	\
		phydm_antdiv.o\
		phydm_interface.o\
		phydm_hwconfig.o\
		phydm.o\
		halphyrf_ce.o\
		phydm_edcaturbocheck.o\
		phydm_dig.o\
		phydm_rainfo.o\
		phydm_dynamicbbpowersaving.o\
		phydm_powertracking_ce.o\
		phydm_dynamictxpower.o\
		phydm_adaptivity.o\
		phydm_cfotracking.o\
		phydm_noisemonitor.o\
		phydm_acs.o\
		phydm_psd.o\
		phydm_adc_sampling.o\
		phydm_kfree.o\
		phydm_ccx.o

# Unused
#phydm_mod-objs +\
		phydm_beamforming.o\
		phydm_antdect.o\
		phydm_pathdiv.o\
		phydm_dynamic_rx_path.o\
		phydm_dfs.o\

#phydm_mod-objs += \
		txbf/halcomtxbf.o\
		txbf/haltxbfinterface.o\
		txbf/phydm_hal_txbf_api.o\

phydm_mod-objs += \
		rtl8822b/halhwimg8822b_bb.o\
		rtl8822b/halhwimg8822b_mac.o\
		rtl8822b/halhwimg8822b_rf.o\
		rtl8822b/halphyrf_8822b.o\
		rtl8822b/phydm_hal_api8822b.o\
		rtl8822b/phydm_iqk_8822b.o\
		rtl8822b/phydm_regconfig8822b.o\
		rtl8822b/phydm_rtl8822b.o

#phydm_mod-objs += \
		txbf/haltxbf8822b.o

phydm_mod-objs += \
		rtl_phydm.o

obj-m = phydm_mod.o
