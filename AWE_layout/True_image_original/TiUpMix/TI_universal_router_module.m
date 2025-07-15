function SYS=TI_universal_router_module(NAME,BLOCKSIZE)

SYS=awe_subsystem('universal router module', 'universal router module');
SYS.name=NAME;

add_pin(SYS,'input', 'in', 'Input', new_pin_type(11,BLOCKSIZE));


add_pin(SYS, 'output', 'out1', 'Output', new_pin_type(1,BLOCKSIZE));
add_pin(SYS, 'output', 'out2', 'Output', new_pin_type(2,BLOCKSIZE));
add_pin(SYS, 'output', 'out3', 'Output', new_pin_type(2,BLOCKSIZE));
add_pin(SYS, 'output', 'out4', 'Output', new_pin_type(2,BLOCKSIZE));
add_pin(SYS, 'output', 'out5', 'Output', new_pin_type(2,BLOCKSIZE));
add_pin(SYS, 'output', 'out6', 'Output', new_pin_type(2,BLOCKSIZE));

SYS = add_module(SYS,interleave_module('il1',1));
SYS = add_module(SYS,interleave_module('il2',2));
SYS = add_module(SYS,interleave_module('il3',2));
SYS = add_module(SYS,interleave_module('il4',2));
SYS = add_module(SYS,interleave_module('il5',2));
SYS = add_module(SYS,interleave_module('il6',2));

SYS = connect(SYS,'il1','.out1');
SYS = connect(SYS,'il2','.out2');
SYS = connect(SYS,'il3','.out3');
SYS = connect(SYS,'il4','.out4');
SYS = connect(SYS,'il5','.out5');
SYS = connect(SYS,'il6','.out6');

SYS = add_module(SYS,deinterleave_module('deil1',11));

SYS = connect(SYS,'deil1.out3','il1');
SYS = connect(SYS,'deil1.out1','il2.in1');
SYS = connect(SYS,'deil1.out2','il2.in2');
SYS = connect(SYS,'deil1.out4','il3.in1');
SYS = connect(SYS,'deil1.out5','il3.in2');
SYS = connect(SYS,'deil1.out6','il4.in1');
SYS = connect(SYS,'deil1.out7','il4.in2');
SYS = connect(SYS,'deil1.out8','il5.in1');
SYS = connect(SYS,'deil1.out9','il5.in2');
SYS = connect(SYS,'deil1.out10','il6.in1');
SYS = connect(SYS,'deil1.out11','il6.in2');

SYS = connect(SYS,'','deil1');

