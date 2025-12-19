function [a] = MINIST_LS(X1,X2)

X=[X1 ones(5000,1);X2 ones(5000,1)];
y=[ones(5000,1);-ones(5000,1)];
a=gmres(X'*X,X'*y);

end