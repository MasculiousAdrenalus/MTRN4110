I = imread("maze1.png");

% I = rgb2gray(I);
[BW,maskedRGBImage] = createMask(I);
% I = bwareafilt()
% BW = imfill(BW, 'holes');
element = strel('disk', 14);
BW = imclose(BW, element);
% imGray = 255*uint8(BW);
BW = bwmorph(BW, 'skel', Inf);
BW = bwmorph(BW, 'spur', 20);
imshowpair(I, BW, 'montage');
