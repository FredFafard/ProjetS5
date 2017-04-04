clc
clear all
close all
% code matlab par SLAJOIE 04-04-2017

f0 = 20000; % frequences en hz
f1 = 40000;

t1 = 0.01;  % temps du sweep (10 ms pour monter)
nb = 960;           % nb de points
delta = t1/nb;     
t = [0:delta:t1];

y = chirp(t,f0,t1,f1);

semilogx(t,y)
title('generation de sweep')
%disp('Generation de sweep par fct CHIRP. nb de points = ', nb)

f = fopen('sweep_gen.txt','w');
fprintf(f,'{');
fprintf(f,'\n');
for i = 1:length(y)-1
    fprintf(f,'%1.4f',y(i));
    fprintf(f,',');
    fprintf(f,'\n');
end
fprintf(f,'%1.4f',y(i));
fprintf(f,'\n');
fprintf(f,'}');
fclose(f);

%%save sweep_generation.txt y -ASCII
