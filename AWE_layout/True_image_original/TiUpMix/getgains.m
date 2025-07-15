disp('Front----------------------------------------------------------------')
SYS.TiSubSys.TI_FrontUpmixer.StageWithSource.value
SYS.TiSubSys.TI_FrontUpmixer.TI_FU_3ch_mixer.gain
SYS.TiSubSys.TI_FrontUpmixer.TI_FU_2ch_scale1
SYS.TiSubSys.TI_FrontUpmixer.TI_FU_1ch_scale2


disp('Surround-------------------------------------------------------------')
SYS.TiSubSys.TI_SurroundUpmixer.EnvelopmentSource.value
SYS.TiSubSys.TI_SurroundUpmixer.LsRsUpmixScale.gain
SYS.TiSubSys.TI_SurroundUpmixer.TI_SU_envelopment_lw_filter.freq
SYS.TiSubSys.TI_SurroundUpmixer.TI_SU_envelopment_rw_filter.freq
SYS.TiSubSys.TI_SurroundUpmixer.TI_SU_envelopment_mixer.gain

disp('Back-------------------------------------------------------------')
SYS.TiSubSys.TI_LRBackUpmixer.EnvelopmentSource.value
SYS.TiSubSys.TI_LRBackUpmixer.LbRbUpmixScale.gain
SYS.TiSubSys.TI_LRBackUpmixer.TI_LRBU_envelopment_lb_filter.freq
SYS.TiSubSys.TI_LRBackUpmixer.TI_LRBU_envelopment_rb_filter.freq
SYS.TiSubSys.TI_LRBackUpmixer.TI_LRBU_back_mixer.gain

disp('Front Height-------------------------------------------------------------')
SYS.TiSubSys.TI_FrontHeightUpmixer.StageWithSource.value
SYS.TiSubSys.TI_FrontHeightUpmixer.TI_FHU_stagewidth_lfh_filter.freq
SYS.TiSubSys.TI_FrontHeightUpmixer.TI_FHU_stagewidth_rfh_filter.freq


disp('SurroundControlSurround-----------------------------------------------')
SYS.TiSubSys.TI_SurroundControlSurroundCh.SurroundControllerSource.value
SYS.TiSubSys.TI_SurroundControlSurroundCh.TI_surround_control_surround_gain_1.gain
SYS.TiSubSys.TI_SurroundControlSurroundCh.TI_surround_control_surround_gain_2.gain

disp('SurroundControlFront-----------------------------------------------')
SYS.TiSubSys.TI_SurroundControlFrontCh.SurroundControllerSource.value
SYS.TiSubSys.TI_SurroundControlFrontCh.TI_surround_control_front_gain_1.gain
SYS.TiSubSys.TI_SurroundControlFrontCh.TI_surround_control_front_gain_2.gain
SYS.TiSubSys.TI_SurroundControlFrontCh.TI_surround_control_front_gain_3.gain

disp('HeigthControl-------------------------------------------------------')
SYS.TiSubSys.TI_HeightControl.HeigthControllerSource.value
SYS.TiSubSys.TI_HeightControl.TI_HeightCtrl_gain_1.gain


disp('Downmix FrontHeight2Front-----------------------------------------------------------')
SYS.TiSubSys.TI_DM.TI_DM_FrontHeight2Front_Scaler.gain
disp('Downmix SurroundHeight2Surround-----------------------------------------------------')
SYS.TiSubSys.TI_DM.TI_DM_SurroundHeight2Surround_Scaler.gain
disp('Downmix BackandSurround2Front-------------------------------------------------------')
SYS.TiSubSys.TI_DM.TI_DM_SurroundAndBack_scaler.trimGain
disp('Downmix Center2Front----------------------------------------------------------------')
SYS.TiSubSys.TI_DM.TI_DM_Centre2Front_scaler.gain
disp('Downmix Front2Center----------------------------------------------------------------')
SYS.TiSubSys.TI_DM.TI_DM_Front2Centre_scaler.gain
disp('Downmix BackSurround switches--------------------------------------------------------')
SYS.TiSubSys.TI_DM.BackMux.index
SYS.TiSubSys.TI_DM.SurroundMux.index
disp('Downmix Heigth switches switches------------------------------------------------------')
SYS.TiSubSys.TI_DM.FrontHeigthMux.index
SYS.TiSubSys.TI_DM.SurroundHeigthMux.index

