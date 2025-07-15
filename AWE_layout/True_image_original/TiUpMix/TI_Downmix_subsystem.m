function SYS=TI_Downmix_subsystem(NAME, setup);
% Creates a True image Downmix subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI DM', 'True image dowmmix');
SYS.name=NAME;


%% Add instances of the true image upmixer subsystem
add_module(SYS, TI_universal_router_module('TI_DM_InputRouter',setup.BLOCKSIZE));
add_module(SYS, scalern_module('TI_DM_FrontHeight2Front_Scaler', 2));
add_module(SYS, scalern_module('TI_DM_SurroundHeight2Surround_Scaler', 2));

add_module(SYS, adder_module('TI_DM_SurroundAndBackAndFrontHeigth2Front_adder', 3, 0));
add_module(SYS, adder_module('TI_DM_SurroundHeight2Surround_adder', 2, 0));


add_module(SYS, adder_module('TI_DM_Back2Surround_adder', 2, 0));
add_module(SYS, scaler_module('TI_DM_Back2Surround_scaler'));

add_module(SYS,scalern_v2_module('TI_DM_SurroundAndBack_scaler', 2));
SYS.TI_DM_SurroundAndBack_scaler.isDB = 0;
SYS.TI_DM_SurroundAndBack_scaler.masterGain = 1;

add_module(SYS, scaler_module('TI_DM_Front2Centre_scaler'));
add_module(SYS, adder_module('TI_DM_Front2Center_adder', 2, 1));

add_module(SYS, scaler_module('TI_DM_Centre2Front_scaler'));
add_module(SYS, TI_Add1pinTo2channels_module('TI_DM_CentreFront2Front_adder', setup.BLOCKSIZE));

add_module(SYS, router_module('TI_DM_OutputRouter', 6, 11));


%% Input and output pins for respective channels
add_pin(SYS, 'input', 'in', 'Downmixer input', new_pin_type(11,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'out', 'Downmixer output', new_pin_type(16,setup.BLOCKSIZE));


%% Connect pins and modules
connect(SYS, '.in', 'TI_DM_InputRouter');
connect(SYS, 'TI_DM_InputRouter.out1', 'TI_DM_Front2Center_adder.in1');
connect(SYS, 'TI_DM_InputRouter.out1', 'TI_DM_Centre2Front_scaler');
connect(SYS, 'TI_DM_InputRouter.out2', 'TI_DM_SurroundAndBackAndFrontHeigth2Front_adder.in1');
connect(SYS, 'TI_DM_InputRouter.out3', 'TI_DM_SurroundHeight2Surround_adder.in1');
connect(SYS, 'TI_DM_InputRouter.out5', 'TI_DM_FrontHeight2Front_Scaler');
connect(SYS, 'TI_DM_InputRouter.out6', 'TI_DM_SurroundHeight2Surround_Scaler');

connect(SYS, 'TI_DM_SurroundHeight2Surround_Scaler', 'TI_DM_SurroundHeight2Surround_adder.in2');

connect(SYS, 'TI_DM_Back2Surround_adder', 'TI_DM_SurroundAndBack_scaler', 'TI_DM_SurroundAndBackAndFrontHeigth2Front_adder.in2');

connect(SYS, 'TI_DM_FrontHeight2Front_Scaler', 'TI_DM_SurroundAndBackAndFrontHeigth2Front_adder.in3');

connect(SYS, 'TI_DM_SurroundAndBackAndFrontHeigth2Front_adder', 'TI_DM_Front2Centre_scaler');

connect(SYS, 'TI_DM_Front2Centre_scaler', 'TI_DM_Front2Center_adder.in2');

connect(SYS, 'TI_DM_Centre2Front_scaler', 'TI_DM_CentreFront2Front_adder.in_2');
connect(SYS, 'TI_DM_SurroundAndBackAndFrontHeigth2Front_adder', 'TI_DM_CentreFront2Front_adder.in_1');

connect(SYS, 'TI_DM_SurroundHeight2Surround_adder', 'TI_DM_Back2Surround_adder.in1');
connect(SYS, 'TI_DM_InputRouter.out4','TI_DM_Back2Surround_scaler','TI_DM_Back2Surround_adder.in2');


SYS.TI_DM_Centre2Front_scaler.gain = 0;
SYS.TI_DM_SurroundHeight2Surround_Scaler.gain = [0; 0];
SYS.TI_DM_FrontHeight2Front_Scaler.gain = [0; 0];
SYS.TI_DM_Front2Centre_scaler.gain = 0;
SYS.TI_DM_SurroundAndBack_scaler.trimGain = zeros(2,1);

SYS=add_module(SYS,dc_source_int_module('CenterChannelsPresent', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS=add_module(SYS,dc_source_int_module('SurroundChannelsPresent', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS=add_module(SYS,dc_source_int_module('BackChannelsPresent', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS=add_module(SYS,dc_source_int_module('FrontHeigthChannelsPresent', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS=add_module(SYS,dc_source_int_module('SurroundHeigthChannelsPresent', 1, 1, setup.FS/setup.BLOCKSIZE));

SYS=add_module(SYS, interleave_module('SurroundOrBackInterleave',2));
SYS=add_module(SYS, logic_any_module('SurroundOrBack',1));
connect(SYS,'SurroundChannelsPresent','SurroundOrBackInterleave.in1');
connect(SYS,'BackChannelsPresent','SurroundOrBackInterleave.in2');
connect(SYS,'SurroundOrBackInterleave','SurroundOrBack');

add_module(SYS, boolean_source_module('OutputChannelMask',12, 1, setup.FS/setup.BLOCKSIZE));
add_module(SYS, deinterleave_module('OutputChannelMaskDeinterleave',12));
connect(SYS,'OutputChannelMask', 'OutputChannelMaskDeinterleave');

add_module(SYS, type_conversion_module('OutputChannelMaskConversion',0));
add_module(SYS, router_module('OutputChannelMaskRouter',1,11));
connect(SYS,'OutputChannelMask','OutputChannelMaskConversion','OutputChannelMaskRouter');
SYS.OutputChannelMaskRouter.channelIndex = [0; 1; 2; 4; 5; 6; 7; 8; 9; 10; 11];

add_module(SYS, logic_compare_const_int_module('Lfh_present_inv'));
connect(SYS,'OutputChannelMaskDeinterleave.out9','Lfh_present_inv');
add_module(SYS,interleave_module('Lfh_not_present_AND_FrontHeigthChannelsPresent_interleave',2));
connect(SYS,'FrontHeigthChannelsPresent','Lfh_not_present_AND_FrontHeigthChannelsPresent_interleave.in1');
connect(SYS,'Lfh_present_inv','Lfh_not_present_AND_FrontHeigthChannelsPresent_interleave.in2');
add_module(SYS,logic_all_module('Lfh_not_present_AND_FrontHeigthChannelsPresent',1));
add_module(SYS, type_conversion_module('Lfh_not_present_AND_FrontHeigthChannelsPresent_conv', 0));
add_module(SYS, param_set_module('TI_DM_FrontHeight2Front_Scaler_Set1', 'float', 'TI_DM_FrontHeight2Front_Scaler.gain[0]'));
connect(SYS,'Lfh_not_present_AND_FrontHeigthChannelsPresent_interleave','Lfh_not_present_AND_FrontHeigthChannelsPresent','Lfh_not_present_AND_FrontHeigthChannelsPresent_conv','TI_DM_FrontHeight2Front_Scaler_Set1');

add_module(SYS, logic_compare_const_int_module('Rfh_present_inv'));
connect(SYS,'OutputChannelMaskDeinterleave.out10','Rfh_present_inv');
add_module(SYS,interleave_module('Rfh_not_present_AND_FrontHeigthChannelsPresent_interleave',2));
connect(SYS,'FrontHeigthChannelsPresent','Rfh_not_present_AND_FrontHeigthChannelsPresent_interleave.in1');
connect(SYS,'Rfh_present_inv','Rfh_not_present_AND_FrontHeigthChannelsPresent_interleave.in2');
add_module(SYS,logic_all_module('Rfh_not_present_AND_FrontHeigthChannelsPresent',1));
add_module(SYS, type_conversion_module('Rfh_not_present_AND_FrontHeigthChannelsPresent_conv', 0));
add_module(SYS, param_set_module('TI_DM_FrontHeight2Front_Scaler_Set2', 'float', 'TI_DM_FrontHeight2Front_Scaler.gain[1]'));
connect(SYS,'Rfh_not_present_AND_FrontHeigthChannelsPresent_interleave','Rfh_not_present_AND_FrontHeigthChannelsPresent', 'Rfh_not_present_AND_FrontHeigthChannelsPresent_conv','TI_DM_FrontHeight2Front_Scaler_Set2');

add_module(SYS, logic_compare_const_int_module('Lsh_present_inv'));
connect(SYS,'OutputChannelMaskDeinterleave.out11','Lsh_present_inv');
add_module(SYS,interleave_module('Lsh_not_present_AND_SurroundHeigthChannelsPresent_interleave',2));
connect(SYS,'SurroundHeigthChannelsPresent','Lsh_not_present_AND_SurroundHeigthChannelsPresent_interleave.in1');
connect(SYS,'Lsh_present_inv','Lsh_not_present_AND_SurroundHeigthChannelsPresent_interleave.in2');
add_module(SYS,logic_all_module('Lsh_not_present_AND_SurroundHeigthChannelsPresent',1));
add_module(SYS, type_conversion_module('Lsh_not_present_AND_SurroundHeigthChannelsPresent_conv', 0));
add_module(SYS, param_set_module('TI_DM_SurroundHeight2Surround_Scaler_Set1', 'float', 'TI_DM_SurroundHeight2Surround_Scaler.gain[0]'));
connect(SYS,'Lsh_not_present_AND_SurroundHeigthChannelsPresent_interleave', 'Lsh_not_present_AND_SurroundHeigthChannelsPresent','Lsh_not_present_AND_SurroundHeigthChannelsPresent_conv','TI_DM_SurroundHeight2Surround_Scaler_Set1');

add_module(SYS, logic_compare_const_int_module('Rsh_present_inv'));
connect(SYS,'OutputChannelMaskDeinterleave.out12','Rsh_present_inv');
add_module(SYS,interleave_module('Rsh_not_present_AND_SurroundHeigthChannelsPresent_interleave',2));
connect(SYS,'SurroundHeigthChannelsPresent','Rsh_not_present_AND_SurroundHeigthChannelsPresent_interleave.in1');
connect(SYS,'Rsh_present_inv','Rsh_not_present_AND_SurroundHeigthChannelsPresent_interleave.in2');
add_module(SYS,logic_all_module('Rsh_not_present_AND_SurroundHeigthChannelsPresent',1));
add_module(SYS, param_set_module('TI_DM_SurroundHeight2Surround_Scaler_Set2', 'float', 'TI_DM_SurroundHeight2Surround_Scaler.gain[1]'));
add_module(SYS, type_conversion_module('Rsh_not_present_AND_SurroundHeigthChannelsPresent_conv', 0));
connect(SYS,'Rsh_not_present_AND_SurroundHeigthChannelsPresent_interleave', 'Rsh_not_present_AND_SurroundHeigthChannelsPresent','Rsh_not_present_AND_SurroundHeigthChannelsPresent_conv','TI_DM_SurroundHeight2Surround_Scaler_Set2');

add_module(SYS, interleave_module('LsRsLbRb',4));
connect(SYS,'OutputChannelMaskDeinterleave.out5', 'LsRsLbRb.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out6', 'LsRsLbRb.in2');
connect(SYS,'OutputChannelMaskDeinterleave.out7', 'LsRsLbRb.in3');
connect(SYS,'OutputChannelMaskDeinterleave.out8', 'LsRsLbRb.in4');
add_module(SYS, logic_compare_const_int_module('LsRsLbRb_inv'));
add_module(SYS,logic_any_module('LsRsLbRb_not_present', 1));
connect(SYS, 'LsRsLbRb', 'LsRsLbRb_not_present', 'LsRsLbRb_inv');
add_module(SYS,interleave_module('LsRsLbRb_not_present_AND_LsRsLbRb_interleave',2));
connect(SYS,'SurroundOrBack','LsRsLbRb_not_present_AND_LsRsLbRb_interleave.in1');
connect(SYS,'LsRsLbRb_inv','LsRsLbRb_not_present_AND_LsRsLbRb_interleave.in2');
add_module(SYS,logic_all_module('LsRsLbRb_not_present_AND_LsRsLbRb',1));
add_module(SYS, type_conversion_module('LsRsLbRb_not_present_AND_LsRsLbRb_conv', 0));
add_module(SYS, scaler_v2_module('LsRsLbRb_not_present_AND_LsRsLbRb_scale'));
SYS.LsRsLbRb_not_present_AND_LsRsLbRb_scale.isDB = 0;
SYS.LsRsLbRb_not_present_AND_LsRsLbRb_scale.gain = 0.707;
connect(SYS, 'LsRsLbRb_not_present_AND_LsRsLbRb_interleave', 'LsRsLbRb_not_present_AND_LsRsLbRb', 'LsRsLbRb_not_present_AND_LsRsLbRb_conv','LsRsLbRb_not_present_AND_LsRsLbRb_scale');
add_module(SYS, param_set_module('TI_DM_SurroundAndBack_scaler_set0', 'float', 'TI_DM_SurroundAndBack_scaler.trimGain[0]'));
add_module(SYS, param_set_module('TI_DM_SurroundAndBack_scaler_set1', 'float', 'TI_DM_SurroundAndBack_scaler.trimGain[1]'));
connect(SYS, 'LsRsLbRb_not_present_AND_LsRsLbRb_scale', 'TI_DM_SurroundAndBack_scaler_set0');
connect(SYS, 'LsRsLbRb_not_present_AND_LsRsLbRb_scale', 'TI_DM_SurroundAndBack_scaler_set1');

add_module(SYS, interleave_module('LfRf',2));
connect(SYS,'OutputChannelMaskDeinterleave.out1', 'LfRf.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out2', 'LfRf.in2');
add_module(SYS, logic_compare_const_int_module('LfRf_inv'));
add_module(SYS,logic_any_module('LfRf_not_present', 1));
add_module(SYS, type_conversion_module('LfRf_not_present_conv', 0));
add_module(SYS, scaler_v2_module('LfRf_not_present_scale'));
SYS.LfRf_not_present_scale.isDB = 0;
SYS.LfRf_not_present_scale.gain = 0.707;
add_module(SYS, param_set_module('LfRf_not_present_set', 'float', 'TI_DM_Front2Centre_scaler.gain'));
connect(SYS, 'LfRf','LfRf_not_present', 'LfRf_inv', 'LfRf_not_present_conv','LfRf_not_present_scale','LfRf_not_present_set');

add_module(SYS, logic_compare_const_int_module('CenterChannelPresent_inv'));
connect(SYS,'CenterChannelsPresent', 'CenterChannelPresent_inv');
add_module(SYS, interleave_module('Cf_OR_CenterChannelPresent_interleave',2));
connect(SYS,'CenterChannelPresent_inv', 'Cf_OR_CenterChannelPresent_interleave.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out3', 'Cf_OR_CenterChannelPresent_interleave.in2');
add_module(SYS,logic_any_module('Cf_OR_CenterChannelPresent', 1));
connect(SYS,'Cf_OR_CenterChannelPresent_interleave','Cf_OR_CenterChannelPresent');
add_module(SYS, logic_compare_const_int_module('Cf_OR_CenterChannelPresent_inv'));
add_module(SYS, type_conversion_module('Cf_OR_CenterChannelPresent_conv', 0));
add_module(SYS, scaler_v2_module('Cf_OR_CenterChannelPresent_scale'));
SYS.Cf_OR_CenterChannelPresent_scale.isDB = 0;
SYS.Cf_OR_CenterChannelPresent_scale.gain = 0.707;
add_module(SYS, param_set_module('Cf_OR_CenterChannelPresent_Set', 'float', 'TI_DM_Centre2Front_scaler.gain'));
connect(SYS, 'Cf_OR_CenterChannelPresent', 'Cf_OR_CenterChannelPresent_inv', 'Cf_OR_CenterChannelPresent_conv','Cf_OR_CenterChannelPresent_scale','Cf_OR_CenterChannelPresent_Set');


add_module(SYS,multiplexor_module('SurroundMux',2,1));
add_module(SYS,multiplexor_module('BackMux',2,1));

connect(SYS, 'TI_DM_Front2Center_adder', 'TI_DM_OutputRouter.in1');
connect(SYS, 'TI_DM_CentreFront2Front_adder', 'TI_DM_OutputRouter.in2');

connect(SYS, 'TI_DM_SurroundHeight2Surround_adder', 'SurroundMux.in1');
connect(SYS,'TI_DM_Back2Surround_adder', 'SurroundMux.in2');
connect(SYS, 'SurroundMux' ,'TI_DM_OutputRouter.in3');

connect(SYS, 'TI_DM_InputRouter.out4', 'BackMux.in1');
connect(SYS, 'TI_DM_Back2Surround_adder', 'BackMux.in2');
connect(SYS, 'BackMux', 'TI_DM_OutputRouter.in4');

add_module(SYS,multiplexor_module('FrontHeigthMux',2,1));
add_module(SYS,multiplexor_module('SurroundHeigthMux',2,1));
add_module(SYS, adder_module('HeigthAdder',2));

connect(SYS, 'TI_DM_InputRouter.out5', 'HeigthAdder.in1');
connect(SYS, 'TI_DM_InputRouter.out6', 'HeigthAdder.in2');

connect(SYS, 'TI_DM_InputRouter.out5', 'FrontHeigthMux.in1');
connect(SYS, 'HeigthAdder', 'FrontHeigthMux.in2');

connect(SYS, 'TI_DM_InputRouter.out6', 'SurroundHeigthMux.in1');
connect(SYS, 'HeigthAdder', 'SurroundHeigthMux.in2');

connect(SYS, 'FrontHeigthMux', 'TI_DM_OutputRouter.in5');
connect(SYS, 'SurroundHeigthMux', 'TI_DM_OutputRouter.in6');



SYS.TI_DM_OutputRouter.channelIndex = [ 2^16 ; 2^16+1; 0 ; 2*2^16 ; 2*2^16+1; 3*2^16 ; 3*2^16+1; 4*2^16 ; 4*2^16+1;  5*2^16 ; 5*2^16+1];

add_module(SYS, interleave_module('LfhRfh',2));
connect(SYS,'OutputChannelMaskDeinterleave.out9', 'LfhRfh.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out10', 'LfhRfh.in2');
add_module(SYS, interleave_module('LshRsh',2));
connect(SYS,'OutputChannelMaskDeinterleave.out11', 'LshRsh.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out12', 'LshRsh.in2');
add_module(SYS, interleave_module('LsRs',2));
connect(SYS,'OutputChannelMaskDeinterleave.out5', 'LsRs.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out6', 'LsRs.in2');
add_module(SYS, interleave_module('LbRb',2));
connect(SYS,'OutputChannelMaskDeinterleave.out7', 'LbRb.in1');
connect(SYS,'OutputChannelMaskDeinterleave.out8', 'LbRb.in2');

add_module(SYS,logic_any_module('LfhRfh_present', 1));
add_module(SYS,logic_any_module('LshRsh_present', 1));
add_module(SYS,logic_any_module('LsRs_present', 1));
add_module(SYS,logic_any_module('LbRb_present', 1));
connect(SYS, 'LfhRfh', 'LfhRfh_present');
connect(SYS, 'LshRsh', 'LshRsh_present');
connect(SYS, 'LsRs', 'LsRs_present');
connect(SYS, 'LbRb', 'LbRb_present');
add_module(SYS, interleave_module('LfhRfh_present_LshRsh_present',2));
add_module(SYS, interleave_module('LsRs_present_LbRb_present',2));
connect(SYS, 'LfhRfh_present', 'LfhRfh_present_LshRsh_present.in1');
connect(SYS, 'LshRsh_present', 'LfhRfh_present_LshRsh_present.in2');
connect(SYS, 'LsRs_present', 'LsRs_present_LbRb_present.in1');
connect(SYS, 'LbRb_present', 'LsRs_present_LbRb_present.in2');
add_module(SYS,logic_all_module('LfhRfhAndLshRsh', 1));
add_module(SYS,logic_all_module('LsRsAndLbRb', 1));
add_module(SYS, logic_compare_const_int_module('LfhRfhAndLshRsh_inv'));
add_module(SYS, logic_compare_const_int_module('LsRsAndLbRb_inv'));
connect(SYS,'LfhRfh_present_LshRsh_present', 'LfhRfhAndLshRsh', 'LfhRfhAndLshRsh_inv');
connect(SYS, 'LsRs_present_LbRb_present', 'LsRsAndLbRb', 'LsRsAndLbRb_inv');

connect(SYS, 'LfhRfhAndLshRsh_inv', 'FrontHeigthMux.in0');
connect(SYS, 'LfhRfhAndLshRsh_inv', 'SurroundHeigthMux.in0');

connect(SYS, 'LsRsAndLbRb_inv', 'BackMux.in0');
connect(SYS, 'LsRsAndLbRb_inv', 'SurroundMux.in0');

add_module(SYS, multiplexor_module('TI_DM_enable',2));

add_module(SYS, scalern_control_module('OutputChannelMaskGate',11));
connect(SYS, 'OutputChannelMaskRouter','OutputChannelMaskGate.g');

connect(SYS, '.in', 'TI_DM_enable.in1');
connect(SYS, 'TI_DM_OutputRouter', 'OutputChannelMaskGate.in');
connect(SYS, 'OutputChannelMaskGate', 'TI_DM_enable.in2');
connect(SYS, 'TI_DM_enable', '.out');

add_module(SYS, sink_int_module('LFEpresentSink'));
connect(SYS,'OutputChannelMaskDeinterleave.out4', 'LFEpresentSink'); 

add_module(SYS, type_conversion_module('TI_DM_Back2Surround_scaler_conv', 0));
add_module(SYS, param_set_module('TI_DM_Back2Surround_scaler_Set', 'float', 'TI_DM_Back2Surround_scaler.gain'));
connect(SYS, 'BackChannelsPresent', 'TI_DM_Back2Surround_scaler_conv', 'TI_DM_Back2Surround_scaler_Set');
