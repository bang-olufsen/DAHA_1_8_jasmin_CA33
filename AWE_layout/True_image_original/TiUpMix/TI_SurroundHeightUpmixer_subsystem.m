function SYS=TI_SurroundHeightUpmixer_subsystem(NAME, setup);
% Creates a True image Surround height upmixer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI SHU', 'True image surround height upmixer');
SYS.name=NAME;


%% Add instances of the true image upmixer subsystem
% add modules for surround input
add_module(SYS, biquad_cascade_module('TI_SHU_SH_filter_gain', 1));
sos1=biquad(250,0,0.5,2,setup.FS);
SYS.TI_SHU_SH_filter_gain.coeffs = [sos2aw(sos1)];
add_module(SYS, second_order_filter_cascade_module('TI_SHU_SH_filter_ap',1,1));
SYS.TI_SHU_SH_filter_ap.filterType = 6;
SYS.TI_SHU_SH_filter_ap.freq = 2000;

add_module(SYS, multiplexor_module('TI_SHU_channel_switch', 2));

%% Input and output pins for respective channels
add_pin(SYS,'input', 'LS_RS_in', 'Surround channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'LSH_RSH_in', 'Surround height channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'LSH_RSH_out', 'Surround height channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
connect(SYS, '.LS_RS_in', 'TI_SHU_SH_filter_gain', 'TI_SHU_SH_filter_ap', 'TI_SHU_channel_switch.in1');
connect(SYS, '.LSH_RSH_in', 'TI_SHU_channel_switch.in2');
connect(SYS, 'TI_SHU_channel_switch', '.LSH_RSH_out');


SYS.TI_SHU_channel_switch.index = 1;



