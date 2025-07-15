function SYS=TI_SNoiseGate(name, setup)

SYS=awe_subsystem('Side noise gate');
SYS.name=name;

SYS=add_pin(SYS,'input','in1','input', new_pin_type(2,setup.BLOCKSIZE));
SYS=add_pin(SYS,'output','out1','output', new_pin_type(2,setup.BLOCKSIZE));

add_module(SYS, deinterleave_module('deil1',2));
add_module(SYS, interleave_module('il1',2));

SYS=add_module(SYS,lfstr2aw(mat2lfstr([1,1;1,-1]),'LR2MS'));
SYS=connect(SYS,'','deil1','LR2MS');

sdstr=sdsetup;
sdstr.AvgExp=1;
sdstr.dBOut=1;
sdstr.TAtt=1e-3;
sdstr.TDel=0;
sdstr.TRel=500e-3;
sdstr.Type='rcfilt';
sdstr=repmat(sdstr,2,1);

SYS=add_module(SYS,sdstr2aw(sdstr,'MSLevEst'));
SYS=connect(SYS,'LR2MS','MSLevEst');

SYS=add_module(SYS,lfstr2aw(mat2lfstr([1,0;-1,0]),'MSDiff'));
SYS=connect(SYS,'MSLevEst','MSDiff');

lustr=lusetup;
lustr.Table=[1;0];
lustr.XStart=16.9;
lustr.XStep=.2;

SYS=add_module(SYS,lustr2aw(lustr,'Diff2Gain'));
SYS=connect(SYS,'MSDiff','Diff2Gain');

sdstr_gain=sdsetup;
% sdstr_gain.AvgExp=1;
sdstr_gain.dBOut=0;
sdstr_gain.TAtt=1e-3;
sdstr_gain.TDel=0;
sdstr_gain.TRel=5000e-3;
sdstr_gain.Type='rcfilt';

SYS=add_module(SYS,sdstr2aw(sdstr_gain,'GainSmooth'));
SYS=connect(SYS,'Diff2Gain','GainSmooth');

mpstr=repmat(mpsetup,2,1);
mpstr(1).Inputs=1;
mpstr(2).Inputs=[2,3];
SYS=add_module(SYS,mpstr2aw(mpstr,'SGainControl'));
SYS=connect(SYS,'LR2MS.out1','SGainControl.in1');
SYS=connect(SYS,'LR2MS.out2','SGainControl.in2');
SYS=connect(SYS,'GainSmooth','SGainControl.in3');

SYS=add_module(SYS,lfstr2aw(mat2lfstr(.5*[1,1;1,-1]),'MS2LR'));
SYS=connect(SYS,'SGainControl','MS2LR','il1','');
