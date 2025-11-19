close all; clear; clc

load('.\yDn_bak.mat');
yDn = DownsampleWithPhaseZero(yFir, q);

plot(yDn, '+'); hold on; plot(yDn_bak, 'o');