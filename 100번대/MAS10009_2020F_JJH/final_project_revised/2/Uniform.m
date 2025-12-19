function [CR] = Uniform(A,B,tt)

p=1/1000;
s=10;
CR=zeros(200,200,200);

for i=1:200
    for j=1:10
        CR(:,:,i)=CR(:,:,i)+A(:,tt(i,j))*B(tt(i,j),:)/(s*p);
    end
end

end

