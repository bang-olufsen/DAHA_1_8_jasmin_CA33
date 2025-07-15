% helper script to setup path to toolboxes from any subfolder
% copy to local folder and execute
teststr='..\audio-toolboxes';
for n=1:20
    if (exist(teststr)~=0)
        addpath(teststr);
        break;
    else
        teststr=strcat('..\',teststr);
    end
end
% teststr='..\libDSPConcepts\matlab';
% for n=1:20
    % if (exist(teststr)~=0)
        % addpath(teststr);
        % break;
    % else
        % teststr=strcat('..\',teststr);
    % end
% end
clear n
clear teststr
addtoolstopath
        
    
    