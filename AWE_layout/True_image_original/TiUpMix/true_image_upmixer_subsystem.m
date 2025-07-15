function SYS=true_image_upmixer_subsystem(NAME, setup )
% Creates a true image upmixer sybsystem that utilizes
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('true_image_upmix', 'True Image Upmixer system');
SYS.name=NAME;

setup.MSCoorrection = 1;

% Add instances of the true image upmixer module
add_module(SYS, router_module('TI_FrontRouter', 1, 2));
add_module(SYS, router_module('TI_CenterRouter', 1, 1));
add_module(SYS, router_module('TI_SurroundRouter', 1, 2));
add_module(SYS, router_module('TI_BackRouter', 1, 2));
add_module(SYS, router_module('TI_FrontHightRouter', 1, 2));
add_module(SYS, router_module('TI_SurroundHighRouter', 1, 2));

add_module(SYS, adder_module('TI_monoSum', 1, 1));

if setup.MSCoorrection
    add_module(SYS, TI_SNoiseGate('TI_MS_Corr', setup));
end

add_module(SYS, TI_FrontUpmixer_subsystem('TI_FrontUpmixer',setup));
add_module(SYS, TI_SurroundUpmixer_subsystem('TI_SurroundUpmixer',setup));
add_module(SYS, TI_FrontHeightUpmixer_subsystem('TI_FrontHeightUpmixer',setup));
add_module(SYS, TI_LRBackUpmixer_subsystem('TI_LRBackUpmixer',setup));
add_module(SYS, TI_SurroundHeightUpmixer_subsystem('TI_SurroundHeightUpmixer',setup));

add_module(SYS, TI_SurroundControlFrontCh_subsystem('TI_SurroundControlFrontCh',setup));
add_module(SYS, TI_SurroundControlSurroundCh_subsystem('TI_SurroundControlSurroundCh',setup));
add_module(SYS, TI_HeightControl_subsystem('TI_HeightControl',setup));

add_module(SYS, router_module('TI_OutputRouter', 6, 11));
add_module(SYS, multiplexor_module('TI_BypassSwitch', 2));
add_module(SYS, TI_Downmix_subsystem('TI_DM', setup));

% Input and output pins for respective channels
    add_pin(SYS, 'input', 'in', 'Input into True Image Upmixer', new_pin_type(11,setup.BLOCKSIZE));
    add_pin(SYS,'output', 'out', 'output from True Image Upmixer', new_pin_type(11,setup.BLOCKSIZE));   
    

% Connect pins and modules

% connect monoSum
connect(SYS, '.in', 'TI_monoSum');

mname = '.in';
mnamed='DebugMeter1';
add_module(SYS,meter_module(mnamed));
SYS=connect(SYS,mname,mnamed);

% Make pair channels
connect(SYS, '.in', 'TI_FrontRouter');
connect(SYS, '.in', 'TI_CenterRouter');
connect(SYS, '.in', 'TI_SurroundRouter');
connect(SYS, '.in', 'TI_BackRouter');
connect(SYS, '.in', 'TI_FrontHightRouter');
connect(SYS, '.in', 'TI_SurroundHighRouter');


% connect front upmixer
if setup.MSCoorrection
    connect(SYS, 'TI_FrontRouter', 'TI_MS_Corr', 'TI_SurroundUpmixer.Front_in');
    connect(SYS, 'TI_MS_Corr', 'TI_FrontUpmixer.Front_in');   % LF & RF
else
    connect(SYS, 'TI_FrontRouter', 'TI_SurroundUpmixer.Front_in');
    connect(SYS, 'TI_FrontRouter', 'TI_FrontUpmixer.Front_in');   % LF & RF    
end    

connect(SYS, 'TI_CenterRouter', 'TI_FrontUpmixer.Centre_in');  % CF

% Connect surround upmixer
%connect(SYS, 'TI_SurroundRouter', 'TI_SurroundUpmixer.Surround_in');

% connect front height upmixer module
connect(SYS, 'TI_FrontUpmixer.Centre_out', 'TI_FrontHeightUpmixer.CF_in');
connect(SYS, 'TI_FrontHightRouter', 'TI_FrontHeightUpmixer.LFH_RFH_in');

% connect L/R back upmixer module
connect(SYS, 'TI_SurroundUpmixer.Surround_out', 'TI_LRBackUpmixer.Surround_in');
%connect(SYS, 'TI_BackRouter', 'TI_LRBackUpmixer.Back_in');

% connect surround height upmixer module
connect(SYS, 'TI_SurroundUpmixer.Surround_out', 'TI_SurroundHeightUpmixer.LS_RS_in');
connect(SYS, 'TI_SurroundHighRouter', 'TI_SurroundHeightUpmixer.LSH_RSH_in');

% Connect surround control - front channels
connect(SYS, 'TI_monoSum', 'TI_SurroundControlFrontCh.Mono_in');
connect(SYS, 'TI_FrontUpmixer.Front_out', 'TI_SurroundControlFrontCh.LF_RF_in');
connect(SYS, 'TI_FrontUpmixer.Centre_out', 'TI_SurroundControlFrontCh.CF_in');


% connect surround control - surround channels
connect(SYS, 'TI_SurroundUpmixer.Surround_out', 'TI_SurroundControlSurroundCh.Surround_in');
connect(SYS, 'TI_LRBackUpmixer.Back_out', 'TI_SurroundControlSurroundCh.Back_in');

% Connect height control - height channels module
connect(SYS, 'TI_FrontHeightUpmixer.LFH_RFH_out', 'TI_HeightControl.LFH_RFH_in');
connect(SYS, 'TI_SurroundHeightUpmixer.LSH_RSH_out', 'TI_HeightControl.LSH_RSH_in');

% connect downmix module
connect(SYS, 'TI_SurroundControlFrontCh.LF_RF_out', 'TI_OutputRouter.in1');
connect(SYS, 'TI_SurroundControlFrontCh.CF_out', 'TI_OutputRouter.in2');
connect(SYS, 'TI_SurroundControlSurroundCh.Surround_out', 'TI_OutputRouter.in3');
connect(SYS, 'TI_SurroundControlSurroundCh.Back_out', 'TI_OutputRouter.in4');
connect(SYS, 'TI_HeightControl.LFH_RFH_CFH_out', 'TI_OutputRouter.in5');
connect(SYS, 'TI_HeightControl.LSH_RSH_out', 'TI_OutputRouter.in6');


% connect outputs
connect(SYS, 'TI_OutputRouter', 'TI_BypassSwitch.in2');
connect(SYS, '.in', 'TI_BypassSwitch.in1');
connect(SYS, 'TI_BypassSwitch', 'TI_DM', '.out');

mname = 'TI_BypassSwitch';
mnamed='DebugMeter2';
add_module(SYS,meter_module(mnamed));
SYS=connect(SYS,mname,mnamed);

mname = 'TI_DM';
mnamed='DebugMeter3';
add_module(SYS,meter_module(mnamed));
SYS=connect(SYS,mname,mnamed);

SYS.TI_FrontRouter.channelIndex = [0; 1];
SYS.TI_CenterRouter.channelIndex = [2];
SYS.TI_SurroundRouter.channelIndex = [3; 4];
SYS.TI_BackRouter.channelIndex = [5; 6];
SYS.TI_SurroundHighRouter.channelIndex = [9; 10];
SYS.TI_FrontHightRouter.channelIndex = [7; 8];

SYS.TI_OutputRouter.channelIndex(1) = 0*2^16 + 0;     % LF
SYS.TI_OutputRouter.channelIndex(2) = 0*2^16 + 1;     % RF
SYS.TI_OutputRouter.channelIndex(3) = 1*2^16 + 0;     % CF
SYS.TI_OutputRouter.channelIndex(4) = 2*2^16 + 0;     % LS
SYS.TI_OutputRouter.channelIndex(5) = 2*2^16 + 1;     % RS
SYS.TI_OutputRouter.channelIndex(6) = 3*2^16 + 0;     % LB
SYS.TI_OutputRouter.channelIndex(7) = 3*2^16 + 1;     % RB 
SYS.TI_OutputRouter.channelIndex(8) = 4*2^16 + 0;     % LFH
SYS.TI_OutputRouter.channelIndex(9) = 4*2^16 + 1;     % RFH
SYS.TI_OutputRouter.channelIndex(10) = 5*2^16 + 0;    % LBH
SYS.TI_OutputRouter.channelIndex(11) = 5*2^16 + 1;    % RBH

SYS.TI_BypassSwitch.index = 0; % make bypass default

add_module(SYS, dc_source_v2_module('StageWithSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.StageWithSource.value = 0;
add_module(SYS, dc_source_v2_module('EnvelopmentSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.EnvelopmentSource.value = 0;

add_module(SYS,param_set_module('StageWithSourceFrontUpSet', 'float', 'TI_FrontUpmixer.StageWithSource.value'));
add_module(SYS,param_set_module('StageWithSourceFrontHightUpSet', 'float', 'TI_FrontHeightUpmixer.StageWithSource.value'));
add_module(SYS,param_set_module('EnvelopmentSourceBackUpSet', 'float', 'TI_LRBackUpmixer.EnvelopmentSource.value'));
add_module(SYS,param_set_module('EnvelopmentSourceSurroundUpSet', 'float', 'TI_SurroundUpmixer.EnvelopmentSource.value'));

connect(SYS,'StageWithSource', 'StageWithSourceFrontUpSet');
connect(SYS,'StageWithSource', 'StageWithSourceFrontHightUpSet');
connect(SYS,'EnvelopmentSource', 'EnvelopmentSourceBackUpSet');
connect(SYS,'EnvelopmentSource', 'EnvelopmentSourceSurroundUpSet');

add_module(SYS, dc_source_v2_module('SurroundControllerSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.SurroundControllerSource.value = 0;

add_module(SYS,param_set_module('SurroundControlFrontCh', 'float', 'TI_SurroundControlFrontCh.SurroundControllerSource.value'));
add_module(SYS,param_set_module('SurroundControlSurroundChSet', 'float', 'TI_SurroundControlSurroundCh.SurroundControllerSource.value'));

connect(SYS, 'SurroundControllerSource', 'SurroundControlFrontCh');
connect(SYS, 'SurroundControllerSource', 'SurroundControlSurroundChSet');

add_module(SYS, dc_source_int_module('SpatialProcessingSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.SpatialProcessingSource.value = 0;

add_module(SYS,param_set_module('SpatialProcessingSetTI','int','TI_BypassSwitch.index'));

add_module(SYS,param_set_module('SpatialProcessingSetTIDM','int','TI_DM.TI_DM_enable.index'));
add_module(SYS, logic_any_module('TiOrDm', 1));
add_module(SYS, logic_compare_const_int_module('TiTrue'));
SYS.TiTrue.compareType = 0;
SYS.TiTrue.constValue = 1;

add_module(SYS, dc_source_int_module('UpmixProcessingEnable',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.UpmixProcessingEnable.value = 0;
add_module(SYS, dc_source_int_module('DownmixProcessingEnable',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.DownmixProcessingEnable.value = 0;
add_module(SYS, multiplexor_module('Upmixer_debug_on', 2));
SYS.Upmixer_debug_on.index = 0;
add_module(SYS, multiplexor_module('Downmixer_debug_on', 2));
SYS.Downmixer_debug_on.index = 0;

connect(SYS,'SpatialProcessingSource', 'TiTrue', 'Upmixer_debug_on.in1');
connect(SYS,'UpmixProcessingEnable', 'Upmixer_debug_on.in2');
connect(SYS,'Upmixer_debug_on', 'SpatialProcessingSetTI');

connect(SYS,'SpatialProcessingSource', 'TiOrDm' , 'Downmixer_debug_on.in1');
connect(SYS,'DownmixProcessingEnable' , 'Downmixer_debug_on.in2');
connect(SYS,'Downmixer_debug_on', 'SpatialProcessingSetTIDM');

add_module(SYS, dc_source_int_module('BackChannelsPresent',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.BackChannelsPresent.value = 0;
add_module(SYS, logic_compare_const_int_module('BackChannelsPresent_inv'));
connect(SYS,'BackChannelsPresent','BackChannelsPresent_inv');
add_module(SYS,interleave_module('TIUpmixON_AND_BackChannelsNotPresent_interleave',2));
connect(SYS, 'Upmixer_debug_on', 'TIUpmixON_AND_BackChannelsNotPresent_interleave.in1');
connect(SYS, 'BackChannelsPresent_inv', 'TIUpmixON_AND_BackChannelsNotPresent_interleave.in2');
add_module(SYS,logic_all_module('TIUpmixON_AND_BackChannelsNotPresent',1));
connect(SYS,'TIUpmixON_AND_BackChannelsNotPresent_interleave','TIUpmixON_AND_BackChannelsNotPresent');

add_module(SYS, adder_module('SurroundAndBackAdder', 2, 0));
connect(SYS, 'TI_SurroundRouter', 'SurroundAndBackAdder.in1');
connect(SYS, 'TI_BackRouter', 'SurroundAndBackAdder.in2');
add_module(SYS, multiplexor_module('Surround_SurroundPlusBack_mux', 2));
add_module(SYS, multiplexor_module('Back_SurroundPlusBack_mux', 2));
connect(SYS, 'TI_SurroundRouter', 'Surround_SurroundPlusBack_mux.in1');
connect(SYS, 'SurroundAndBackAdder', 'Surround_SurroundPlusBack_mux.in2');
connect(SYS, 'TI_BackRouter', 'Back_SurroundPlusBack_mux.in1');
connect(SYS, 'SurroundAndBackAdder', 'Back_SurroundPlusBack_mux.in2');

SYS=add_module(SYS, param_set_module('Surround_SurroundPlusBack_mux_set', 'int', 'Surround_SurroundPlusBack_mux.index'));
SYS=add_module(SYS, param_set_module('Back_SurroundPlusBack_mux_set', 'int', 'Back_SurroundPlusBack_mux.index'));
connect(SYS,'TIUpmixON_AND_BackChannelsNotPresent','Surround_SurroundPlusBack_mux_set');
connect(SYS,'TIUpmixON_AND_BackChannelsNotPresent','Back_SurroundPlusBack_mux_set');
connect(SYS,'Surround_SurroundPlusBack_mux','TI_SurroundUpmixer.Surround_in');
connect(SYS, 'Back_SurroundPlusBack_mux', 'TI_LRBackUpmixer.Back_in');

