clc; clear all; close all;

x1 = xlsread('C:\Users\gaud1910\Desktop\Bas1')
x2 = xlsread('C:\Users\gaud1910\Desktop\Bas2')
x3 = xlsread('C:\Users\gaud1910\Desktop\Bas3')

x4 = xlsread('C:\Users\gaud1910\Desktop\NoTouch')
x5 = xlsread('C:\Users\gaud1910\Desktop\Haut')

r1 = 1 - (sum((x1(:,2)-x3(:,2)).*(x1(:,2)-x3(:,2)))/sum(x1(:,2).^2)) %Bas1 et Bas3
r2 = 1 - (sum((x2(:,2)-x3(:,2)).*(x2(:,2)-x3(:,2)))/sum(x2(:,2).^2)) %Bas2 et Bas3
r3 = 1 - (sum((x2(:,2)-x1(:,2)).*(x2(:,2)-x1(:,2)))/sum(x2(:,2).^2)) %Bas1 et Bas2
r4 = 1 - (sum((x1(:,2)-x4(:,2)).*(x1(:,2)-x4(:,2)))/sum(x1(:,2).^2)) %Bas1 et Notouch
r5 = 1 - (sum((x2(:,2)-x4(:,2)).*(x2(:,2)-x4(:,2)))/sum(x2(:,2).^2)) %Bas2 et Notouch
r6 = 1 - (sum((x3(:,2)-x4(:,2)).*(x3(:,2)-x4(:,2)))/sum(x3(:,2).^2)) %Bas3 et notouch
r7 = 1 - (sum((x1(:,2)-x5(:,2)).*(x1(:,2)-x5(:,2)))/sum(x1(:,2).^2)) %Bas1 et Haut
r8 = 1 - (sum((x2(:,2)-x5(:,2)).*(x2(:,2)-x5(:,2)))/sum(x2(:,2).^2)) %Bas2 et Haut
r9 = 1 - (sum((x3(:,2)-x5(:,2)).*(x3(:,2)-x5(:,2)))/sum(x3(:,2).^2)) %Bas3 et Haut