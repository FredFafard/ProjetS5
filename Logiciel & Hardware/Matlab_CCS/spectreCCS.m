function [ Xmag, f ] = spectreCCS( filename )
% Lire le fichier Excel de données CCS contenant la séquence "Re[X], Im[X],
% Re[X], Im[X],..." dont les composantes fréquentielles complexes, X,
% sont en ordre digit-reversed
s = xlsread(filename);
Datafloat = s(:, 1);
% Convertir la séquence en tableau Matlab de valeurs complexes
X = zeros(1, length(Datafloat)/2);
N = length(X);
for i = 1:N
X(i) = complex(Datafloat(2*(i-1) + 1), Datafloat(2*(i-1) + 2));
end
% Remettre les composantes fréquentielles dans l'ordre
X = digitrevorder(X, 2);
% Mettre les fréquences négatives en premier, pour que la DC se retrouve
% au milieu du spectre (Matlab présente par défaut le spectre
% sur l'intervalle [0..fe] au lieu de [-fe/2..fe/2]
X = fftshift(X);
% Calcul du vecteur des fréquences correspondantes
fe = 96000;
f = -fe/2:fe/N:fe/2-fe/N;
% Graphique de l'amplitude des composantes fréquentielles
Xmag = abs(X);
stem(f, Xmag);
grid
xlabel('Fréquence (Hz)')
ylabel('|X(f)|')
title(sprintf('Spectre d''amplitude |X(f)| (fe = %d Hz)', fe))
end