function [CR] = Norm(A,B,tt,p)

s=10;
CR=zeros(200,200,200);

for i=1:200
    for j=1:10
        CR(:,:,i)=CR(:,:,i)+A(:,tt(i,j))*B(tt(i,j),:)/(s*p(tt(i,j)));
    end
end

end

