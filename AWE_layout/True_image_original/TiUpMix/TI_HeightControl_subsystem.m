function SYS=TI_HeightControl_subsystem(NAME, setup);
% Creates a True image height control - height channels subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI HeightCtrl', 'Height control - Height channels');
SYS.name=NAME;

%% Add instances of the true image upmixer subsystem
add_module(SYS, scaler_v2_module('TI_HeightCtrl_gain_1',0,2));
SYS.TI_HeightCtrl_gain_1.isDB = 0;
SYS.TI_HeightCtrl_gain_1.gain = 1;
SYS.TI_HeightCtrl_gain_1.smoothingTime=1000;

%% Input and output pins for respective channels
add_pin(SYS,'input', 'LFH_RFH_in', 'Front height channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'LSH_RSH_in', 'Surround height channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'output', 'LFH_RFH_CFH_out', 'Left, right, centre front height channel output', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'output', 'LSH_RSH_out', 'Surround height channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
connect(SYS, '.LFH_RFH_in', 'TI_HeightCtrl_gain_1.in1');
connect(SYS, '.LSH_RSH_in', 'TI_HeightCtrl_gain_1.in2');
connect(SYS, 'TI_HeightCtrl_gain_1.out1', '.LFH_RFH_CFH_out');
connect(SYS, 'TI_HeightCtrl_gain_1.out2', '.LSH_RSH_out');

add_module(SYS, dc_source_v2_module('HeigthControllerSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.HeigthControllerSource.value = 5;
add_module(SYS, table_lookup_module('HeigthControllerLookup01',11));
SYS.HeigthControllerLookup01.interpolationType = 0;
SYS.HeigthControllerLookup01.table = [0 0.1 0.40 0.63 1 1.12 1.26 1.41 1.58 1.78 2.00]';
SYS.HeigthControllerLookup01.minX = 0;
SYS.HeigthControllerLookup01.maxX = 10;

add_module(SYS, param_set_module('TI_HeigthCtrl_gain_1set', 'float', 'TI_HeightCtrl_gain_1.gain'));

connect(SYS, 'HeigthControllerSource', 'HeigthControllerLookup01', 'TI_HeigthCtrl_gain_1set');
