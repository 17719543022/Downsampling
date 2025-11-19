close all; clear; clc

load('.\yUp_bak.mat');
yUp = UpsampleWithZero(x, p);

plot(yUp, '+'); hold on; plot(yUp_bak, 'o');
