function SYS=TI_FrontUpmixer_subsystem(NAME, setup);
% Creates a True image front upmixer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI FU', 'True image front upmixer');
SYS.name=NAME;

% set maximum supported delay (5 ms) and convert to samples
MAXDELAY = ceil(5/1000*setup.FS);

%% Add instances of the true image upmixer subsystem
% add modules for 2-channel input
add_module(SYS, mixer_smoothed_module('TI_FU_2ch_mixer', 2));
SYS.TI_FU_2ch_mixer.gain = [ -0.2, 0; 0, -0.2];

add_module(SYS,delay_module('LRFdelay', 96, 'AWE_HEAP_FAST2SLOW')); 
SYS.LRFdelay.currentDelay = 14; %Change from 1.5 to 0.3ms dealy FIX CAXLIV-6662-Tinny-sound-from-PCM-2.0-sources-2.5.5.1056

add_module(SYS, scaler_v2_module('TI_FU_2ch_scale1'));
SYS.TI_FU_2ch_scale1.isDB = 1;
SYS.TI_FU_2ch_scale1.gain = 0;
add_module(SYS, scaler_v2_module('TI_FU_1ch_scale2'));
SYS.TI_FU_1ch_scale2.isDB = 1;
SYS.TI_FU_1ch_scale2.gain = 0;

add_module(SYS, adder_module('TI_FU_2ch_adder', 1, 1));

add_module(SYS, biquad_cascade_module('TI_FU_front_filter_gain', 1));
[B,A] = biquad(100,-12,0.5,10,setup.FS);
sos1 = [0.25*B A];
SYS.TI_FU_front_filter_gain.coeffs = sos2aw(sos1);
add_module(SYS, router_module('TI_FU_2ch_output_router', 2, 3));

% add module for 3-channel input
add_module(SYS, router_module('TI_FU_3ch_input_router', 2, 3));
add_module(SYS, mixer_smoothed_module('TI_FU_3ch_mixer', 3));
SYS.TI_FU_3ch_mixer.smoothingTime=500;

% add module for front upmixer switch
add_module(SYS, multiplexor_module('TI_FU_channel_switch', 2));
add_module(SYS, deinterleave_module('TI_FU_DIL', 3));
add_module(SYS, interleave_module('TI_FU_IL', 2));



%% Input and output pins for respective channels
add_pin(SYS,'input', 'Front_in', 'Front channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'Centre_in', 'Centre channel input', new_pin_type(1,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Front_out', 'Front channel output', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Centre_out', 'Centre channel output', new_pin_type(1,setup.BLOCKSIZE));


%% Connect pins and modules
% connect modules for 2-channel input
%connect(SYS, '.in', 'TI_FU_2ch_input_router');
connect(SYS, '.Front_in', 'LRFdelay', 'TI_FU_2ch_mixer', 'TI_FU_2ch_scale1' , 'TI_FU_2ch_output_router.in1');
connect(SYS, '.Front_in', 'TI_FU_2ch_adder', 'TI_FU_front_filter_gain', 'TI_FU_1ch_scale2', 'TI_FU_2ch_output_router.in2');

% conenct modules for 3-channel input
connect(SYS, '.Front_in', 'TI_FU_3ch_input_router.in1');
connect(SYS, '.Centre_in', 'TI_FU_3ch_input_router.in2');
connect(SYS, 'TI_FU_3ch_input_router', 'TI_FU_3ch_mixer', 'TI_FU_channel_switch.in2');

% Connect modules for output switch
connect(SYS, 'TI_FU_2ch_output_router', 'TI_FU_channel_switch.in1');
connect(SYS, 'TI_FU_channel_switch', 'TI_FU_DIL');
connect(SYS, 'TI_FU_DIL.out1', 'TI_FU_IL.in1');
connect(SYS, 'TI_FU_DIL.out2', 'TI_FU_IL.in2');
connect(SYS, 'TI_FU_IL', '.Front_out');
connect(SYS, 'TI_FU_DIL.out3', '.Centre_out');


SYS.TI_FU_2ch_output_router.channelIndex(1) = 0*2^16 + 0;     % Lf => ch 0
SYS.TI_FU_2ch_output_router.channelIndex(2) = 0*2^16 + 1;     % Rf => ch 1
SYS.TI_FU_2ch_output_router.channelIndex(3) = 1*2^16 + 0;     % Cf => ch 2

SYS.TI_FU_3ch_input_router.channelIndex(1) = 0*2^16 + 0;      % Lf => ch 0
SYS.TI_FU_3ch_input_router.channelIndex(2) = 0*2^16 + 1;      % Rf => ch 1
SYS.TI_FU_3ch_input_router.channelIndex(3) = 1*2^16 + 0;      % Cf => ch 2

SYS=prebuild(SYS);

add_module(SYS, dc_source_v2_module('StageWithSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.StageWithSource.value = 10;

add_module(SYS, table_lookup_module('FrontLookup01',11));
SYS.FrontLookup01.interpolationType = 0;
SYS.FrontLookup01.table = [0 0.18 0.35 0.71 0.89 1 1 1 1 1 1]';
SYS.FrontLookup01.minX = 0;
SYS.FrontLookup01.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup02',11));
SYS.FrontLookup02.interpolationType = 0;
SYS.FrontLookup02.table = [0.5 0.35 0.25 0.13 0.06 0 0 0 0 0 0]';
SYS.FrontLookup02.minX = 0;
SYS.FrontLookup02.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup03',11));
SYS.FrontLookup03.interpolationType = 0;
SYS.FrontLookup03.table = [0 0 0 0 0 0 0.06 0.13 0.25 0.35 0.5]';
SYS.FrontLookup03.minX = 0;
SYS.FrontLookup03.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup04',11));
SYS.FrontLookup04.interpolationType = 0;
SYS.FrontLookup04.table = [1 1 1 1 1 1 0.89 0.71 0.35 0.18 0]';
SYS.FrontLookup04.minX = 0;
SYS.FrontLookup04.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup05',11));
SYS.FrontLookup05.interpolationType = 0;
SYS.FrontLookup05.table = [-10 -8 -6 -4 -2 0 0 0 1 2 3]';
SYS.FrontLookup05.minX = 0;
SYS.FrontLookup05.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup06',11));
SYS.FrontLookup06.interpolationType = 0;
SYS.FrontLookup06.table = [3 3 2 2 1 0 -3 -6 -9 -12 -100]';
SYS.FrontLookup06.minX = 0;
SYS.FrontLookup06.maxX = 10;
add_module(SYS, table_lookup_module('FrontLookup07',11));
SYS.FrontLookup07.interpolationType = 0;
SYS.FrontLookup07.table = [ -0.2825 -0.2825 -0.2518 -0.2518 -0.2244 -0.2000 -0.1416 -0.1002 -0.0710 -0.0502 0]';
SYS.FrontLookup07.minX = 0;
SYS.FrontLookup07.maxX = 10;


add_module(SYS,param_set_module('LCross', 'float', 'TI_FU_2ch_mixer.gain[1]'));
add_module(SYS,param_set_module('Rcross', 'float', 'TI_FU_2ch_mixer.gain[2]'));

add_module(SYS,param_set_module('L2C', 'float', 'TI_FU_3ch_mixer.gain[6]'));
add_module(SYS,param_set_module('R2C', 'float', 'TI_FU_3ch_mixer.gain[7]'));
add_module(SYS,param_set_module('C2C', 'float', 'TI_FU_3ch_mixer.gain[8]'));
add_module(SYS,param_set_module('C2R', 'float', 'TI_FU_3ch_mixer.gain[5]'));
add_module(SYS,param_set_module('C2L', 'float', 'TI_FU_3ch_mixer.gain[2]'));
add_module(SYS,param_set_module('L2L', 'float', 'TI_FU_3ch_mixer.gain[0]'));
add_module(SYS,param_set_module('R2R', 'float', 'TI_FU_3ch_mixer.gain[4]'));


connect(SYS,'StageWithSource', 'FrontLookup01');
connect(SYS,'StageWithSource', 'FrontLookup02');
connect(SYS,'StageWithSource', 'FrontLookup03');
connect(SYS,'StageWithSource', 'FrontLookup04');
connect(SYS,'StageWithSource', 'FrontLookup05');
connect(SYS,'StageWithSource', 'FrontLookup06');
connect(SYS,'StageWithSource', 'FrontLookup07');
connect(SYS, 'FrontLookup04', 'C2C');
connect(SYS, 'FrontLookup02', 'L2C');
connect(SYS, 'FrontLookup07', 'LCross');
connect(SYS, 'FrontLookup07', 'Rcross');
connect(SYS, 'FrontLookup02', 'R2C');
connect(SYS, 'FrontLookup03', 'C2L');
connect(SYS, 'FrontLookup03', 'C2R');
connect(SYS, 'FrontLookup01', 'L2L');
connect(SYS, 'FrontLookup01', 'R2R');

add_module(SYS, param_set_module('TI_FU_2ch_scale1Set', 'float', 'TI_FU_2ch_scale1.gain'));
add_module(SYS, param_set_module('TI_FU_1ch_scale2Set', 'float', 'TI_FU_1ch_scale2.gain'));

connect(SYS, 'FrontLookup05', 'TI_FU_2ch_scale1Set');
connect(SYS, 'FrontLookup06', 'TI_FU_1ch_scale2Set');


