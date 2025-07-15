global AWE_INFO;
AWE_INFO.AWE_version = 'v6';
setup.FS = 48000;
setup.BLOCKSIZE = 64;
setup.nI = 11;
setup.nO = 11;
setup.allocationPriority.delay = [];

SYS=target_system('AudioLayout', 'Audio Layout for CA44', 1);

add_pin(SYS,'input', 'in', '', new_pin_type(setup.nI, setup.BLOCKSIZE, setup.FS, 'float'));
add_pin(SYS,'output', 'out', '', new_pin_type(setup.nO, setup.BLOCKSIZE, setup.FS, 'float'));

add_module(SYS, true_image_upmixer_subsystem('TiSubSys', setup ));

SYS=connect(SYS,'','TiSubSys','');

SYS=build(SYS)

draw(SYS)

test_start_audio

draw(SYS)
