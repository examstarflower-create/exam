function [a, b]=LS_solver(x, y, opt)
% --------- function file "LS_solver.m" --------- %
% input data: x, y and opt
%   if opt=1, linear model (y=a*x+b)
%   if opt=2, exponential model (y=a*exp(b*x))
%   if opt=3, logarithmic model (y=a+b*ln(x))

[m1, n1]=size(x);   [m2, n2]=size(y);   % size of input data
xx=linspace(min(x), max(x), 100);   % xx for plotting the fitting curve.
if (m1~=1)||(m2~=1)||(n1~=n2)       % If the input data size is not proper
    fprintf('Error: Improper input data.\n');   % error message.
elseif (opt==1)||(opt==2)||(opt==3) % option = 1, 2, 3
    figure; plot(x, y, 'o');        % Plotting the given data points
    hold on;                        % Ready to draw the next graph
    if opt == 1  % Linear model
        fprintf('Linear model\n');
        
        A=[x' ones(n1,1)];
        b=y';
        sol=(A'*A)\A'*b;
        
        a=sol(1); b=sol(2);     % fitting constant a and b
        plot(xx, a*xx+b);       % Plot the fitting curve with obtain a and b
        title('Linear model (y=a*x+b)');
    elseif opt == 2 % Exponential model
        fprintf('Exponential model\n');
        
        A=[x' ones(n1,1)];
        b=log(y)';
        sol=(A'*A)\A'*b;
                
        a=exp(sol(2)); b=sol(1);     % fitting constant a and b
        plot(xx, a*exp(b*xx));       % Plot the fitting curve with obtain a and b
        title('Linear model (y=a*e^(b*x))');
    elseif opt == 3 % Logarithmic model
        fprintf('Logarithmic models\n');
        
        A=[log(x)' ones(n1,1)];
        b=y';
        sol=(A'*A)\A'*b;
                
        a=sol(2); b=sol(1);     % fitting constant a and b
        plot(xx, a+b*log(xx));       % Plot the fitting curve with obtain a and b
        title('Linear model (y=a+b*ln(x))');
    end
    hold off;       % no more graph
else                % for invalid [opt]
    fprintf('Error: Improper option value.\n'); % error message
    return;         % Return the process.
end
end