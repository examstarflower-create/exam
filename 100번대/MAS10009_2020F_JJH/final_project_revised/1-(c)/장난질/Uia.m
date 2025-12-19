function [R] = Uia(DX,uia,d)

T=ones(10000,10);
for k=1:10
    coeff=pca(DX(:,:,k));
    W=coeff(:,1:d);
    A=W*W';
    T(1,k)=norm(A*uia(1,:)');
end

[x1,x2]=max(T(1,:));
R(1,1)=x2-1;

end

