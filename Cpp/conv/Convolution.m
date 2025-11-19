function c = Convolution(a, b)

if nargin < 3
    shape = 'full';
end

% compute as if both inputs are column vectors
% c = conv2(a(:),b(:),shape);
c = conv2(a,b,shape);

% restore orientation
% if shape(1) == 'f' || shape(1) == 'F'  %  shape 'full'
%     if length(a) > length(b)
%         if size(a,1) == 1 %row vector
%             c = c.';
%         end
%     else
%         if size(b,1) == 1 %row vector
%             c = c.';
%         end
%     end
% else
%     if size(a,1) == 1 %row vector
%         c = c.';
%     end
% end
