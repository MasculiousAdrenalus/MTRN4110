rgb = double(imread('maze.jpg'));
I = double(rgb2gray(rgb));
imshow(I)
% 
% text(732,501,'Image courtesy of Corel(R)',...
%      'FontSize',7,'HorizontalAlignment','right')
[gmag, gdir] = imgradient(I);
imshow(gmag,[])
title('Gradient Magnitude')

%foo = imoverlay((gmag), rgb, 'red');
%imshow(foo)

% overlay the red boundaries
hold on;
Segout = rgb; 
Segout((gmag)) = 255; 
imshow(Segout)
hold off;