function []=MTRN4110T22019()

clc; clear all; close all; dbstop if error;

global fig; fig=[];

global img;
img.V=360; img.U=480; img.L=256; img.N=img.V*img.U;

[fn,pn,bn]=uigetfile('..//Images//*.*');

if bn==1,
  JPG=imread([pn fn]);
  [img,RGB]=MyImResize(img,JPG);
  fig(end+1)=MyFigure(); MyImShow(RGB);
  
%   HSV=MyRGB2HSV(RGB);
%   R=RGB(:,:,1); G=RGB(:,:,2); B=RGB(:,:,3);
%   fig(end+1)=MyFigure(); plot3(R(:),G(:),B(:),'.'); 
%   camtarget([0 0 0]); campos([1 1 1]*2);
%   axis equal; grid on; xlabel('R'); ylabel('G'); zlabel('B');
%   fig(end+1)=MyFigure(); MyImShow(HSV(:,:,1));
%   fig(end+1)=MyFigure(); MyImShow(HSV(:,:,2));
%   fig(end+1)=MyFigure(); MyImShow(HSV(:,:,3));
  
%   YIQ=MyRGB2YIQ(RGB);
%   fig(end+1)=MyFigure(); surf(flipud(YIQ(:,:,1)),'edgecolor','none');
%   fig(end+1)=MyFigure(); surf(flipud(YIQ(:,:,2)),'edgecolor','none');
%   fig(end+1)=MyFigure(); surf(flipud(YIQ(:,:,3)),'edgecolor','none');
  
%   ACA=MyAutoContrastAdj(RGB,[0.1 0.9]);
%   fig(end+1)=MyFigure(); MyImShow(ACA);

%   MAC=MyModifyAutoContrast(RGB,[0.2 0.8]);
%   fig(end+1)=MyFigure(); MyImShow(MAC);

%   HEQ=MyHistEQ(RGB);
%   fig(end+1)=MyFigure(); MyImShow(HEQ);
  
%   HSVheq=MyHSVhistEQ(RGB);
%   fig(end+1)=MyFigure(); MyImShow(HSVheq);
  
%   HSP=MyHistSpec(RGB,sin(linspace(0,1,img.L)*pi));
%   fig(end+1)=MyFigure(); MyImShow(HSP);

%   HMA=MyHistMatch(RGB);
%   fig(end+1)=MyFigure(); MyImShow(HMA);

%   GMA=MyGammaCorrec(RGB,1.2);
%   fig(end+1)=MyFigure(); MyImShow(GMA);

%   GMA2=MyGammaCorrec2(RGB,1.3);
%   fig(end+1)=MyFigure(); MyImShow(GMA2);

%   BLE=MyBlending(RGB,0.5);
%   fig(end+1)=MyFigure(); MyImShow(BLE);
  
%   MinF=MyMinFilter(RGB,3);
%   fig(end+1)=MyFigure(); MyImShow(MinF);
% 
%   MaxF=MyMaxFilter(RGB,3);
%   fig(end+1)=MyFigure(); MyImShow(MaxF);
%   
%   fig(end+1)=MyFigure(); MyImShow(MaxF-MinF);

%   FTR1=MyLinearFilt(RGB,5);
%   fig(end+1)=MyFigure(); MyImShow(FTR1);

%   FTR2=MyGaussianFilt(RGB,9,3);
%   fig(end+1)=MyFigure(); MyImShow(FTR2);

%   FTR3=MyLaplacianFilt(RGB,0.3);
%   fig(end+1)=MyFigure(); MyImShow(FTR3);

%   MED1=MyMedianFilt(RGB,3);
%   fig(end+1)=MyFigure(); MyImShow(MED1);

%   MED2=MyMedianFilt2(RGB,3);
%   fig(end+1)=MyFigure(); MyImShow(MED2);

%   MED2=MyUnsharp(RGB,5,3);
%   fig(end+1)=MyFigure(); MyImShow(MED2);

  BLF=MyBilateral(RGB,3,1);
  fig(end+1)=MyFigure(); MyImShow(BLF);

  
%   SEG1=MySimpleTreshold(RGB);
%   fig(end+1)=MyFigure(); MyImShow(SEG1);

%   SEG2=MyOtsuTreshold(RGB);
%   fig(end+1)=MyFigure(); MyImShow(SEG2);

%   SEG3=MyISODATA(RGB);
%   fig(end+1)=MyFigure(); MyImShow(SEG3);
 
%   SEG4=MyMaxEntropy(RGB);
%   fig(end+1)=MyFigure(); MyImShow(SEG4);

%   SEG5=MyBernsenThresh(RGB,21);
%   fig(end+1)=MyFigure(); MyImShow(SEG5);

%   SEG6=MyNiblackThresh(RGB,21,0.2);
%   fig(end+1)=MyFigure(); MyImShow(SEG6);
  
%   GRD1=MyGradient(RGB);
%   fig(end+1)=MyFigure(); MyImShow(GRD1);

%   GRD2=MyGradAngle(RGB);
%   fig(end+1)=MyFigure(); MyImShow(GRD2);

%   EDG1=MyEdge(RGB);
%   fig(end+1)=MyFigure(); MyImShow(EDG1);
    
%   MyHoughLine(RGB);
% 
%   MyFindCorner(RGB);

%   LoG=MyLoG(RGB,15,1);
%   fig(end+1)=MyFigure(); MyImShow(LoG);

%   DoG=MyDoG(RGB,15,1,1.5);
%   fig(end+1)=MyFigure(); MyImShow(DoG);
  
%   MyKeyPoint(RGB);

else
%   MyTest3D;
%   MyStereo;
%   MyLKtracker;
end;


function [HSV]=MyRGB2HSV(RGB)
HSV=rgb2hsv(RGB);

function [YIQ]=MyRGB2YIQ(RGB)
YIQ=rgb2ntsc(RGB);

function [jmg]=MyAutoContrastAdj(jmg,rng)
amin=rng(1); amax=rng(2);
alow=min(jmg(:)); ahigh=max(jmg(:));
jmg=amin+(jmg-alow).*(amax-amin)./(ahigh-alow);

function [jmg]=MyModifyAutoContrast(jmg,rng)
alow=rng(1); ahigh=rng(2); amin=0; amax=1;
zmin=find(jmg<=alow);
zmax=find(jmg>=ahigh);
zmid=find(jmg>alow & jmg<ahigh);
jmg(zmin)=alow; jmg(zmax)=ahigh;
jmg(zmid)=amin+(jmg(zmid)-alow).*(amax-amin)./(ahigh-alow);

function [jmg]=MyHistEQ(jmg)
for c=1:3,
  jmg(:,:,c)=histeq(jmg(:,:,c));
end;

function [jmg]=MyHistSpec(jmg,his)
for c=1:3,
  jmg(:,:,c)=histeq(jmg(:,:,c),his);
end;

function [jmg]=MyHistMatch(jmg)
global fig img;
[fn,pn,bn]=uigetfile('..//Images//*.jpg');
if bn==1,
  JPG=imread([pn fn]);
  [img,RGB]=MyImResize(img,JPG);
  fig(end+1)=MyFigure(); MyImShow(RGB);
  his=hist(RGB(:),img.L);
  for c=1:3,
    jmg(:,:,c)=histeq(jmg(:,:,c),his);
  end;
end;

function [jmg]=MyGammaCorrec(jmg,gma)
jmg=jmg.^gma;

function [jmg]=MyGammaCorrec2(jmg,gma)
HSV=rgb2hsv(jmg); gry=HSV(:,:,3);
G_low=gry.^gma; G_high=gry.^(1/gma);
HSV(:,:,3)=G_low.*(1-gry)+G_high.*gry;
jmg=hsv2rgb(HSV);

function [jmg]=MyBlending(jmg,alp)
global fig img;
[fn,pn,bn]=uigetfile('..//Images//*.jpg');
if bn==1,
  JPG=imread([pn fn]);
  [img,RGB]=MyImResize(img,JPG);
  fig(end+1)=MyFigure(); MyImShow(RGB);
  jmg=alp*jmg+(1-alp)*RGB;
end;

function [jmg]=MyHSVhistEQ(jmg)
HSV=rgb2hsv(jmg);
HSV(:,:,3)=histeq(HSV(:,:,3));
jmg=hsv2rgb(HSV);


function [jmg]=MyLinearFilt(jmg,sze)
global fig;
jmg=imnoise(jmg,'gaussian',0,0.01);
fig(end+1)=MyFigure(); MyImShow(jmg);
H=fspecial('average',[sze sze]);
jmg=imfilter(jmg,H);

function [jmg]=MyGaussianFilt(jmg,sze,sig)
global fig;
jmg=imnoise(jmg,'gaussian',0,0.01);
fig(end+1)=MyFigure(); MyImShow(jmg);
H=fspecial('gaussian',sze,sig);
jmg=imfilter(jmg,H);

function [jmg]=MyLaplacianFilt(jmg,alp)
global fig;
H=fspecial('laplacian',alp);
jmg=imfilter(jmg,H);
fig(end+1)=MyFigure(); surf(flipud(mean(jmg,3)),'edgecolor','none');

function [jmg]=MyMedianFilt(jmg,rng)
global fig;
jmg=imnoise(jmg,'salt & pepper');
fig(end+1)=MyFigure(); MyImShow(jmg);
for c=1:3,
  jmg(:,:,c)=medfilt2(jmg(:,:,c),rng*[1 1]);
end;

function [kmg]=MyMedianFilt2(jmg,rng)
global fig;
jmg=imnoise(jmg,'salt & pepper');
fig(end+1)=MyFigure(); MyImShow(jmg);
[V,U,~]=size(jmg); sze=floor(rng/2); kmg=jmg;
for v=sze+1:V-sze,
  for u=sze+1:U-sze,
    I=jmg(v-sze:v+sze,u-sze:u+sze,:);
    J=reshape(I,[rng^2,3]);
    for z=1:rng^2,
      d(z)=sum(sum(abs(repmat(J(z,:),[rng^2,1])-J)));
    end;
    [mi,ix]=min(d); [y,x]=ind2sub([rng,rng],ix);
    kmg(v,u,:)=I(y,x,:);
  end;
end;

function [jmg]=MyUnsharp(jmg,rng1,rng2)
kmg=jmg;
for c=1:3,
  jmg(:,:,c)=medfilt2(jmg(:,:,c),rng1*[1 1]);
end;
H=fspecial('average',rng2);
E=kmg-imfilter(kmg,H);
jmg=jmg+E;

function [jmg]=MyMinFilter(jmg,sze)
HSV=rgb2hsv(jmg); gry=HSV(:,:,3); SE=ones(sze,sze);
jmg=imopen(gry,SE);

function [jmg]=MyMaxFilter(jmg,sze)
HSV=rgb2hsv(jmg); gry=HSV(:,:,3); SE=ones(sze,sze);
jmg=imclose(gry,SE);

function [jmg]=MyBilateral(jmg,sze,sig)
global fig;
HSV=rgb2hsv(jmg); gry=HSV(:,:,3); 
gryN=imnoise(gry,'gaussian',0,0.02);
fig(end+1)=MyFigure(); MyImShow(gryN);
H=sze; S=sig; h=floor(H/2);
SF=fspecial('gaussian',H,S);
[V,U]=size(gry);
for v=h+1:V-h,
  for u=h+1:U-h,
    RF=exp(-(repmat(gryN(v,u),[H,H])-gry(v-h:v+h,u-h:u+h)).^2/(2*S^2));
    BF=SF.*RF; BF=BF/sum(BF(:));
    HSV(v,u,3)=sum(sum(gryN(v-h:v+h,u-h:u+h).*BF));
  end;
end;
jmg=hsv2rgb(HSV);


function [jmg]=MySimpleTreshold(jmg)
gry=rgb2gray(jmg);
q=0.5*(min(gry(:))+max(gry(:)));
jmg=zeros(size(gry));
jmg(find(gry>q))=1;

function [jmg]=MyOtsuTreshold(jmg)
gry=rgb2gray(jmg);
q=graythresh(gry);
jmg=zeros(size(gry));
jmg(find(gry>q))=1;

function [jmg]=MyISODATA(jmg)
gry=uint8(rgb2gray(jmg)*255); Qold=128; 
G1=gry(find(gry<=Qold)); G2=gry(find(gry>Qold)); 
m1=mean(G1); m2=mean(G2); Qnew=floor(mean([m1 m2]));
while abs(Qold-Qnew)>0,
  Qold=Qnew;
  G1=gry(find(gry<=Qold)); G2=gry(find(gry>Qold));
  m1=mean(G1); m2=mean(G2); Qnew=floor(mean([m1 m2]));
end;
jmg=zeros(size(gry));
jmg(find(gry>Qnew))=1;

function [jmg]=MyMaxEntropy(jmg)
gry=uint8(rgb2gray(jmg)*255);
for k=1:255,
  G1=gry(find(gry<=k)); G2=gry(find(gry>k));
  if (length(G1)>0 & length(G2)>0),
    E1=entropy(G1); E2=entropy(G2); sumE(k)=E1+E2;
  end;
end;
[mx,ix]=max(sumE);
jmg=zeros(size(gry));
jmg(find(gry>ix))=1;

function [jmg]=MyBernsenThresh(jmg,sze)
global img;
gry=rgb2gray(jmg); jmg=zeros(size(gry)); s=ceil(sze/2);
for v=s:img.V-s,
  for u=s:img.U-s,
    R=gry(v-s+1:v+s-1,u-s+1:u+s-1);
    mi=min(R(:)); mx=max(R(:)); Q=(mi+mx)/2;
    jmg(v,u)=gry(v,u)>Q;
  end;
end;

function [jmg]=MyNiblackThresh(jmg,sze,k)
global img;
gry=rgb2gray(jmg); jmg=zeros(size(gry)); s=ceil(sze/2);
for v=s:img.V-s,
  for u=s:img.U-s,
    gR=gry(v-s+1:v+s-1,u-s+1:u+s-1);
    mn=mean(gR(:)); sd=std(gR(:)); Q=mn+k*sd;
    jmg(v,u)=gry(v,u)>Q;
  end;
end;


function [jmg]=MyWavelet1(jmg)
global fig;
gry=rgb2gray(jmg);
fig(end+1)=MyFigure(); MyImShow(gry);
W=2; ahvd={'a','h','v','d'}; wname='db5'; % wavelet name
[C,S]=wavedec2(gry,W,wname); % decomposition
for w=1:W,
  fig(end+1)=MyFigure();
  set(gcf,'position',[rand*0.1+0.2 rand*0.1+0.1 0.5 0.7]);
  for x=1:4,
    if x==1,
      % approximation coefficient
      eval(sprintf('%s%d=appcoef2(C,S,''%s'',%d);',ahvd{x},w,wname,w));
    else
      % detail coefficient
      eval(sprintf('%s%d=detcoef2(''%s'',C,S,%d);',ahvd{x},w,ahvd{x},w));
    end;
    % extended pseudocolor matrix scaling
    subplot(2,2,x); eval(sprintf('image(wcodemat(%s%d,256));',ahvd{x},w));
  end;
end;
for w=1:W,
  % single-level inverse discrete 2-D wavelet transform
  eval(sprintf('gry=idwt2(a%d,h%d,v%d,d%d,''%s'');',w,w,w,w,wname));
  fig(end+1)=MyFigure(); MyImShow(gry);
end;
jmg=waverec2(C,S,wname); % multilevel 2-D wavelet reconstruction

% Set wavelet name. 
fig(end+1)=MyFigure(); wname='db5'; 
% Compute the four filters associated with wavelet name given 
[Lo_D,Hi_D,Lo_R,Hi_R] = wfilters(wname); 
subplot(221); stem(Lo_D); 
title('Decomposition low-pass filter'); 
subplot(222); stem(Hi_D); 
title('Decomposition high-pass filter'); 
subplot(223); stem(Lo_R); 
title('Reconstruction low-pass filter'); 
subplot(224); stem(Hi_R); 
title('Reconstruction high-pass filter'); 


function [jmg]=MyGradient(jmg)
gry=rgb2gray(jmg);
[Fx,Fy]=gradient(gry);
jmg=sqrt(Fx.^2+Fy.^2);

function [jmg]=MyGradAngle(jmg)
gry=rgb2gray(jmg);
[Fx,Fy]=gradient(gry);
jmg=atan2(Fy,Fx);


function [jmg]=MyEdge(jmg)
gry=rgb2gray(jmg);
% jmg=edge(gry,'sobel');
% jmg=edge(gry,'Prewitt'); 
% jmg=edge(gry,'Roberts'); 
% jmg=edge(gry,'Log');
% jmg=edge(gry,'zerocross');
jmg=edge(gry,'Canny');

function []=MyHoughLine(jmg)
global fig;
gry=rgb2gray(jmg); z=5; gry=gry(z:end-z,z:end-z);
edg=edge(gry,'canny');
fig(end+1)=MyFigure(); MyImShow(edg);
[H,theta,rho] = hough(edg);
fig(end+1)=MyFigure(); 
imshow(imadjust(mat2gray(H)),[],'XData',theta,'YData',rho,...
        'InitialMagnification','fit');
xlabel('\theta (degrees)'), ylabel('\rho');
axis on, axis normal, hold on;
P=houghpeaks(H,9,'threshold',ceil(0.1*max(H(:))));
x=theta(P(:,2)); y=rho(P(:,1));
plot(x,y,'s','color','black');
lines = houghlines(edg,theta,rho,P,'FillGap',5,'MinLength',15);
fig(end+1)=MyFigure(); imshow(gry), hold on;
set(gca,'position',[0 0 1 1]);
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
   % Plot beginnings and ends of lines
   plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
   plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');
end

function []=MyFindCircle(jmg)
gry=rgb2gray(jmg); Rmin=5; Rmax=50;
[centers, radii, metric] = imfindcircles(gry,[Rmin Rmax]);
Thr=0.5; if min(metric)>Thr,
  C=length(radii); centersStrong = centers(1:C,:);
  radiiStrong = radii(1:C); metricStrong = metric(1:C);
  viscircles(centersStrong, radiiStrong,'EdgeColor','y');
end;

function []=MyFindCorner(jmg)
global fig img;
gry=rgb2gray(jmg); jmg=zeros(size(gry));
Thr=graythresh(gry); jmg(gry>Thr)=1;
C=corner(jmg,'qualitylevel',0.3,'Sensitivityfactor',0.02);
fig(end+1)=MyFigure(); MyImShow(gry);
hold on; plot(C(:,1),C(:,2),'r*');


function [jmg]=MyLoG(jmg,h,s)
gry=rgb2gray(jmg);
h_=floor(h/2); [x,y]=meshgrid(-h_:h_,-h_:h_);
N2G=1/(2*pi*s^4).*((x.^2+y.^2-2*s^2)./s^2).*exp(-(x.^2+y.^2)/(2*s^2));
jmg=imfilter(gry,N2G,'replicate','same','conv');
mi=min(jmg(:)); mx=max(jmg(:)); jmg=(jmg-mi)/(mx-mi);

function [jmg]=MyDoG(jmg,h,s,alp)
gry=rgb2gray(jmg);
H1=fspecial('gaussian',h,s);
H2=fspecial('gaussian',h,s*alp);
L1=imfilter(gry,H1,'replicate','same','conv');
L2=imfilter(gry,H2,'replicate','same','conv');
jmg=L1-L2;
mi=min(jmg(:)); mx=max(jmg(:)); jmg=(jmg-mi)/(mx-mi);

function []=MyKeyPoint(jmg)
global fig img;
gry=rgb2gray(jmg);
points=detectSURFFeatures(gry,...
  'MetricThreshold',1000,'NumOctaves',3,'NumScaleLevels',4);
[features,valid_points]=extractFeatures(gry, points);
fig(end+1)=MyFigure(); MyImShow(gry); hold on;
plot(valid_points.selectStrongest(10),'showOrientation',true);

function []=MyLKtracker()
global img;
% Read in a video file
vidReader = VideoReader('viptraffic.avi');
% Create optical flow object
opticFlow = opticalFlowLK('NoiseThreshold',0.009);
% Estimate and display the optical flow of objects in the video
while hasFrame(vidReader)
    frameRGB = readFrame(vidReader); 
    [img,frameRGB]=MyImResize(img,frameRGB);
    frameGray = rgb2gray(frameRGB);
    flow = estimateFlow(opticFlow,frameGray);
    imshow(frameRGB)
    hold on
    plot(flow,'DecimationFactor',[5 5],'ScaleFactor',10)
    hold off
end

function []=MyStereo()
global fig;
% Load the stereoParameters object.
load('handshakeStereoParams.mat');
% Visualize camera extrinsics.
showExtrinsics(stereoParams);
% Create System Objects for reading and displaying the video
videoFileLeft = 'handshake_left.avi';
videoFileRight = 'handshake_right.avi';
readerLeft=vision.VideoFileReader(videoFileLeft,'VideoOutputDataType','uint8');
readerRight=vision.VideoFileReader(videoFileRight,'VideoOutputDataType','uint8');
player = vision.VideoPlayer('Position', [20, 400, 850, 650]);
% Read and Rectify Video Frames
frameLeft = readerLeft.step();
frameRight = readerRight.step();
[frameLeftRect, frameRightRect] = ...
    rectifyStereoImages(frameLeft, frameRight, stereoParams);
fig(end+1)=MyFigure(); 
imshow(stereoAnaglyph(frameLeftRect, frameRightRect));
title('Rectified Video Frames');
% Compute Disparity
frameLeftGray  = rgb2gray(frameLeftRect);
frameRightGray = rgb2gray(frameRightRect);
disparityMap = disparity(frameLeftGray, frameRightGray);
fig(end+1)=MyFigure();
imshow(disparityMap, [0, 64]);
title('Disparity Map');
colormap jet; colorbar;
% Reconstruct the 3-D Scene
point3D = reconstructScene(disparityMap, stereoParams);
% Limit the range of Z and X for display.
z = point3D(:,:,3);
z(z < 0 | z > 8000) = NaN;
x = point3D(:,:,1);
x(x < -3000 | x > 3000) = NaN;
point3D(:,:,3) = z; point3D(:,:,1) = x;
fig(end+1)=MyFigure();
pcshow(point3D, frameLeftRect, 'VerticalAxis', 'Y', 'VerticalAxisDir', 'Down');
xlabel('X (mm)');ylabel('Y (mm)');zlabel('Z (mm)');
set(gca, 'CameraViewAngle',10, 'CameraUpVector',[0 -1 0],...
    'CameraPosition',[16500 -13852 -49597], 'DataAspectRatio',[1 1 1]);
title('Reconstructed 3-D Scene');
% Detect People in the Left Image
% Create the people detector object. Limit the minimum object size for speed.
peopleDetector = vision.PeopleDetector('MinSize', [166 83]);
% Detect people.
bboxes = peopleDetector.step(frameLeftGray);
% Determine The Distance of Each Person to the Camera
% Find the centroids of detected people.
centroids = [round(bboxes(:, 1) + bboxes(:, 3) / 2), ...
    round(bboxes(:, 2) + bboxes(:, 4) / 2)];
% Find the 3-D world coordinates of the centroids.
centroidsIdx = sub2ind(size(disparityMap), centroids(:, 2), centroids(:, 1));
X = point3D(:, :, 1); Y = point3D(:, :, 2); Z = point3D(:, :, 3);
centroids3D = [X(centroidsIdx)'; Y(centroidsIdx)'; Z(centroidsIdx)'];
% Find the distances from the camera in meters.
dists = sqrt(sum(centroids3D .^ 2)) / 1000;
% Display the detected people and their distances.
labels = cell(1, numel(dists));
for i = 1:numel(dists)
    labels{i} = sprintf('%0.2f meters', dists(i));
end
fig(end+1)=MyFigure();
imshow(insertObjectAnnotation(frameLeftRect, 'rectangle', bboxes, labels));
title('Detected People');
% Process the Rest of the Video
while ~isDone(readerLeft) && ~isDone(readerRight)
    % Read the frames.
    frameLeft = readerLeft.step();
    frameRight = readerRight.step();
    % Rectify the frames.
    [frameLeftRect, frameRightRect] = ...
        rectifyStereoImages(frameLeft, frameRight, stereoParams);
    % Convert to grayscale.
    frameLeftGray  = rgb2gray(frameLeftRect);
    frameRightGray = rgb2gray(frameRightRect);
    % Compute disparity.
    disparityMap = disparity(frameLeftGray, frameRightGray);
    % Reconstruct 3-D scene.
    point3D = reconstructScene(disparityMap, stereoParams);
    % Detect people.
    bboxes = peopleDetector.step(frameLeftGray);
    if ~isempty(bboxes)
        % Find the centroids of detected people.
        centroids = [round(bboxes(:, 1) + bboxes(:, 3) / 2), ...
            round(bboxes(:, 2) + bboxes(:, 4) / 2)];
        % Find the 3-D world coordinates of the centroids.
        centroidsIdx = sub2ind(size(disparityMap), centroids(:, 2), centroids(:, 1));
        X = point3D(:, :, 1);
        Y = point3D(:, :, 2);
        Z = point3D(:, :, 3);
        centroids3D = [X(centroidsIdx), Y(centroidsIdx), Z(centroidsIdx)];
        % Find the distances from the camera in meters.
        dists = sqrt(sum(centroids3D .^ 2, 2)) / 1000;
        % Display the detect people and their distances.
        labels = cell(1, numel(dists));
        for i = 1:numel(dists)
            labels{i} = sprintf('%0.2f meters', dists(i));
        end
        dispFrame = insertObjectAnnotation(frameLeftRect, 'rectangle', bboxes,...
            labels);
    else
        dispFrame = frameLeftRect;
    end
    % Display the frame.
    step(player, dispFrame);
end
% Clean up
reset(readerLeft);
reset(readerRight);
release(player);

function []=MyTest3D()
global fig;
fig(end+1)=MyFigure();
plot3(0,0,0); grid on; hold on; view(30,45); axis equal;
xlabel('X'); ylabel('Z'); zlabel('Y');

cam.b=0.1; 
cam.L.Orig=[0,0,0];
cam.R.Orig=[cam.b,0,0];
plot3(cam.L.Orig(1),cam.L.Orig(2),cam.L.Orig(3),...
  'ro','MarkerFaceColor','r');
plot3(cam.R.Orig(1),cam.R.Orig(2),cam.R.Orig(3),...
  'bo','MarkerFaceColor','b');

cam.focal=0.015;
cam.width=0.015; cam.width2=cam.width/2;
cam.viewang=2*atan(cam.width/(2*cam.focal));

cam.L.frame=[-cam.width2  cam.width2 cam.width2 -cam.width2 -cam.width2;
  [1 1 1 1 1]*cam.focal; 
  -cam.width2 -cam.width2 cam.width2  cam.width2 -cam.width2];
cam.R.frame=cam.L.frame+[ones(1,5)*cam.b; 0 0 0 0 0; 0 0 0 0 0];
plot3(cam.L.frame(1,:),cam.L.frame(2,:),cam.L.frame(3,:),'r');
plot3(cam.R.frame(1,:),cam.R.frame(2,:),cam.R.frame(3,:),'b');

obj.Orig=[0 -0.5 1];
P=21; h=linspace(0,1,P); s=sin(2*pi*h); e=2; e=fliplr(exp(-e*h));
[Jx,Jz,Jy]=cylinder(s.*e*0.5); 
Jx=Jx+obj.Orig(1); Jy=Jy+obj.Orig(2); Jz=Jz+obj.Orig(3); 
surf(Jx,Jz,Jy); o=1.75;
plot3([0 0],[0 obj.Orig(3)*o],[0 0],'r');
plot3([1 1]*cam.b,[0 obj.Orig(3)*o],[0 0],'b');
plot3([0 0],[0 obj.Orig(3)],[0 0],'ro','markerfacecolor','r');
plot3([1 1]*cam.b,[0 obj.Orig(3)],[0 0],'bo','markerfacecolor','b');

obj.mag=obj.Orig(3)/cam.focal; obj.width2=cam.width2*obj.mag;
obj.L.frame=[-obj.width2  obj.width2 obj.width2 -obj.width2 -obj.width2;
  [1 1 1 1 1]*obj.Orig(3); 
  -obj.width2 -obj.width2 obj.width2  obj.width2 -obj.width2];
obj.R.frame=obj.L.frame+[ones(1,5)*cam.b; 0 0 0 0 0; 0 0 0 0 0];
plot3(obj.L.frame(1,:),obj.L.frame(2,:),obj.L.frame(3,:),'r');
plot3(obj.R.frame(1,:),obj.R.frame(2,:),obj.R.frame(3,:),'b');
for c=1:4,
  plot3([0 obj.L.frame(1,c)],[0 obj.L.frame(2,c)],...
    [0 obj.L.frame(3,c)],'r-.');
  plot3([cam.b obj.R.frame(1,c)],[0 obj.R.frame(2,c)],...
    [0 obj.R.frame(3,c)],'b-.');
end; alpha 0.5; ax=axis;
for p=1:P,
  for q=1:P,
    if Jz(p,q)<=obj.Orig(3),
      z=cam.focal/Jz(p,q);
      plot3(Jx(p,q)*z,cam.focal,Jy(p,q)*z,'r.');  
      plot3((Jx(p,q)-cam.b)*z+cam.b,cam.focal,Jy(p,q)*z,'b.'); 
      img.L.x(p,q)=Jx(p,q)*z; img.L.y(p,q)=Jy(p,q)*z;
      img.R.x(p,q)=(Jx(p,q)-cam.b)*z; img.R.y(p,q)=Jy(p,q)*z;
    else
      img.L.x(p,q)=NaN; img.L.y(p,q)=NaN;
      img.R.x(p,q)=NaN; img.R.y(p,q)=NaN;      
    end;
  end;
end;
fig(end+1)=MyFigure();
subplot(2,2,1); plot(img.L.x,img.L.y,'r.'); 
hold on; grid on; axis equal; hd.L=plot(0,0,'ro','markersize',5);
axis([-cam.width2 cam.width2 -cam.width2 cam.width2]);
subplot(2,2,2); plot(img.R.x,img.R.y,'b.'); 
hold on; grid on; axis equal; hd.R=plot(0,0,'bo','markersize',5);
axis([-cam.width2 cam.width2 -cam.width2 cam.width2]);
subplot(2,3,5); plot3(0,0,0); hold on; grid on;
xlabel('X'); ylabel('Z'); zlabel('Y'); view(30,45);
for p=1:P,
  for q=1:P,
    if Jz(p,q)<=obj.Orig(3),
      L.x=img.L.x(p,q); L.y=img.L.y(p,q);
      R.x=img.R.x(p,q); R.y=img.R.y(p,q);
      subplot(2,2,1); title(sprintf('X=%5.4f Y=%5.4f',L.x,L.y));
      set(hd.L,'xdata',L.x,'ydata',L.y);
      subplot(2,2,2); title(sprintf('Z=%5.4f Y=%5.4f',R.x,R.y));
      set(hd.R,'xdata',R.x,'ydata',R.y);
      Xo(p,q)=cam.b*L.x/(L.x-R.x); 
      Yo(p,q)=cam.b*L.y/(L.x-R.x); 
      Zo(p,q)=cam.b*cam.focal/(L.x-R.x);
      subplot(2,3,5); plot3(Xo(p,q),Zo(p,q),Yo(p,q),'k.'); 
      title(sprintf('X=%5.4f Y=%5.4f Z=%5.4f',Xo(p,q),Yo(p,q),Zo(p,q)));
      pause(0.05);
    else
      Xo(p,q)=NaN; Yo(p,q)=NaN; Zo(p,q)=NaN;
    end;
  end;
end;
surf(Xo,Zo,Yo); alpha 0.5; axis(ax);


%%%%%%%%%%%%%%%%%%%%%%%%
function [fig]=MyFigure()
fig=figure('units','normalized');
set(gcf,'position',[rand*0.1+0.2 rand*0.1+0.2 0.3 0.35]);

function []=MyImShow(jmg)
global fig img;
figure(fig(end)); 
if max(jmg(:))<=1,
  imshow(jmg,[0 1]);
else
  imshow(jmg);
end;
set(gca,'position',[0 0 1 1]); drawnow;

function [img,jmg]=MyImResize(img,jmg)
[v,u,w]=size(jmg);
maxvu=max([v u]); maxVU=max([img.V img.U]);
jmg=imresize(jmg,maxVU/maxvu,'bilinear');
[v,u,w]=size(jmg); img.V=v; img.U=u; img.N=img.V*img.U;
if max(jmg(:))>1,
  jmg=double(jmg)/img.L;
end;
  

%   WAV1=MyWavelet1(RGB);
%   fig(end+1)=MyFigure(); MyImShow(WAV1);


%   MyFindCircle(RGB);
