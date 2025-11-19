close all; clear; clc

load('.\yFir_bak.mat');
h = h.';
yFir = Convolution(h, yUp);

plot(yFir, '+'); hold on; plot(yFir_bak, 'o');