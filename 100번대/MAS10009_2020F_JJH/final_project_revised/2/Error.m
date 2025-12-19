function [error] = Error(A,B,CR,tt)

ECR=zeros(200,200,200);
for j=1:200
    for i=1:10
        ECR(:,:,j)=ECR(:,:,j)+A(:,tt(j,i))*B(tt(j,i),:)/10;
    end
end

ECRF=zeros(200,1);
for j=1:200
    for i=1:200
        for k=1:200
            ECRF(j,1)=ECRF(j,1)+ECR(i,k,j)^2;
        end
    end
end

EECRF=zeros(200,1);
for j=1:200
    for i=1:200
        for k=1:200
            EECRF(j,1)=EECRF(j,1)+(CR(i,k,j)-ECR(i,k,j))^2;
        end
    end
end

error=zeros(200,1);
for j=1:200
    error(j,1)=EECRF(j,1)/ECRF(j,1);
end
    
end

