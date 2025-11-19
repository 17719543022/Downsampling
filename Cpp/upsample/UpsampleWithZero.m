function y = UpsampleWithZero(x,N)

yCol = cast(zeros(numel(x)*N,1),'like',x);    

% Perform the upsample
yCol(1:N:end,1) = x;

y = yCol;

% [EOF]
