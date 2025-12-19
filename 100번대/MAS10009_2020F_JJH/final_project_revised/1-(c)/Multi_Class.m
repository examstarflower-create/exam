function [R] = Multi_Class(DX,TX,d)

T=ones(10000,10);
R=ones(10000,1);
for k=1:10
    coeff=pca(DX(:,:,k));
    W=coeff(:,1:d);
    A=W*W';
    for j=1:10000
        T(j,k)=norm(A*TX(j,:)');
    end
end

for i=1:10000
    [x1,x2]=max(T(i,:));
    R(i,1)=x2-1;
end

end

