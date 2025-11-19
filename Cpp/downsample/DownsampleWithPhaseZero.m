function y = DownsampleWithPhaseZero(x,N)
    dim = 1;
    sizeX = size(x);
    
    nshifts = dim - 1;
    lshift = circshift(sizeX,-nshifts);
    ytemp = reshape(x,lshift);
    
    % Downsample on the leading non-singleton dimension
    ytemp1 = ytemp(1:N:end,:);
    
    % Update the new downsampled dimension
    sizeX(1,nshifts+1) = size(ytemp1,1);
    
    % Restore to the original N-D dimensions
    y = reshape(ytemp1,sizeX);
end

% [EOF] 

% LocalWords:  downsamples th lockdown downsampled
