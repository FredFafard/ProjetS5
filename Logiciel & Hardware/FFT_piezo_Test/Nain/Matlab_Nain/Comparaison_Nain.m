close all
clear all
clc

%% Data Loading (XLSX)

sheet = 1;
range = 'A1:B1024';

NoTouch1 = xlsread('NoTouch1.xlsx',sheet,range);
NoTouch2 = xlsread('NoTouch2.xlsx',sheet,range);
Barbe1 = xlsread('Barbe1.xlsx',sheet,range);
Barbe2 = xlsread('Barbe2.xlsx',sheet,range);
Barbe3 = xlsread('Barbe3.xlsx',sheet,range);
Chapeau1 = xlsread('Chapeau1.xlsx',sheet,range);
Chapeau2 = xlsread('Chapeau2.xlsx',sheet,range);
Chapeau3 = xlsread('Chapeau3.xlsx',sheet,range);
Poche1 = xlsread('Poche1.xlsx',sheet,range);
Poche2 = xlsread('Poche2.xlsx',sheet,range);
Poche3 = xlsread('Poche3.xlsx',sheet,range);

%% Plots

figure
plot(NoTouch1(:,1),smooth(NoTouch1(:,2),10));
hold on
plot(NoTouch2(:,1),smooth(NoTouch2(:,2),10));
legend('NoTouch1','NoTouch2');
title('FFT Nain - NoTouch');

figure
plot(Barbe1(:,1),smooth(Barbe1(:,2),10));
hold on;
plot(Barbe2(:,1),smooth(Barbe2(:,2),10));
plot(Barbe3(:,1),smooth(Barbe3(:,2),10));
legend('Barbe1','Barbe2','Barbe3')
title('FFT Nain - Barbe');

figure
plot(Chapeau1(:,1),smooth(Chapeau1(:,2),10));
hold on;
plot(Chapeau2(:,1),smooth(Chapeau2(:,2),10));
plot(Chapeau3(:,1),smooth(Chapeau3(:,2),10));
legend('Chapeau1','Chapeau2','Chapeau3')
title('FFT Nain - Chapeau');

figure
plot(Poche1(:,1),smooth(Poche1(:,2),10));
hold on;
plot(Poche2(:,1),smooth(Poche2(:,2),10));
plot(Poche3(:,1),smooth(Poche3(:,2),10));
legend('Poche1','Poche2','Poche3')
title('FFT Nain - Poche');


