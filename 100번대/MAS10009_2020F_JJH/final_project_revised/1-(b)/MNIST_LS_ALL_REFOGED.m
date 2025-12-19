function [R] = MNIST_LS_ALL_REFOGED(DX,TX)


for k=1:10
    X=[DX(:,:,k) ones(5000,1)];
    for j=1:10
        if j~=k
            X=[X;DX(:,:,j) ones(5000,1)];
        end
    end
    y=[ones(5000,1) ; -ones(45000,1)];
    a(:,k)=gmres(X'*X,X'*y);   
end

for i=1:10000
    [x1,x2]=max([TX(i,:) 1]*a);
    R(i,1)=x2-1;
end

end

