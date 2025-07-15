function SYS=TI_SurroundControlSurroundCh_subsystem(NAME, setup);
% Creates a True image Surround control - surround channels subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI SurroundCtrl', 'Surround control - Surround channels');
SYS.name=NAME;


%% Add instances of the true image upmixer subsystem
add_module(SYS, scaler_v2_module('TI_surround_control_surround_gain_1'));
SYS.TI_surround_control_surround_gain_1.isDB = 1;
SYS.TI_surround_control_surround_gain_1.gain = 0;
SYS.TI_surround_control_surround_gain_1.smoothingTime = 1000;
add_module(SYS, scaler_v2_module('TI_surround_control_surround_gain_2'));
SYS.TI_surround_control_surround_gain_2.isDB = 1;
SYS.TI_surround_control_surround_gain_2.gain = 0;
SYS.TI_surround_control_surround_gain_2.smoothingTime = 1000;

%% Input and output pins for respective channels
add_pin(SYS,'input', 'Surround_in', 'Surround channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'Back_in', 'Back channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Surround_out', 'Surround channel output', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Back_out', 'L/R back channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
connect(SYS, '.Surround_in', 'TI_surround_control_surround_gain_1', '.Surround_out');
connect(SYS, '.Back_in', 'TI_surround_control_surround_gain_2', '.Back_out');

add_module(SYS, dc_source_v2_module('SurroundControllerSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.SurroundControllerSource.value = 0;
add_module(SYS, table_lookup_module('SurroundControllerLookup01',11));
SYS.SurroundControllerLookup01.interpolationType = 0;
SYS.SurroundControllerLookup01.table = [-10 -8 -6 -4 -2 0 1 2 2 3 3]';
SYS.SurroundControllerLookup01.minX = 0;
SYS.SurroundControllerLookup01.maxX = 10;
add_module(SYS, table_lookup_module('SurroundControllerLookup02',11));
SYS.SurroundControllerLookup02.interpolationType = 0;
SYS.SurroundControllerLookup02.table = [-10 -8 -6 -4 -2 0 1 2 2 3 3]';
SYS.SurroundControllerLookup02.minX = 0;
SYS.SurroundControllerLookup02.maxX = 10;

add_module(SYS, param_set_module('TI_surround_control_surround_gain_1set', 'float', 'TI_surround_control_surround_gain_1.gain'));
add_module(SYS, param_set_module('TI_surround_control_surround_gain_2set', 'float', 'TI_surround_control_surround_gain_2.gain'));

connect(SYS, 'SurroundControllerSource', 'SurroundControllerLookup01', 'TI_surround_control_surround_gain_1set');
connect(SYS, 'SurroundControllerSource', 'SurroundControllerLookup02', 'TI_surround_control_surround_gain_2set');


