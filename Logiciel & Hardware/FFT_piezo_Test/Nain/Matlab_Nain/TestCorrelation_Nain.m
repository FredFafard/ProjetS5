clc; 
clear all; 
close all;

sheet = 1;
range = 'A1:B1024';

x1 = xlsread('Chapeau1.xlsx',sheet,range);
x2 = xlsread('Chapeau2.xlsx',sheet,range);
x3 = xlsread('Chapeau3.xlsx',sheet,range);

x4 = xlsread('NoTouch1.xlsx',sheet,range');
x5 = xlsread('Barbe1.xlsx',sheet,range);

r1 = 1 - (sum((x1(:,2)-x3(:,2)).*(x1(:,2)-x3(:,2)))/sum(x1(:,2).^2)) %x1 et x3
r2 = 1 - (sum((x2(:,2)-x3(:,2)).*(x2(:,2)-x3(:,2)))/sum(x2(:,2).^2)) %x2 et x3
r3 = 1 - (sum((x2(:,2)-x1(:,2)).*(x2(:,2)-x1(:,2)))/sum(x2(:,2).^2)) %x1 et x2
r4 = 1 - (sum((x1(:,2)-x4(:,2)).*(x1(:,2)-x4(:,2)))/sum(x1(:,2).^2)) %x1 et x4
r5 = 1 - (sum((x2(:,2)-x4(:,2)).*(x2(:,2)-x4(:,2)))/sum(x2(:,2).^2)) %x2 et x4
r6 = 1 - (sum((x3(:,2)-x4(:,2)).*(x3(:,2)-x4(:,2)))/sum(x3(:,2).^2)) %x3 et x4
r7 = 1 - (sum((x1(:,2)-x5(:,2)).*(x1(:,2)-x5(:,2)))/sum(x1(:,2).^2)) %x1 et x5
r8 = 1 - (sum((x2(:,2)-x5(:,2)).*(x2(:,2)-x5(:,2)))/sum(x2(:,2).^2)) %x2 et x5
r9 = 1 - (sum((x3(:,2)-x5(:,2)).*(x3(:,2)-x5(:,2)))/sum(x3(:,2).^2)) %x3 et x5