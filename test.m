close all; clear; clc;

fileID = fopen('x_rect.txt', 'r');
C = textscan(fileID, '%f');
x = C{:};
fclose(fileID);

mean_x = mean(x);
periods_original = 0;
for i = 1 : length(x) - 1;
    if ((x(i) < mean_x) && (x(i + 1) >= mean_x))
        periods_original = periods_original + 1;
    end
end

ups = 7;
dns = 10;

[y, by] = resample(x,ups,dns);
mean_y = mean(y);
periods_resampled = 0;
for i = 1 : length(y) - 1;
    if ((y(i) < mean_y) && (y(i + 1) >= mean_y))
        periods_resampled = periods_resampled + 1;
    end
end
