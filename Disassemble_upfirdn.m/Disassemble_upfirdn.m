close all; clear; clc;

load('.\matlab.mat');
yVec = upfirdn(x,h,p,q);

yUp = upsample(x, p);
yConv = conv(h, yUp);
yDn = downsample(yConv, q);

plot(yDn,'+'); hold on; plot(yVec,'o');