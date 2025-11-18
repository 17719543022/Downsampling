function w = KaiserWindow(n_est,bta)

% [nn,w,trivialwin] = check_order(n_est);
if n_est == floor(n_est)
    nn = n_est;
else
    nn = round(n_est);
end

% special cases: N is 0 0r 1
w = 0;
trivialwin = 0;
if nn == 0 
    w = zeros(0,1);       % Empty matrix: 0-by-1
    trivialwin = 1;
elseif nn == 1
    w = 1;
    trivialwin = 1;
end

if trivialwin, return, end

nw = round(nn);
bes = abs(besseli(0,bta));
odd = rem(nw,2);
xind = (nw-1)^2;
n = fix((nw+1)/2);
xi = (0:n-1) + .5*(1-odd);
xi = 4*xi.^2;
w = besseli(0,bta*sqrt(1-xi/xind))/bes;
w = abs([w(n:-1:odd+1) w])';

    
% [EOF] kaiser.m
