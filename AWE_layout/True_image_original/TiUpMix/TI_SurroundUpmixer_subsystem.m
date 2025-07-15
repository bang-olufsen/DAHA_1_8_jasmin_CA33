function SYS=TI_SurroundUpmixer_subsystem(NAME, setup);
% Creates a True image surround upmixer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('True image surround upmixer', 'TI SU');
SYS.name=NAME;

% set maximum supported delay (20 ms) and convert to samples
MAXDELAY = ceil(20/1000*setup.FS);

%% Add instances of the true image upmixer subsystem
% Add modules for front channel input
%add_module(SYS, scaler_module('TI_SU_inv_rf_channel'));
%add_module(SYS, adder_module('TI_SU_lf_rf_adder', 1, 1));
add_module(SYS, mixer_module('TI_SU_lf_rf_2_mono_mixer', 1));

add_module(SYS, biquad_cascade_module('TI_SU_surround_filter_gain',4));
sos1=biquad(1300,-4,0.5,7,setup.FS);
sos2=biquad(100,-12,0.5,10,setup.FS);
sos4=biquad(100,-12,0.5,10,setup.FS); %Neede 2 filters to make 360Phase 
[B, A]=biquad(3000,-9,0.5,11,setup.FS);
sos3=[0.63*B A];
SYS.TI_SU_surround_filter_gain.coeffs = [sos2aw(sos1) sos2aw(sos2) sos2aw(sos4) sos2aw(sos3)];

add_module(SYS, scaler_v2_module('LsRsUpmixScale'));
SYS.LsRsUpmixScale.isDB = 1;
SYS.LsRsUpmixScale.gain = 0;

add_module(SYS, delay_module('TI_SU_surround_delay', MAXDELAY, 'AWE_HEAP_FAST2SLOW'));
SYS.TI_SU_surround_delay.maxDelay = 580;
SYS.TI_SU_surround_delay.currentDelay = 576;
add_module(SYS, second_order_filter_cascade_module('TI_SU_envelopment_lw_filter',1,1));
SYS.TI_SU_envelopment_lw_filter.filterType = 6;
SYS.TI_SU_envelopment_lw_filter.freq = 500;
add_module(SYS, second_order_filter_cascade_module('TI_SU_envelopment_rw_filter',1,1));
SYS.TI_SU_envelopment_rw_filter.filterType = 6;
SYS.TI_SU_envelopment_rw_filter.freq = 500;
add_module(SYS, interleave_module('TI_SU_IL', 2));

% add module for surround channel input
add_module(SYS, mixer_smoothed_module('TI_SU_envelopment_mixer', 2));
SYS.TI_SU_envelopment_mixer.smoothingTime=500;

% add modules for input switch
add_module(SYS, multiplexor_module('TI_SU_channel_switch', 2));


%% Input and output pins for respective channels
add_pin(SYS,'input', 'Front_in', 'Front channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS,'input', 'Surround_in', 'Surround channel input', new_pin_type(2,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'Surround_out', 'Surround channel output', new_pin_type(2,setup.BLOCKSIZE));


%% Connect pins and modules
% connect modules for front channel input
connect(SYS, '.Front_in', 'TI_SU_lf_rf_2_mono_mixer', 'TI_SU_surround_filter_gain', 'TI_SU_surround_delay', 'LsRsUpmixScale' );
connect(SYS, 'LsRsUpmixScale', 'TI_SU_envelopment_lw_filter', 'TI_SU_IL.in1');
connect(SYS, 'LsRsUpmixScale', 'TI_SU_envelopment_rw_filter', 'TI_SU_IL.in2');
connect(SYS, 'TI_SU_IL', 'TI_SU_channel_switch.in1');

% Connect modules for surround channel input
connect(SYS, '.Surround_in', 'TI_SU_envelopment_mixer', 'TI_SU_channel_switch.in2');

% connect channel switch to output
connect(SYS, 'TI_SU_channel_switch', '.Surround_out');


%% Set allocation priority
SYS.TI_SU_surround_delay.allocationPriority = setup.allocationPriority.delay;
SYS = prebuild(SYS);
SYS.TI_SU_lf_rf_2_mono_mixer.gain = [ 1; -1];

add_module(SYS, table_lookup_module('SurroundLookup01',11));
SYS.SurroundLookup01.interpolationType = 0;
SYS.SurroundLookup01.table = [-4 -3 -2 -1 0 0 0 1 2 3 4]';
SYS.SurroundLookup01.minX = 0;
SYS.SurroundLookup01.maxX = 10;
add_module(SYS, table_lookup_module('SurroundLookup02',11));
SYS.SurroundLookup02.interpolationType = 0;
SYS.SurroundLookup02.table = [0.71 0.5 0.35 0.25 0.13 0 0 0 0 0 0]';
SYS.SurroundLookup02.minX = 0;
SYS.SurroundLookup02.maxX = 10;
add_module(SYS, table_lookup_module('SurroundLookup03',11));
SYS.SurroundLookup03.interpolationType = 0;
SYS.SurroundLookup03.table = [0.5 0.56 0.63 0.71 0.79 1 1 1 1 1 1]';
SYS.SurroundLookup03.minX = 0;
SYS.SurroundLookup03.maxX = 10;

add_module(SYS, dc_source_v2_module('EnvelopmentSource',1, 1, setup.FS/setup.BLOCKSIZE));
SYS.EnvelopmentSource.value = 0;

connect(SYS,'EnvelopmentSource', 'SurroundLookup01');
connect(SYS,'EnvelopmentSource', 'SurroundLookup02');
connect(SYS,'EnvelopmentSource', 'SurroundLookup03');

add_module(SYS, param_set_module('LsRsUpmixScaleSet', 'float', 'LsRsUpmixScale.gain'));
connect(SYS,'SurroundLookup01', 'LsRsUpmixScaleSet');

add_module(SYS, param_set_module('Ls2LsSet', 'float', 'TI_SU_envelopment_mixer.gain[0]'));
add_module(SYS, param_set_module('Rs2LsSet', 'float', 'TI_SU_envelopment_mixer.gain[1]'));
add_module(SYS, param_set_module('Ls2RsSet', 'float', 'TI_SU_envelopment_mixer.gain[2]'));
add_module(SYS, param_set_module('Rs2RsSet', 'float', 'TI_SU_envelopment_mixer.gain[3]'));

connect(SYS,'SurroundLookup03', 'Ls2LsSet');
connect(SYS,'SurroundLookup03', 'Rs2RsSet');
connect(SYS,'SurroundLookup02', 'Ls2RsSet');
connect(SYS,'SurroundLookup02', 'Rs2LsSet');

add_module(SYS, scaler_v2_module('Third'));
SYS.Third.isDB = 0;
SYS.Third.gain = 1/3;
add_module(SYS, scaler_v2_module('NegThird'));
SYS.NegThird.isDB = 0;
SYS.NegThird.gain = -1/3;

add_module(SYS,adder_module('addLsSet',2));
add_module(SYS,adder_module('addRsSet',2));
add_module(SYS,dc_source_v2_module('Fourth', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.Fourth.value = 0.25;

connect(SYS,'EnvelopmentSource', 'NegThird', 'addLsSet.in1');
connect(SYS,'Fourth', 'addLsSet.in2');
connect(SYS,'EnvelopmentSource', 'Third', 'addRsSet.in1');
connect(SYS,'Fourth', 'addRsSet.in2');

add_module(SYS,dc_source_v2_module('Two', 1, 1, setup.FS/setup.BLOCKSIZE));
SYS.Two.value = 2;
add_module(SYS,pow_module('powLsSet'));
add_module(SYS,pow_module('powRsSet'));
connect(SYS,'Two','powLsSet.x');
connect(SYS,'addLsSet','powLsSet.y');
connect(SYS,'Two','powRsSet.x');
connect(SYS,'addRsSet','powRsSet.y');
add_module(SYS, scaler_v2_module('Ls440'));
SYS.Ls440.isDB = 0;
SYS.Ls440.gain = 440;
add_module(SYS, scaler_v2_module('Rs440'));
SYS.Rs440.isDB = 0;
SYS.Rs440.gain = 440;
connect(SYS,'powLsSet', 'Ls440');
connect(SYS,'powRsSet', 'Rs440');


add_module(SYS, param_set_module('Ls2LsSetfreq', 'float', 'TI_SU_envelopment_lw_filter.freq'));
add_module(SYS, param_set_module('Rs2RsSetfreq', 'float', 'TI_SU_envelopment_rw_filter.freq'));

connect(SYS,'Ls440', 'Ls2LsSetfreq');
connect(SYS,'Rs440', 'Rs2RsSetfreq');



