function SYS = TI_Add1pinTo2channels_module(NAME,BLOCKSIZE)

SYS=awe_subsystem('special adder module', 'special adder module');
SYS.name=NAME;

add_pin(SYS,'input', 'in_1', 'Input', new_pin_type(2,BLOCKSIZE));
add_pin(SYS,'input', 'in_2', 'Input', new_pin_type(1,BLOCKSIZE));

add_pin(SYS, 'output', 'out2', 'Output', new_pin_type(2,BLOCKSIZE));

SYS = add_module(SYS, adder_module('ad1',2));
SYS = add_module(SYS, adder_module('ad2',2));

SYS = add_module(SYS, deinterleave_module('deil1',2));
SYS = add_module(SYS, interleave_module('il1',2));

SYS = connect(SYS, '.in_1', 'deil1');
SYS = connect(SYS, 'il1', '');

SYS = connect(SYS, 'ad1', 'il1.in1');
SYS = connect(SYS, 'ad2', 'il1.in2');

SYS = connect(SYS, 'deil1.out1', 'ad1.in1'); 
SYS = connect(SYS, 'deil1.out2', 'ad2.in1');

SYS = connect(SYS, '.in_2', 'ad1.in2');
SYS = connect(SYS, '.in_2', 'ad2.in2');




