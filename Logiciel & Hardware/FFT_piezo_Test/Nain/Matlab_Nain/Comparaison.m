close all
clear all
clc

%% Data Loading (XLSX)

sheet = 1;
range = 'A1:B1006';

NoTouch = xlsread('NoTouch.xlsx',sheet,range);
Bas1 = xlsread('Bas1.xlsx',sheet,range);
Bas2 = xlsread('Bas2.xlsx',sheet,range);
Bas3 = xlsread('Bas3.xlsx',sheet,range);
Bouchon = xlsread('Bouchon.xlsx',sheet,range);
Haut = xlsread('Haut.xlsx',sheet,range);

%% Plots

plot(NoTouch(:,1),smooth(NoTouch(:,2),10))
hold on
plot(Bas1(:,1),smooth(Bas1(:,2),10))
plot(Bas2(:,1),smooth(Bas2(:,2),10))
plot(Bas3(:,1),smooth(Bas3(:,2),10))
plot(Haut(:,1),smooth(Haut(:,2),10))
%plot(Bouchon(:,1),smooth(Bouchon(:,2),10))
legend('No Touch','Bas 1 ','Bas 2','Bas 3','Haut')
title('Ensemble des courbes')






% figure()
% plot(Bas1(:,1),smooth(Bas1(:,2),5))
% hold on
% plot(Bas2(:,1),smooth(Bas2(:,2),5))
% plot(Bas3(:,1),smooth(Bas3(:,2),5))



