function [N1, N2] = HW2_2a_20209999(T)
% HW2  guide code for IJ 2-(a)
% input T is scalar
% output N1 and N2 are scalar 
% Fill in the areas marked with @

e = exp(1);
%% For N1
% initial staring point k=0
N1 = 0;
approximation1 = 1;
error1 = abs(e - approximation1);
% Untile the condition is satisfied, N1 grows up 1 by 1
while error1 >= T
   N1 = N1 + 1;
   syms n;
   approximation1 = symsum(1/factorial(n),n,0,N1);   % use the command "factorial(n)" to compute the n!
   error1 =  abs(e - approximation1);  
end

%% For N2
% initial staring point k=0
N2 = 0;
approximation2 = (1 + 1/N2)^N2;
error2 = abs(e - approximation2);
% Untile the condition is satisfied, N2 grows up 1 by 1
while error2 >= T
   N2 = N2 + 1;
   approximation2 = (1+1/N2)^N2;
   error2 = abs(e - approximation2);   
end

end