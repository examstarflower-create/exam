% HW2 guide code for IJ 1-(c)
% Fill in the areas marked with @
syms x
f = atan(x);  % declare the arctan function
Tf = taylor(f, x, 'order', 10);
error = (f-Tf)^2;
values = double(int(error ,x ,[-1, 1]));