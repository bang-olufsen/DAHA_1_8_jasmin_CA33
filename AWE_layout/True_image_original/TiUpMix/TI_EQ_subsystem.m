function SYS=TI_EQ_subsystem(NAME, setup, NOF_INPUT_CH);
% Creates a True image upmixer equalizer subsystem that utilizes 
% xxx_module to process the 8 channels (still interleaved) 
%
% Arguments:
%    NAME - name of the module

SYS=awe_subsystem('TI EQ', 'True image upmixer equalizer');
SYS.name=NAME;

% Add instances of the true image module
add_module(SYS, biquad_cascade_module('TI_EQ', 2));

sos1 = biquad(1300, -4, 0.5, 7, setup.FS);
sos2 = biquad(100, -1, 1, 10, setup.FS);
SYS.TI_EQ.coeffs = [sos2aw(sos1) sos2aw(sos2)];

% Input and output pins for respective channels
add_pin(SYS,'input', 'in', 'Input into equalizer', new_pin_type(NOF_INPUT_CH,setup.BLOCKSIZE));
add_pin(SYS, 'output', 'out', 'Output from equalizer', new_pin_type(NOF_INPUT_CH,setup.BLOCKSIZE));


% Connect pins and modules
connect(SYS, '.in', 'TI_EQ','.out');



