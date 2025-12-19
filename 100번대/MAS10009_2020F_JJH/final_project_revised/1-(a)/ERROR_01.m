function [a] = ERROR_01(R,TY01)

TY01=double(TY01);
X=R-TY01;

for i=1:1000
    if X(i,1)==0
        X(i,1)=1;
    else
        X(i,1)=0;
    end
end

a=(norm(X)^2)/10;

end

