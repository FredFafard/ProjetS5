clc
clear all
close all
% code matlab par SLAJOIE 04-04-2017

%% choix des parametres
f0 = 20000; % frequences en hz
f1 = 40000;
t1 = 0.01;  % temps du sweep (10 ms pour monter)
nb = 960;           % nb de points
delta = t1/nb;     
t = [0:delta:t1];

%% Generation du sweep
y = chirp(t,f0,t1,f1);

semilogx(t,y)
title('generation de sweep')
%disp('Generation de sweep par fct CHIRP. nb de points = ', nb)

gain = 1;   
%y = y*gain %si necessaire
y = round(y);

%% generer le fichier qu'on sauve..
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

%% output pour fichier .da
%save sweep_generation.txt y -ASCII

%% FFT
Y = fftshift(fft(y))
figure
plot(t, Y)
title('FFT avec FFT shift')

%% enveloppe, filtre passe bas
% a faire
