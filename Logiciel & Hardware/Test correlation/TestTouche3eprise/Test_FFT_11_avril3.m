clc
clear all
close all

%% VRAI DONNÉES DU DSK
%   minuscule: temporel
%   MAJUSCUL: FREQ (FFT)

nt = xlsread('NoTouch');        %% load 8 colonnes dans un fichier
entre = xlsread('Entre');
opose = xlsread('Oppose');
poigne = xlsread('Poigne');

% n = (96000/8192)*(1:8192);

%% FFT

% FFT des données
%-------------------------------------------------------
for n = 1:8
    NT(:,n) = abs(fft(nt(:,n)));
end

moyNT(:,1) = (NT(:,1)+NT(:,3)+NT(:,5)+NT(:,7))/4;
moyNT(:,2) = (NT(:,2)+NT(:,4)+NT(:,6)+NT(:,8))/4;

for n = 1:8
    ENT(:,n) = abs(fft(entre(:,n)));
end

moyENT(:,1) = (ENT(:,1)+ENT(:,3)+ENT(:,5)+ENT(:,7))/4;
moyENT(:,2) = (ENT(:,2)+ENT(:,4)+ENT(:,6)+ENT(:,8))/4;

for n = 1:8
    OP(:,n) = abs(fft(opose(:,n)));
end

moyOP(:,1) = (OP(:,1)+OP(:,3)+OP(:,5)+OP(:,7))/4;
moyOP(:,2) = (OP(:,2)+OP(:,4)+OP(:,6)+OP(:,8))/4;

for n = 1:8
    POI(:,n) = abs(fft(poigne(:,n)));
end

moyPOI(:,1) = (POI(:,1)+POI(:,3)+POI(:,5)+POI(:,7))/4;
moyPOI(:,2) = (POI(:,2)+POI(:,4)+POI(:,6)+POI(:,8))/4;
%-------------------------------------------------------

% Lisser les données (n(0) = (N(-1)+N(0)+N(1))/3
%-------------------------------------------------------
ordreSmooth = 15;
range = [1200:1320 1475:1550 1650:1800 2000:2400 2810:2860 3050:3150 3260:3420 3580:3680];
for m = 1:2
    NTsmooth(:,m) = smooth(moyNT(:,m),ordreSmooth);
    ENTsmooth(:,m) = smooth(moyENT(:,m),ordreSmooth);
    OPsmooth(:,m) = smooth(moyOP(:,m),ordreSmooth);
    POIsmooth(:,m) = smooth(moyPOI(:,m),ordreSmooth);
end
%-------------------------------------------------------   
    

% figure
% title('RAW FFT DATA')
% hold on
% plot(NT)
% plot(COTE)
% plot(CONTOUR)
% plot(FOND)
% plot(POIGNEE)
% legend('No touch','cote','contour','fond','poignee');

% Affichage des FFT
%------------------------------------------------------- 
figure
% NoTouch
subplot(3,1,1)
plot(NTsmooth(:,1));
hold on;
plot(NTsmooth(:,2));
title('Réponse en fréquence lissé - NoTouch')
xlabel('Échantillon');
ylabel('Amplitude (dB)');
% Entre
subplot(3,1,2)
plot(ENTsmooth(:,1));
hold on;
plot(ENTsmooth(:,2));
title('Réponse en fréquence lissé - Entre')
xlabel('Échantillon');
ylabel('Amplitude (dB)');
% Opose
subplot(3,1,3)
plot(OPsmooth(:,1));
hold on;
plot(OPsmooth(:,2));
title('Réponse en fréquence lissé - Opose')
xlabel('Échantillon');
ylabel('Amplitude (dB)');

figure
plot(NTsmooth(1:end/2,1));
hold on;
plot(ENTsmooth(1:end/2,1));
plot(OPsmooth(1:end/2,1));
plot(POIsmooth(1:end/2,1));
title('Réponses en fréquence lissées et superposé')
legend('NoTouch','Entre','Opposé','Poignée');
xlabel('Échantillon');
ylabel('Amplitude (G)');
%------------------------------------------------------- 

% Ligne 1 = NT(1)       % Colonne 1 = NT(2)
% Ligne 2 = ENT(1)      % Colonne 2 = ENT(2)
% Ligne 3 = OP(1)       % Colonne 3 = OP(2)
% Autocorrélation moyenne avec son propre test (OUI)
%------------------------------------------------------- 
Corr(1,1) = 1 - sum((NTsmooth(1:end/2,1)-NTsmooth(1:end/2,2)).^2)/sum(NTsmooth(1:end/2,1).^2);
Corr(2,2) = 1 - sum((ENTsmooth(1:end/2,1)-ENTsmooth(1:end/2,2)).^2)/sum(ENTsmooth(1:end/2,1).^2); 
Corr(3,3) = 1 - sum((OPsmooth(1:end/2,1)-OPsmooth(1:end/2,2)).^2)/sum(OPsmooth(1:end/2,1).^2); 
Corr(4,4) = 1 - sum((POIsmooth(1:end/2,1)-POIsmooth(1:end/2,2)).^2)/sum(POIsmooth(1:end/2,1).^2); 
%------------------------------------------------------- 

% Corrélation - NoTouch (NON)
%------------------------------------------------------- 
Corr(1,2) = 1 - sum((NTsmooth(1:end/2,1)-ENTsmooth(1:end/2,2)).^2)/sum(NTsmooth(1:end/2,1).^2);
Corr(1,3) = 1 - sum((NTsmooth(1:end/2,1)-OPsmooth(1:end/2,2)).^2)/sum(NTsmooth(1:end/2,1).^2); 
Corr(1,4) = 1 - sum((NTsmooth(1:end/2,1)-POIsmooth(1:end/2,2)).^2)/sum(NTsmooth(1:end/2,1).^2); 
%-------------------------------------------------------

% Corrélation - Entre (NON)
%------------------------------------------------------- 
Corr(2,1) = 1 - sum((ENTsmooth(1:end/2,1)-NTsmooth(1:end/2,2)).^2)/sum(ENTsmooth(1:end/2,1).^2);
Corr(2,3) = 1 - sum((ENTsmooth(1:end/2,1)-OPsmooth(1:end/2,2)).^2)/sum(ENTsmooth(1:end/2,1).^2); 
Corr(2,4) = 1 - sum((ENTsmooth(1:end/2,1)-POIsmooth(1:end/2,2)).^2)/sum(ENTsmooth(1:end/2,1).^2); 
%-------------------------------------------------------

% Corrélation - Opose (NON)
%------------------------------------------------------- 
Corr(3,1) = 1 - sum((OPsmooth(1:end/2,1)-NTsmooth(1:end/2,2)).^2)/sum(OPsmooth(1:end/2,1).^2);
Corr(3,2) = 1 - sum((OPsmooth(1:end/2,1)-ENTsmooth(1:end/2,2)).^2)/sum(OPsmooth(1:end/2,1).^2); 
Corr(3,4) = 1 - sum((OPsmooth(1:end/2,1)-POIsmooth(1:end/2,2)).^2)/sum(OPsmooth(1:end/2,1).^2); 
%-------------------------------------------------------

% Corrélation - Opose (NON)
%------------------------------------------------------- 
Corr(4,1) = 1 - sum((POIsmooth(1:end/2,1)-NTsmooth(1:end/2,2)).^2)/sum(POIsmooth(1:end/2,1).^2);
Corr(4,2) = 1 - sum((POIsmooth(1:end/2,1)-ENTsmooth(1:end/2,2)).^2)/sum(POIsmooth(1:end/2,1).^2); 
Corr(4,3) = 1 - sum((POIsmooth(1:end/2,1)-OPsmooth(1:end/2,2)).^2)/sum(POIsmooth(1:end/2,1).^2); 
%-------------------------------------------------------
Corr = abs(Corr);
disp('--------------------Corrélations-------------------');
disp('          NT(2)      ENT(2)      OP(2)      POI(2)');
disp(['NT(1)   ',num2str(Corr(1,:))]);
disp(['ENT(1)  ',num2str(Corr(2,:))]);
disp(['OP(1)   ',num2str(Corr(3,:))]);
disp(['POI(1)  ',num2str(Corr(4,:))]);
disp('---------------------------------------------------');









