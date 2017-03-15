function [ Xmag, f ] = spectreCCS( filename )
% Lire le fichier Excel de donn�es CCS contenant la s�quence "Re[X], Im[X],
% Re[X], Im[X],..." dont les composantes fr�quentielles complexes, X,
% sont en ordre digit-reversed
s = xlsread(filename);
Datafloat = s(:, 1);
% Convertir la s�quence en tableau Matlab de valeurs complexes
X = zeros(1, length(Datafloat)/2);
N = length(X);
for i = 1:N
X(i) = complex(Datafloat(2*(i-1) + 1), Datafloat(2*(i-1) + 2));
end
% Remettre les composantes fr�quentielles dans l'ordre
X = digitrevorder(X, 2);
% Mettre les fr�quences n�gatives en premier, pour que la DC se retrouve
% au milieu du spectre (Matlab pr�sente par d�faut le spectre
% sur l'intervalle [0..fe] au lieu de [-fe/2..fe/2]
X = fftshift(X);
% Calcul du vecteur des fr�quences correspondantes
fe = 96000;
f = -fe/2:fe/N:fe/2-fe/N;
% Graphique de l'amplitude des composantes fr�quentielles
Xmag = abs(X);
stem(f, Xmag);
grid
xlabel('Fr�quence (Hz)')
ylabel('|X(f)|')
title(sprintf('Spectre d''amplitude |X(f)| (fe = %d Hz)', fe))
end