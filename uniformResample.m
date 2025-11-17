function  [y, h] = uniformResample(x, p, q)

N = 10;
bta = 5;

[p, q] = rat( p/q, 1e-12 );  %--- reduce to lowest terms
% (usually exact, sometimes not; loses at most 1 second every 10^12 seconds)
p = p(1);
q = q(1);

pqmax = max(p,q);
if length(N)>1      % use input filter
    L = length(N);
    h = N;
else                % design filter
    if( N>0 )
        fc = 1/2/pqmax;
        L = 2*N(1)*pqmax + 1;
        h = firls( L-1, [0 2*fc 2*fc 1], [1 1 0 0]).*kaiser(L,bta)' ;
        h = p*h/sum(h);
    else
        L = p;
        h = ones(1,p);
    end
end

Lhalf = (L-1)/2;

if isvector(x)
    Lx = length(x);
else
    Lx = size(x, 1);
end

% Need to delay output so that downsampling by q hits center tap of filter.
nZeroBegin = floor(q-mod(Lhalf,q));
z = zeros(1,nZeroBegin);
h = [z h(:).'];  % ensure that h is a row vector.
Lhalf = Lhalf + nZeroBegin;

% Number of samples removed from beginning of output sequence
% to compensate for delay of linear phase filter:
delay = floor(ceil(Lhalf)/q);

% Need to zero-pad so output length is exactly ceil(Lx*p/q).
nZeroEnd = computeZeroPadLength(Lx,p,q,length(h),delay);
h = [h zeros(1,nZeroEnd)];

% Get rid of trailing and leading data so input and output signals line up
% temporally:
Ly = ceil(Lx*p/q);  % output length
% Ly = floor((Lx-1)*p/q+1);  <-- alternately, to prevent "running-off" the
%                                data (extrapolation)

% ----  HERE'S THE CALL TO UPFIRDN  ----------------------------
y = coder.nullcopy(zeros(Ly,1));

xTrue = [x; zeros(size(h,2),1)];

if isvector(x)
    yUp = upsample(xTrue, p);
    yFir = filter(h, 1, yUp);
    yDn = downsample(yFir, q);
    yVec = [yDn;zeros(size(h,2),1)];
    indV = delay+(1:Ly);
    
    if ~isrow(x)
        indV = indV.';
        yV = yVec(indV);
        y = yV;
    end
end

h = h(nZeroBegin+1:end-nZeroEnd);  % get rid of leading and trailing zeros
% in case filter is output
end

function nZeroEnd = computeZeroPadLength(Lx,p,q,lenH,delay)
% coder.internal.prefer_const(Lx,p,q,lenH,delay);
nZeroEnd = 0;
while ceil( ((Lx-1)*p+lenH+nZeroEnd )/q ) - delay < ceil(Lx*p/q)
    nZeroEnd = nZeroEnd+1;
end
end
% LocalWords:  resamples Ns Fs BTA upsampling ty resampled Krauss LPF Lx xin sy Tmp Dimenion
% LocalWords:  extrap
