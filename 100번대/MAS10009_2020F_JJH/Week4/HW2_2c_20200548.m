function [D] = HW2_2c_20209999(A)
% HW2  guide code for IJ 2-(c)
% input) A is n by n square matrix.
% output) D is a scalar which is a determinant of A.
% Fill in the areas marked with @

[m, n] = size(A);
D = 0;
if m ~= n
    fprintf('Error : Matrix is not a square\n');
else
    if m == 1
        D = A;
    elseif m == 2
        D = A(1,1)*A(2,2)-A(1,2)*A(2,1);
    else
        for i = 1:m
            D = D + (-1)^(i+1)*A(i,1)*HW2_2c_20209999(A([1:i-1,i+1:m],2:m));
        end
    end
end

end