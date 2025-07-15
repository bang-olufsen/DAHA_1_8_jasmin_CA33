function SYS=TI_SurroundControlFrontCh_subsystem(NAME, setup);
% Creates a True image Surround control - front channels subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI FrontCtrl', 'Surround control - front channels');
SYS.name=NAME;

%% Add instances of the true image upmixer subsystem
add_module(SYS, scaler_v2_module('TI_surround_control_front_gain_1'));
SYS.TI_surround_control_front_gain_1.isDB = 1;
SYS.TI_surround_control_front_gain_1.gain = 0;
SYS.TI_surround_control_front_gain_1.smoothingTime=1000;
add_module(SYS, scaler_v2_module('TI_surround_control_front_gain_2'));
SYS.TI_surround_control_front_gain_2.isDB = 1;
SYS.TI_surround_control_front_gain_2.gain = 0;
SYS.TI_surround_control_front_gain_2.smoothingTime=1000;
add_module(SYS, scaler_v2_module('TI_surround_control_front_gain_3'));
SYS.TI_surround_control_front_gain_3.isDB = 1;
SYS.TI_surround_control_front_gain_3.gain = -1000;
SYS.TI_surround_control_front_gain_3.smoothingTime=1000;

add_module(SYS, adder_module('TI_surround_control_front_adder', 2, 1));

%% Input and output pins for respective channels
add_pin(SYS,'input', 'LF_RF_in', 'L/R front channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'CF_in', 'Centre front channel input', new_pin_type(1,setup.BLOCKSIZE));
add_pin(SYS,'input', 'Mono_in', 'Mono channel input', new_pin_type(1,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'LF_RF_out', 'Left, right, front channel output', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'CF_out', 'Centre front channel output', new_pin_type(1,setup.BLOCKSIZE));

%% Connect pins and modules
connect(SYS, '.LF_RF_in', 'TI_surround_control_front_gain_1', '.LF_RF_out');
connect(SYS, '.CF_in', 'TI_surround_control_front_gain_2', 'TI_surround_control_front_adder.in1');
connect(SYS, '.Mono_in', 'TI_surround_control_front_gain_3', 'TI_surround_control_front_adder.in2');
connect(SYS, 'TI_surround_control_front_adder', '.CF_out');

add_module(SYS, dc_source_v2_module('SurroundControllerSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.SurroundControllerSource.value = 0;
add_module(SYS, table_lookup_module('SurroundControllerLookup01',11));
SYS.SurroundControllerLookup01.interpolationType = 0;
SYS.SurroundControllerLookup01.table = [-14 -7 -2 -1 0 0 0 -1 -1 -3 -3]';
SYS.SurroundControllerLookup01.minX = 0;
SYS.SurroundControllerLookup01.maxX = 10;
add_module(SYS, table_lookup_module('SurroundControllerLookup02',11));
SYS.SurroundControllerLookup02.interpolationType = 0;
SYS.SurroundControllerLookup02.table = [-14 -7 -2 -1 0 0 0 -1 -1 -3 -3]';
SYS.SurroundControllerLookup02.minX = 0;
SYS.SurroundControllerLookup02.maxX = 10;
add_module(SYS, table_lookup_module('SurroundControllerLookup03',11));
SYS.SurroundControllerLookup03.interpolationType = 0;
SYS.SurroundControllerLookup03.table = [0 -2 -6 -12 -18 -1000 -1000 -1000 -1000 -1000 -1000]';
SYS.SurroundControllerLookup03.minX = 0;
SYS.SurroundControllerLookup03.maxX = 10;

add_module(SYS, param_set_module('TI_surround_control_front_gain_1set', 'float', 'TI_surround_control_front_gain_1.gain'));
add_module(SYS, param_set_module('TI_surround_control_front_gain_2set', 'float', 'TI_surround_control_front_gain_2.gain'));
add_module(SYS, param_set_module('TI_surround_control_front_gain_3set', 'float', 'TI_surround_control_front_gain_3.gain'));


connect(SYS,'SurroundControllerSource', 'SurroundControllerLookup01', 'TI_surround_control_front_gain_1set');
connect(SYS,'SurroundControllerSource', 'SurroundControllerLookup02', 'TI_surround_control_front_gain_2set');
connect(SYS,'SurroundControllerSource', 'SurroundControllerLookup03', 'TI_surround_control_front_gain_3set');







