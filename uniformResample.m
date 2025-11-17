function  [y, h] = uniformResample(x, isDimValSet, Dim, dimIn, xTrue, p, q)

% codegen inference
if nargin < 7
    q = 1;
end

% % number of numeric arguments in varargin
% nNum = length(varargin);
N = 10;
bta = 5;

% % parse N and beta
% if ~isempty(varargin)
%     if ((nNum >= 2 && isDimValSet)|| (nNum >= 1 && ~isDimValSet))&& ~isempty(varargin{1})
%         N = varargin{1};
%     end
%     if ((nNum >= 3 && isDimValSet)|| (nNum >= 2 && ~isDimValSet))&& ~isempty(varargin{2})
%         bta = varargin{2};
%     end
% end

validateattributes(x, {'numeric'},{},'resample','X',1);
validateResampleRatio(p, q);

[p, q] = rat( p/q, 1e-12 );  %--- reduce to lowest terms
% (usually exact, sometimes not; loses at most 1 second every 10^12 seconds)
p = p(1);
q = q(1);

if (p == 1) && (q == 1)
    yTmp = x;
    if (numel(x) == numel(xTrue))
        y = ipermute(yTmp,dimIn);
        y = reshape(y,size(xTrue));
    else
        y = reshape(yTmp,size(x));
        y = ipermute(y,dimIn);
    end
    h = 1;
    return
end

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
szx = size(x);
sy = szx;
if isrow(x)
    sy(2) = Ly;
else
    sy(1) = Ly;
end

% numel in the 3rd dimension, when nD array is collapsed to a 3D-array
n2D = 1;
if numel(szx) >= 3
    n2D = prod(szx(3:length(szx)),'all');
end

% syTrue is the desired output size for uniform resample
sxTrue = size(xTrue);
syTrue = sxTrue;

if isvector(xTrue)
    if isrow(xTrue)
        syTrue(2) = Ly;
    else
        syTrue(1) = Ly;
    end
else
    syTrue(Dim) = Ly;
end

% ----  HERE'S THE CALL TO UPFIRDN  ----------------------------
if isreal(x)
    y = coder.nullcopy(zeros(syTrue));
else
    y = coder.nullcopy(complex(ones(syTrue),ones(syTrue)));
end

if isvector(x)
    yVec = upfirdn(x,h,p,q);
    indV = delay+(1:Ly);
    
    if ~isrow(x)
        indV = indV.';
        yV = yVec(indV);
        y = yV;
    else
        yV = yVec(indV);
        yV1 = yV.';
        if (numel(x) == numel(xTrue))
            y = reshape(yV1,syTrue);       % % uniform resample
        else
            y = reshape(yV1,sy);           % % non-uniform resample
        end
    end
elseif ~isvector(x) && (numel(szx)==2)
    ymat = upfirdn(x,h,p,q);
    indM = delay+(1:Ly);
    indM = indM.';
    yM=ymat(indM,:);
    
    if (numel(ymat) == prod(syTrue))
        yRshp = ipermute(yM,dimIn);
        y = reshape(yRshp,syTrue);
    else
        y = ipermute(yM,dimIn);       % % non-uniform resample
    end
end

% input is an nD-array
if (numel(szx)> 2)
    syTmp = [sy(1:2) n2D];
    if isreal(x)
        yTmp = coder.nullcopy(zeros(syTmp));
    else
        yTmp = coder.nullcopy(complex(ones(syTmp),ones(syTmp)));
    end
    
    for ii = 1:n2D
        xTmp = x(:,:,ii);
        
        if (szx(1) == 1)
            % if xTmp is a row vector and user sets Dimension to the singleton dimension
            if isreal(x)
                yTmp1 = coder.nullcopy(zeros(sy(1),sy(2)));
            else
                yTmp1 = coder.nullcopy(complex(ones(sy(1),sy(2)),ones(sy(1),sy(2))));
            end
            
            for jj = 1: szx(2)
                xTmp1 = x(1,jj,ii);
                yTmp2 = upfirdn(xTmp1,h,p,q).';
                indTmp = (1:Ly)+delay;
                indTmp = indTmp.';
                y1 = yTmp2(indTmp,:);
                yTmp1(1:Ly,jj) = y1;
            end
            yTmp(:,:,ii) = yTmp1;
            
        else
            yTmp1 = upfirdn(xTmp,h,p,q);
            ind = (1:Ly)+delay;
            ind = ind.';
            y1 = yTmp1(ind,:);
            yTmp(:,:,ii) = y1;
        end
    end
    
    if (numel(syTmp) ~= numel(sy))      % nonuniform resample
        yRshp = reshape(yTmp,sy);       % converting 3D output to nD
        y1 = ipermute(yRshp,dimIn);      % returns to the original orientation
        y = reshape(y1,syTrue);          % ensures the correct output size
    else
        y1 = ipermute(yTmp,dimIn);
        y = reshape(y1,syTrue);
    end
end

h = h(nZeroBegin+1:end-nZeroEnd);  % get rid of leading and trailing zeros
% in case filter is output
end
%-------------------------------------------------------------------------
function validateResampleRatio(p, q)
validateattributes(p, {'numeric'},{'integer','positive','finite', ...
    'scalar'},'resample','P');
validateattributes(q, {'numeric'},{'integer','positive','finite', ...
    'scalar'},'resample','Q');
end
%-------------------------------------------------------------------------
function [method] = getInterpMethod(varargin)

method = '';
supportedMethods = {'linear','pchip','spline'};
for i=1:numel(varargin)
    if ischar(varargin{i})|| isStringScalar(varargin{i})
        if (strncmpi(varargin{i},'Dimension',3))
            break;
        else
            method = validatestring(varargin{i},supportedMethods,'resample','METHOD');
        end
    end
end
end

%-------------------------------------------------------------------------
function [xOut, dimPerm] = orientToNdim (x, nDim)
sX = size(x);

% error if Dimenion is larger than input size
coder.internal.assert(~(~isscalar(x) && (numel(sX)< nDim)),...
    'signal:resample:DimensionMismatch');

trueDim = 1:numel(sX);
dimPerm = coder.nullcopy(trueDim);

if isvector(x)
    xOut = x;
    dimPerm = trueDim;
elseif (numel(sX) >= 2)
    % rotate the input according to Dimension
    if (nDim ~= 1)
        [~,inds] = sort(sX,'descend');
        i1 = (inds ~= nDim);
        dimPerm(1) = nDim;
        dimPerm(2:end) = inds(i1);
        xOut = permute(x, dimPerm);
    else
        xOut = x;
        dimPerm = trueDim;
    end
end
end
%-------------------------------------------------------------------------
function [dim,m,isDimValSet] = dimParser(varargin)

% By default, set nDim to the first non-singleton dimension
sx = size(varargin{1});
dim = 1;

if numel(sx) > 1 && ~isscalar(varargin{1})
    nonSingDim = find(sx>1);
    dim = nonSingDim(1);
end

% flags to set
dimSet = false;
isDimValSet = false;
possibleStrings = {'linear','pchip','spline','Dimension'};

coder.unroll;
for argIndex = 1:length(varargin)
    inputVal = varargin{argIndex};
    if ischar(inputVal) || isStringScalar(inputVal)
        str = validatestring(inputVal,possibleStrings,'resample');
        switch str
            case 'Dimension'
                coder.internal.assert(~dimSet, ...
                    'signal:resample:MultipleNameEntered');
                dimSet = true;
        end
    elseif isnumeric(inputVal)
        if (dimSet) && (argIndex == length(varargin))
            validateattributes(inputVal,{'numeric'},...
                {'scalar','finite','real','positive'},'resample','Dim');
            dim = double(inputVal);
            isDimValSet = true;
        end
    end
end

coder.internal.assert(~(dimSet && ~isDimValSet),...
    'signal:resample:NameValueExpected');

n = coder.const(countNumericInputs(varargin{:}));

% the number of numeric arguments in varargin after removing Dimension
if dimSet && isDimValSet
    m = n-1;                            % user specified Dim
else
    m = n;
end

end

function n = countNumericInputs(varargin)
n = 0;
coder.unroll;
for k = 1:nargin
    if isnumeric(varargin{k}) || isdatetime(varargin{k})
        n = n + 1;
    end
end
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
