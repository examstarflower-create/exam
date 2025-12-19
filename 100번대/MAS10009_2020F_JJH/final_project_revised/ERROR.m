function [a] = ERROR(R,TY)

TY=double(TY);
X=R-TY;

for i=1:10000
    if X(i,1)==0
        X(i,1)=1;
    else
        X(i,1)=0;
    end
end

a=(norm(X)^2)/100;

end

