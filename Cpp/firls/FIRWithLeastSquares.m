function h= FIRWithLeastSquares(N,freq,amp)

% Cast to enforce precision rules N, F and A
N = double(N(1));
freq = double(freq);
amp = double(amp);

freq_length = length(freq);

weight = ones(floor(freq_length/2),1);

% validate ftype
filtype = 0;

% filter length
N = N + 1;

max_freq = max(freq,[],2);
min_freq = min(freq,[],2);

% check validity of input F and A
if (max_freq(1,1) > 1) || (min_freq(1,1) < 0)
    h = zeros(1,N);
    return
end

F = freq(:)/2;
A = amp(:);

wt = abs(sqrt(complex(weight)));

% find the order
L = (N(1) - 1)/2;

% odd order
Nodd = (rem(N,2) == 1);

% initialize b0
b0 = 0;

% Type I linear phase FIR
if filtype == 0
    % Basis vectors are cos(2*pi*m*f)
    if ~Nodd
        m = (0:L)+.5;   % type II
    else
        m = (0:L);      % type I
    end
    k = m';
    
    if Nodd
        k = k(2:length(k));
        b0 = 0;       %  first entry must be handled separately (where k(1)=0)
    end
    
    % preallocate b matrix
    b = zeros(size(k));
    
    for s = 1:2:length(F)
        m_s = ( A(s+1)-A(s) )/( F(s+1)-F(s) );    %  slope
        b1 = A(s) - m_s * F(s);                   %  y-intercept
        if Nodd
            b0 = b0 + (b1*(F(s+1)-F(s)) + m_s/2*(F(s+1)*F(s+1)-F(s)*F(s)))...
                * (wt((s+1)/2)^2) ;
        end
        b = b + (m_s/(4*pi*pi)*(cos(2*pi*k*F(s+1))-cos(2*pi*k*F(s)))./(k.*k))...
            * (wt((s+1)/2)^2);
        b = b + (F(s+1)*(m_s*F(s+1)+b1)*sinc(2*k*F(s+1)) ...
            - F(s)*(m_s*F(s)+b1)*sinc(2*k*F(s))) ...
            * (wt((s+1)/2)^2);
    end
    if Nodd
        b = [b0; b];
    end
    
    a = ((wt(1)^2)*4*b);
    if Nodd
        a(1) = a(1)/2;
    end
    
    if Nodd
        h = [a(L+1:-1:2)/2; a(1); a(2:L+1)/2]';
    else
        h = .5*[flipud(a); a]';
    end
end

end


