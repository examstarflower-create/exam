function [R] = MINIST_LS_REFORGED(DX,TX01)

X=[DX(:,:,1) ones(5000,1);DX(:,:,2) ones(5000,1)];
y=[ones(5000,1);-ones(5000,1)];
a=gmres(X'*X,X'*y);

for i=1:1000
    if [TX01(i,:) 1]*a >0
        R(i,1)=0;
    else
        R(i,1)=1;
    end
end

end