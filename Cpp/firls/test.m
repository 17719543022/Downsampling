close all; clear; clc;

load('.\h_bak.mat');

h = FIRWithLeastSquares( L-1, [0 2*fc 2*fc 1], [1 1 0 0]);

plot(h_bak, 'o');
hold on;
plot(h, '+');
