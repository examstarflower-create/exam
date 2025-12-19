clear;
clc;
% Fill out the @ area
%------------------------------------------------------------------------%

% Read the image, and convert to gray scale
I = rgb2gray(imread('kaist.jpg'));
% Convert image values from [0, 255] to [0, 1] 
% (built-in function "svd" works for [0, 1])
I = im2double(I);   
% Image size
[a, b] = size(I);
% Singular value decomposition
[U, S, V] = svd(I); 
ft = 15;
figure(1), clf(1)
% Draw the original image
subplot(2, 4, 1),imshow(I), title(sprintf('Original image %d x %d', a,b))
set(gca, 'fontsize', ft)
% Plot the Singular values
subplot(2, 4, 2),plot(S, 'linewidth',2), title('Singular values')
set(gca, 'fontsize', ft), xlim([0, a])
r = 20;
for k=1:6
    subplot(2, 4, k+2),
    % r*k rank approximation
    Approximation = U(:,1:r*k)*S(1:r*k,1:r*k)*V(:,1:r*k)';
    imshow(Approximation)
    title(sprintf('Rank %d approximation',r*k))
    set(gca, 'fontsize', ft)
end