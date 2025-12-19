clear;
clc;
% Fill out the @ area
%------------------------------------------------------------------------%

image_list = {'bus.jpg', 'man.jpg', 'apartment.jpg'};
ft = 20;
figure(2),clf(2)
for i=1:3
    % Read the image, and convert to gray scale
    I = rgb2gray(imread(strcat(image_list{i})));
    % Convert image values from [0, 255] to [0, 1]
    % (built-in function "svd" works for [0, 1])
    I = im2double(I);
    % Iimage size
    [a,b] = size(I);
    % alpha is the first singular value of matrix G (every component are 0.5)
    % Compute alpha value without using "svd" funciton. depends on image size
    alpha = sqrt(eigs(0.25*a*ones(b),1));
    [U, S, V] = svd(I); 
    ratio = alpha / svds(S,1);
    subplot(2, 3, i),imshow(I),title(sprintf('Image %s', image_list{i}))
    set(gca, 'fontsize', ft)
    
    subplot(2, 3, i+3)
    imshow(ratio*I),title('Equalized image') 
    set(gca, 'fontsize', ft)
end