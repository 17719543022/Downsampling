close all; clear; clc;

fileID = fopen('x_rect.txt', 'r');
C = textscan(fileID, '%f');
x = C{:};
fclose(fileID);

ups = 7;
dns = 10;

[y, by] = uniformResample(x, ups, dns);

