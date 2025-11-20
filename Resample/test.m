close all; clear; clc;

fileID = fopen('FP1.txt', 'r');
C = textscan(fileID, '%f');
x = C{:};
fclose(fileID);

ups = 7;
dns = 10;

[y, by] = resample(x, ups, dns);


