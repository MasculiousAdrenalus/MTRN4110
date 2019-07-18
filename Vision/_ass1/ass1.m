% %bryce gossling z3424655
% 
% %%
% % figure(2); clf; hold on;
%  board = imread('PSE2_Example_Images/board.tif');
% % imshow(board);
% % hold off;
% %% PART 1.A
% figure(3); clf; hold on;
% gray_board = rgb2gray(board)* 0.25;% 25percent intensity
% imshow(gray_board);
% hold off;
% %% PART 1.B & 1.C
% figure(4); clf; hold on;
% [bw, msk] = createMask(board); 
% subplot(1,5,1);
% imshow(board);
% subplot(1,5,2);
% imshow(bw);
% BW2 = bwareaopen(bw,25);
% pie =  uint8(BW2);
% MSK2 = msk.*pie;%bwareaopen(msk,25);
% subplot(1,5,3);
% BW2=~BW2;
% imshow(BW2);
% temp = uint8(BW2);
% subplot(1,5,4);
% foo = (temp).*gray_board;
% imshow(foo);
% subplot(1,5,5);
% imshow((foo)+ MSK2);
% hold off;
% %% PART 2.1
% figure(5); clf; hold on;
% sherlock = imread('PSE2_Example_Images/sherlock.jpg');
% points = detectSURFFeatures(rgb2gray(sherlock));
% imshow(sherlock);hold on;
% plot(points.selectStrongest(50));
% hold off;
% 
% figure(6); clf; hold on;
% zExam = imread('PSE2_Example_Images/zEXAMPLE.jpg');
% points = detectSURFFeatures(rgb2gray(zExam));
% imshow(zExam); hold on;
% plot(points.selectStrongest(50));
% hold off;
% 
% % scale = .7;
% % J = imresize(zExam, scale); % Try varying the scale factor.
% % 
% % theta = 30;
% % distorted = imrotate(J,theta); % Try varying the angle, theta.
% % figure(7); clf; hold on;
% % imshow(distorted)
% 
% ptsOriginal  = detectSURFFeatures(rgb2gray(sherlock));
% ptsDistorted = detectSURFFeatures(rgb2gray(zExam));
% 
% [featuresOriginal,   validPtsOriginal]  = extractFeatures(rgb2gray(sherlock),  ptsOriginal);
% [featuresDistorted, validPtsDistorted]  = extractFeatures(rgb2gray(zExam), ptsDistorted);
% 
% indexPairs = matchFeatures(featuresOriginal, featuresDistorted);
% 
% matchedOriginal  = validPtsOriginal(indexPairs(:,1));
% matchedDistorted = validPtsDistorted(indexPairs(:,2));
% 
% figure(8); clf; hold on;
% showMatchedFeatures(rgb2gray(sherlock),zExam,matchedOriginal,matchedDistorted);
% title('Putatively matched points (including outliers)');
% 
% [tform, inlierDistorted, inlierOriginal] = estimateGeometricTransform(...
%     matchedDistorted, matchedOriginal, 'similarity');
% 
% figure(9); clf; hold on;
% showMatchedFeatures(sherlock,zExam, inlierOriginal, inlierDistorted);
% title('Matching points (inliers only)');
% legend('ptsOriginal','ptsDistorted');
% 
% Tinv  = tform.invert.T;
% 
% ss = Tinv(2,1);
% sc = Tinv(1,1);
% scale_recovered = sqrt(ss*ss + sc*sc)
% theta_recovered = atan2(ss,sc)*180/pi;
% theta_recovered = -theta_recovered
% outputView = imref2d(size(rgb2gray(sherlock)));
% recovered  = imwarp(rgb2gray(zExam),tform,'OutputView',outputView);
% 
% figure(10);clf; hold on; imshowpair(zExam,recovered,'montage')

%% PART 3.a
rgb = imread('pears.png');
I = rgb2gray(rgb);
imshow(I)
% 
% text(732,501,'Image courtesy of Corel(R)',...
%      'FontSize',7,'HorizontalAlignment','right')
gmag = imgradient(I);
imshow(gmag,[])
title('Gradient Magnitude')

L = watershed(gmag);
Lrgb = label2rgb(L);
imshow(Lrgb)
title('Watershed Transform of Gradient Magnitude')

se = strel('disk',20);
Io = imopen(I,se);
imshow(Io)
title('Opening')

Ie = imerode(I,se);
Iobr = imreconstruct(Ie,I);
imshow(Iobr)
title('Opening-by-Reconstruction')

Ioc = imclose(Io,se);
imshow(Ioc)
title('Opening-Closing')

Iobrd = imdilate(Iobr,se);
Iobrcbr = imreconstruct(imcomplement(Iobrd),imcomplement(Iobr));
Iobrcbr = imcomplement(Iobrcbr);
imshow(Iobrcbr)
title('Opening-Closing by Reconstruction')

fgm = imregionalmax(Iobrcbr);
imshow(fgm)
title('Regional Maxima of Opening-Closing by Reconstruction')

I2 = labeloverlay(I,fgm);
imshow(I2)
title('Regional Maxima Superimposed on Original Image')

se2 = strel(ones(5,5));
fgm2 = imclose(fgm,se2);
fgm3 = imerode(fgm2,se2);

fgm4 = bwareaopen(fgm3,20);
I3 = labeloverlay(I,fgm4);
imshow(I3)
title('Modified Regional Maxima Superimposed on Original Image')

bw = imbinarize(Iobrcbr);
imshow(bw)
title('Thresholded Opening-Closing by Reconstruction')

D = bwdist(bw);
DL = watershed(D);
bgm = DL == 0;
imshow(bgm)
title('Watershed Ridge Lines)')

gmag2 = imimposemin(gmag, bgm | fgm4);

L = watershed(gmag2);

labels = imdilate(L==0,ones(3,3)) + 2*bgm + 3*fgm4;
I4 = labeloverlay(I,labels);
imshow(I4)
title('Markers and Object Boundaries Superimposed on Original Image')
%%
figure(12); clf; hold on;

img1=imread('pears.png');
imshow(img1)

img1=rgb2gray(img1);
pears_gray = img1;
imshow(img1)

img2=im2bw(img1,graythresh(img1));
imshow(img2)

img2=~img2;
img2 = bwareaopen(img2,9900);

imshow(img2)

B = bwboundaries(img2);
imshow(img2)
text(10,10,strcat('\color{green}Objects Found:',num2str(length(B))))
hold on

for k = 1:length(B)
boundary = B{k};
plot(boundary(:,2), boundary(:,1), 'r', 'LineWidth', 0.2)
end

%
figure(14); clf; hold on;
% BW1 = imbinarize(pears_gray,'Global');
% BW2 = imfill(BW1,'holes');
% se = strel('disk',30);
% afteropen = imopen(BW2,se);
bw1 = edge(pears_gray,'sobel',0.04);
[centers, radii] = imfindcircles(bw1,[30 90],'ObjectPolarity','bright','Sensitivity',0.93);
hold on
imshow(img1)
hold off
viscircles(centers, radii,'Color','b');
length(centers)
