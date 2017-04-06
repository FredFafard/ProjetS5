clc; clear all; close all;

%Correlation selon nos APP:
% Document D6-9-1 page 230
% sum(x1(:,2)*x2(:,2))

% Correlation utilisee (Correlation normalisee sur une valeur de 1):
%  1- sum((X1(:,2)-X2(:,2))^2)/sum(X1(:,2)^2)

%Les (:,2) sont pour aller chercher les valeurs dans la deuxieme colonne.
%La premiere colonne sont les index


x1 = xlsread('Bas1');
x2 = xlsread('Bas2');
x3 = xlsread('Bas3');

x4 = xlsread('NoTouch');
x5 = xlsread('Haut');
[m,n] = size(x1);
xzeros = zeros(m,1);
xzeros(:,2) = xzeros(:,1);
xzeros(:,1) = x1(:,1); %Pour ecrire les index

%Resultat de correlation avec xcorr

xcorr1 = xcorr(x1(:,2),x1(:,2));
xcorr2 = xcorr(x1(:,2),x3(:,2));
xcorr1(1006);
xcorr2(1006);

%Resultats de correlation a la main
r(1) = 1 - (sum((x1(:,2)-x3(:,2)).*(x1(:,2)-x3(:,2)))/sum(x1(:,2).^2)); %Bas1 et Bas3
r(2) = 1 - (sum((x2(:,2)-x3(:,2)).*(x2(:,2)-x3(:,2)))/sum(x2(:,2).^2)); %Bas2 et Bas3
r(3) = 1 - (sum((x2(:,2)-x1(:,2)).*(x2(:,2)-x1(:,2)))/sum(x2(:,2).^2)); %Bas1 et Bas2
r(4) = 1 - (sum((x1(:,2)-x4(:,2)).*(x1(:,2)-x4(:,2)))/sum(x1(:,2).^2)); %Bas1 et Notouch
r(5) = 1 - (sum((x2(:,2)-x4(:,2)).*(x2(:,2)-x4(:,2)))/sum(x2(:,2).^2)); %Bas2 et Notouch
r(6) = 1 - (sum((x3(:,2)-x4(:,2)).*(x3(:,2)-x4(:,2)))/sum(x3(:,2).^2)); %Bas3 et notouch
r(7) = 1 - (sum((x1(:,2)-x5(:,2)).*(x1(:,2)-x5(:,2)))/sum(x1(:,2).^2)); %Bas1 et Haut
r(8) = 1 - (sum((x2(:,2)-x5(:,2)).*(x2(:,2)-x5(:,2)))/sum(x2(:,2).^2)); %Bas2 et Haut
r(9) = 1 - (sum((x3(:,2)-x5(:,2)).*(x3(:,2)-x5(:,2)))/sum(x3(:,2).^2)); %Bas3 et Haut
r(10) = 1 - (sum((x1(:,2)-x1(:,2)).*(x1(:,2)-x1(:,2)))/sum(x1(:,2).^2)); %correlation parfaite de 1
r(11) = 1 - (sum((x1(:,2)-xzeros(:,2)).*(x1(:,2)-xzeros(:,2)))/sum(x1(:,2).^2)); %correlation nulle (avec zero)

x6 = [2 0 1 4 0 1 3 4];
x7 = [3 4 1];

xcorr(x6,x7);
m = length(x6);
n = length(x7);
for k=1:1:m-1
    x7(n+k) = 0;
end
x6(n:n+m-1) = x6;
for k=1:1:n-1
    x6(k) = 0;
end
for k=1:1:m+n-1
    xcorrmanuel(k) = sum(x6((m-k+n):end).*x7(1:k));
end
%Correlation avec filtre a coeff egaux
%%filtrage
figure()
ordreSmooth = 200;
xx1 = smooth(x1(:,2),ordreSmooth);
xx2 = smooth(x2(:,2),ordreSmooth);
xx3 = smooth(x3(:,2),ordreSmooth);
xx4 = smooth(x4(:,2),ordreSmooth);
xx5 = smooth(x5(:,2),ordreSmooth);

hold on;
plot(xx1);
plot(xx2);
plot(xx3);
plot(xx4);
plot(xx5);
legend('xx1','xx2','xx3','xx4','xx5')

%%correlations
rf(1) = 1 - (sum((xx1-xx3).*(xx1-xx3))/sum(xx1.^2)); %Bas1 et Bas3
rf(2) = 1 - (sum((xx2-xx3).*(xx2-xx3))/sum(xx2.^2)); %Bas2 et Bas3
rf(3) = 1 - (sum((xx2-xx1).*(xx2-xx1))/sum(xx2.^2)); %Bas1 et Bas2
rf(4) = 1 - (sum((xx1-xx4).*(xx1-xx4))/sum(xx1.^2)); %Bas1 et Notouch
rf(5) = 1 - (sum((xx2-xx4).*(xx2-xx4))/sum(xx2.^2)); %Bas2 et Notouch
rf(6) = 1 - (sum((xx3-xx4).*(xx3-xx4))/sum(xx3.^2)); %Bas3 et notouch
rf(7) = 1 - (sum((xx1-xx5).*(xx1-xx5))/sum(xx1.^2)); %Bas1 et Haut
rf(8) = 1 - (sum((xx2-xx5).*(xx2-xx5))/sum(xx2.^2)); %Bas2 et Haut
rf(9) = 1 - (sum((xx3-xx5).*(xx3-xx5))/sum(xx3.^2)); %Bas3 et Haut

%%Correlation avec decimation

dec = 50;
rd(1) = 1 - (sum((xx1(1:dec:end)-xx3(1:dec:end)).*(xx1(1:dec:end)-xx3(1:dec:end)))/sum(xx1(1:dec:end).^2)); %Bas1 et Bas3
rd(2) = 1 - (sum((xx2(1:dec:end)-xx3(1:dec:end)).*(xx2(1:dec:end)-xx3(1:dec:end)))/sum(xx2(1:dec:end).^2)); %Bas2 et Bas3
rd(3) = 1 - (sum((xx2(1:dec:end)-xx1(1:dec:end)).*(xx2(1:dec:end)-xx1(1:dec:end)))/sum(xx2(1:dec:end).^2)); %Bas1 et Bas2
rd(4) = 1 - (sum((xx1(1:dec:end)-xx4(1:dec:end)).*(xx1(1:dec:end)-xx4(1:dec:end)))/sum(xx1(1:dec:end).^2)); %Bas1 et Notouch
rd(5) = 1 - (sum((xx2(1:dec:end)-xx4(1:dec:end)).*(xx2(1:dec:end)-xx4(1:dec:end)))/sum(xx2(1:dec:end).^2)); %Bas2 et Notouch
rd(6) = 1 - (sum((xx3(1:dec:end)-xx4(1:dec:end)).*(xx3(1:dec:end)-xx4(1:dec:end)))/sum(xx3(1:dec:end).^2)); %Bas3 et notouch
rd(7) = 1 - (sum((xx1(1:dec:end)-xx5(1:dec:end)).*(xx1(1:dec:end)-xx5(1:dec:end)))/sum(xx1(1:dec:end).^2)); %Bas1 et Haut
rd(8) = 1 - (sum((xx2(1:dec:end)-xx5(1:dec:end)).*(xx2(1:dec:end)-xx5(1:dec:end)))/sum(xx2(1:dec:end).^2)); %Bas2 et Haut
rd(9) = 1 - (sum((xx3(1:dec:end)-xx5(1:dec:end)).*(xx3(1:dec:end)-xx5(1:dec:end)))/sum(xx3(1:dec:end).^2)); %Bas3 et Haut