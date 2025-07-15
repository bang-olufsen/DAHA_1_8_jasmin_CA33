function SYS=TI_FrontHeightUpmixer_subsystem(NAME, setup);
% Creates a True image front height upmixer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI FHU', 'True image front height upmixer');
SYS.name=NAME;


%% Add instances of the true image upmixer subsystem
% add modules for front input
add_module(SYS, biquad_cascade_module('TI_FHU_FH_filter_gain',2));
sos1=biquad(250,0,0.7,2,setup.FS);
[B, A]=biquad(5000,0,0.9,1,setup.FS);
sos2=[0.71*B A];
SYS.TI_FHU_FH_filter_gain.coeffs = [sos2aw(sos1) sos2aw(sos2)];

add_module(SYS, second_order_filter_cascade_module('TI_FHU_stagewidth_lfh_filter',1,1));
SYS.TI_FHU_stagewidth_lfh_filter.filterType = 6;
SYS.TI_FHU_stagewidth_lfh_filter.freq = 800;
add_module(SYS, second_order_filter_cascade_module('TI_FHU_stagewidth_rfh_filter',1,1));
SYS.TI_FHU_stagewidth_rfh_filter.filterType = 6;
SYS.TI_FHU_stagewidth_rfh_filter.freq = 800;

add_module(SYS, interleave_module('TI_FHU_IL', 2));
add_module(SYS, multiplexor_module('TI_FHU_channel_switch1', 2));
SYS.TI_FHU_channel_switch1.index = 1;

%% Input and output pins for respective channels
add_pin(SYS,'input', 'CF_in', 'Centre Front channel input', new_pin_type(1,setup.BLOCKSIZE));
add_pin(SYS,'input', 'LFH_RFH_in', 'Front height channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'LFH_RFH_out', 'Front height channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
connect(SYS, '.CF_in', 'TI_FHU_FH_filter_gain');
connect(SYS, 'TI_FHU_FH_filter_gain', 'TI_FHU_stagewidth_lfh_filter', 'TI_FHU_IL.in1');
connect(SYS, 'TI_FHU_FH_filter_gain', 'TI_FHU_stagewidth_rfh_filter', 'TI_FHU_IL.in2');
connect(SYS, 'TI_FHU_IL', 'TI_FHU_channel_switch1.in1');
connect(SYS, '.LFH_RFH_in', 'TI_FHU_channel_switch1.in2');
connect(SYS, 'TI_FHU_channel_switch1', '.LFH_RFH_out');

add_module(SYS, dc_source_v2_module('StageWithSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.StageWithSource.value = 0;

add_module(SYS, scaler_v2_module('Sixth'));
SYS.Sixth.isDB = 0;
SYS.Sixth.gain = 1/6;
add_module(SYS, scaler_v2_module('NegSixth'));
SYS.NegSixth.isDB = 0;
SYS.NegSixth.gain = -1/6;

add_module(SYS,adder_module('addLfhSet',2));
add_module(SYS,adder_module('addRfhSet',2));
add_module(SYS,dc_source_v2_module('ElevenOverTwelwe', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.ElevenOverTwelwe.value = 11/12;

connect(SYS,'StageWithSource', 'NegSixth', 'addLfhSet.in1');
connect(SYS,'ElevenOverTwelwe', 'addLfhSet.in2');
connect(SYS,'StageWithSource', 'Sixth', 'addRfhSet.in1');
connect(SYS,'ElevenOverTwelwe', 'addRfhSet.in2');

add_module(SYS,dc_source_v2_module('Two', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.Two.value = 2;
add_module(SYS,pow_module('powLfhSet'));
add_module(SYS,pow_module('powRfhSet'));
connect(SYS,'Two','powLfhSet.x');
connect(SYS,'addLfhSet','powLfhSet.y');
connect(SYS,'Two','powRfhSet.x');
connect(SYS,'addRfhSet','powRfhSet.y');
add_module(SYS, scaler_v2_module('Lfh440'));
SYS.Lfh440.isDB = 0;
SYS.Lfh440.gain = 440;
add_module(SYS, scaler_v2_module('Rfh440'));
SYS.Rfh440.isDB = 0;
SYS.Rfh440.gain = 440;
connect(SYS,'powLfhSet', 'Lfh440');
connect(SYS,'powRfhSet', 'Rfh440');


add_module(SYS, param_set_module('Lfh2LfhSetfreq', 'float', 'TI_FHU_stagewidth_lfh_filter.freq'));
add_module(SYS, param_set_module('Rfh2RfhSetfreq', 'float', 'TI_FHU_stagewidth_rfh_filter.freq'));

connect(SYS,'Lfh440', 'Lfh2LfhSetfreq');
connect(SYS,'Rfh440', 'Rfh2RfhSetfreq');

