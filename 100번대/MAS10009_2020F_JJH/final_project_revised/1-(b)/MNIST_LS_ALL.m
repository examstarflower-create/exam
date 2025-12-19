function [a] = MNIST_LS_ALL(DX,k)

X=[DX(:,:,k) ones(5000,1)];
for j=1:10
    if j~=k
        X=[X;DX(:,:,j) ones(5000,1)];
    end
end

y=[ones(5000,1) ; -ones(45000,1)];

a=gmres(X'*X,X'*y);   

end

