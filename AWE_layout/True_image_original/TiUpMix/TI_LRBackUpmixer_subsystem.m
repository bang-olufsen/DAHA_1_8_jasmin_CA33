function SYS=TI_LRBackUpmixer_subsystem(NAME, setup);
% Creates a True image L/R back upmixer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI LRBU', 'True image L/R Back upmixer');
SYS.name=NAME;

% set maximum supported delay (5 ms) and convert to samples
MAXDELAY = ceil(10/1000*setup.FS);

%% Add instances of the true image upmixer subsystem
% add modules for Surround input
add_module(SYS, adder_module('TI_LRBU_surround_adder', 1, 1));

add_module(SYS, biquad_cascade_module('TI_LRBU_back_filter_gain',1));
sos1=biquad(200,0,0.5,2,setup.FS);
SYS.TI_LRBU_back_filter_gain.coeffs = [sos2aw(sos1)];
add_module(SYS, scaler_v2_module('LbRbUpmixScale'));
SYS.LbRbUpmixScale.isDB = 1;
SYS.LbRbUpmixScale.gain = 0;

add_module(SYS, delay_module('TI_LRBU_back_delay', MAXDELAY, 'AWE_HEAP_FAST2SLOW'));
SYS.TI_LRBU_back_delay.currentDelay = ceil(7/1000*setup.FS);
add_module(SYS, second_order_filter_cascade_module('TI_LRBU_envelopment_lb_filter',1,1));
SYS.TI_LRBU_envelopment_lb_filter.filterType = 6;
SYS.TI_LRBU_envelopment_lb_filter.freq = 500;
add_module(SYS, second_order_filter_cascade_module('TI_LRBU_envelopment_rb_filter',1,1));
SYS.TI_LRBU_envelopment_rb_filter.filterType = 6;
SYS.TI_LRBU_envelopment_rb_filter.freq = 500;
add_module(SYS, interleave_module('TI_LRBU_IL', 2));

% add_modules for back input
add_module(SYS, mixer_smoothed_module('TI_LRBU_back_mixer', 2));
SYS.TI_LRBU_back_mixer.smoothingTime=500;
% add_modules for input switch
add_module(SYS, multiplexor_module('TI_LRBU_channel_switch', 2));
SYS.TI_LRBU_channel_switch.index = 1;



%% Input and output pins for respective channels
add_pin(SYS,'input', 'Surround_in', 'Surround channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'Back_in', 'Back channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Back_out', 'Back channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
% connect modules for surround input
connect(SYS, '.Surround_in', 'TI_LRBU_surround_adder', 'TI_LRBU_back_filter_gain', 'TI_LRBU_back_delay','LbRbUpmixScale');
connect(SYS, 'LbRbUpmixScale', 'TI_LRBU_envelopment_lb_filter', 'TI_LRBU_IL.in1');
connect(SYS, 'LbRbUpmixScale', 'TI_LRBU_envelopment_rb_filter', 'TI_LRBU_IL.in2');
connect(SYS, 'TI_LRBU_IL', 'TI_LRBU_channel_switch.in1');

% connect modules for back input
connect(SYS, '.Back_in', 'TI_LRBU_back_mixer', 'TI_LRBU_channel_switch.in2');

% connect modules for input switch
connect(SYS, 'TI_LRBU_channel_switch', '.Back_out');


%% Set allocation priority
SYS.TI_LRBU_back_delay.allocationPriority = setup.allocationPriority.delay;


add_module(SYS, dc_source_v2_module('EnvelopmentSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.EnvelopmentSource.value = 0;

add_module(SYS, table_lookup_module('BackLookup01',11));
SYS.BackLookup01.interpolationType = 0;
SYS.BackLookup01.table = [-4 -3 -2 -1 0 0 0 1 2 3 4]';
SYS.BackLookup01.minX = 0;
SYS.BackLookup01.maxX = 10;
add_module(SYS, table_lookup_module('BackLookup02',11));
SYS.BackLookup02.interpolationType = 0;
SYS.BackLookup02.table = [0.71 0.5 0.35 0.25 0.13 0 0 0 0 0 0]';
SYS.BackLookup02.minX = 0;
SYS.BackLookup02.maxX = 10;
add_module(SYS, table_lookup_module('BackLookup03',11));
SYS.BackLookup03.interpolationType = 0;
SYS.BackLookup03.table = [0.5 0.56 0.63 0.71 0.79 1 1 1 1 1 1]';
SYS.BackLookup03.minX = 0;
SYS.BackLookup03.maxX = 10;

add_module(SYS, param_set_module('LbRbUpmixScaleSet', 'float', 'LbRbUpmixScale.gain'));
connect(SYS,'BackLookup01', 'LbRbUpmixScaleSet');

add_module(SYS, param_set_module('Lb2LbSet', 'float', 'TI_LRBU_back_mixer.gain[0]'));
add_module(SYS, param_set_module('Rb2LbSet', 'float', 'TI_LRBU_back_mixer.gain[1]'));
add_module(SYS, param_set_module('Lb2RbSet', 'float', 'TI_LRBU_back_mixer.gain[2]'));
add_module(SYS, param_set_module('Rb2RbSet', 'float', 'TI_LRBU_back_mixer.gain[3]'));

connect(SYS,'EnvelopmentSource', 'BackLookup01');
connect(SYS,'EnvelopmentSource', 'BackLookup02');
connect(SYS,'EnvelopmentSource', 'BackLookup03');
connect(SYS, 'BackLookup02', 'Rb2LbSet');
connect(SYS, 'BackLookup02', 'Lb2RbSet');
connect(SYS, 'BackLookup03', 'Lb2LbSet');
connect(SYS, 'BackLookup03', 'Rb2RbSet');

add_module(SYS, scaler_v2_module('Third'));
SYS.Third.isDB = 0;
SYS.Third.gain = 1/3;
add_module(SYS, scaler_v2_module('NegThird'));
SYS.NegThird.isDB = 0;
SYS.NegThird.gain = -1/3;

add_module(SYS,adder_module('addLbSet',2));
add_module(SYS,adder_module('addRbSet',2));
add_module(SYS,dc_source_v2_module('Fourth', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.Fourth.value = 0.25;

connect(SYS,'EnvelopmentSource', 'NegThird', 'addLbSet.in1');
connect(SYS,'Fourth', 'addLbSet.in2');
connect(SYS,'EnvelopmentSource', 'Third', 'addRbSet.in1');
connect(SYS,'Fourth', 'addRbSet.in2');

add_module(SYS,dc_source_v2_module('Two', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.Two.value = 2;
add_module(SYS,pow_module('powLbSet'));
add_module(SYS,pow_module('powRbSet'));
connect(SYS,'Two','powLbSet.x');
connect(SYS,'addLbSet','powLbSet.y');
connect(SYS,'Two','powRbSet.x');
connect(SYS,'addRbSet','powRbSet.y');
add_module(SYS, scaler_v2_module('Lb440'));
SYS.Lb440.isDB = 0;
SYS.Lb440.gain = 440;
add_module(SYS, scaler_v2_module('Rb440'));
SYS.Rb440.isDB = 0;
SYS.Rb440.gain = 440;
connect(SYS,'powLbSet', 'Lb440');
connect(SYS,'powRbSet', 'Rb440');


add_module(SYS, param_set_module('Lb2LbSetfreq', 'float', 'TI_LRBU_envelopment_lb_filter.freq'));
add_module(SYS, param_set_module('Rb2RbSetfreq', 'float', 'TI_LRBU_envelopment_rb_filter.freq'));

connect(SYS,'Lb440', 'Lb2LbSetfreq');
connect(SYS,'Rb440', 'Rb2RbSetfreq');

