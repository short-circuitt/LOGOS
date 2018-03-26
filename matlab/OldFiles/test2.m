% load images
addpath(genpath('../../SupportFunctions'));
eval(['mex LOGOS.cpp ../src/Point.cpp ../src/Match.cpp ../src/Logos.cpp ../src/PointPair.cpp']); 

% get features etc.
datadir = '/home/stephanie/Datasets/city_centre/';
imagedir = sprintf('%sImages/',datadir);
fformat = sprintf('%s%%04i.jpg',imagedir);

    rdir = '/home/stephanie/BackUp/Research/QuantizedMetric/VLAD_RANSAC/';
    processeddir = sprintf('%s/DataFolder/',rdir);

numClusters = 512;

% Set up VLAD
load(sprintf('%s/centers_%s_%d.mat',processeddir,'SURF',numClusters),'centers','c');
wnum = numClusters;

addpath(genpath('/home/stephanie/3rdParty/vlfeat-0.9.20/'));
kdtree = vl_kdtreebuild(centers);

im1 = 1448;
im2 = 388;

% im1 = 1872;
% im2 = 778;

% im1 = 1253;
% im2 = 1013;

% im1 = 1234;
% im2 = 337;


IM1 = imread(sprintf(fformat,im1));
imsize = size(IM1);
IM2 = imread(sprintf(fformat,im2));

%extract features
[f1,vPA] = findFeatures(rgb2gray(IM1));
[enc1,nn1] = calculateVLAD(kdtree,centers,f1',wnum);

L1 = size(vPA,1);
vP1 = vPA.Location;
oP1 = vPA.Orientation;
sP1 = vPA.Scale; 

[f2,vPB] = findFeatures(rgb2gray(IM2));
[enc2,nn2] = calculateVLAD(kdtree,centers,f2',wnum);

L2 = size(vPB,1);
vP2 = vPB.Location;
oP2 = vPB.Orientation;
sP2 = vPB.Scale; 

w1 = double(nn1);
w2 = double(nn2);

[x1,y1,z1] = LOGOS(double(vP1'),double(oP1),double(sP1),w1,double(vP2'),double(oP2),double(sP2),w2,parameters);

% disp(size(y1));
% disp(size(z1));

parameters = defaultparameterstest1();
tic;
[a1,u,d1,b1,c1,e1,f1,mp] = estimateMatches(vP1,oP1,sP1,vP2,oP2,sP2,w1,w2,parameters);
elapsedtime=toc;
fprintf('MATLAB implementation takes %06f secs\n',elapsedtime);

vPC = vP1(d1,:);
vP2C = vP2(b1,:);

FH2 = figure(2); showMatchedFeatures(IM1,IM2,vPC,vP2C,'montage');
title('LOGOS inliers (MATLAB implementation)')

vPD = vP1(y1+1,:);
vP2D = vP2(z1+1,:);

FH3 = figure(3); showMatchedFeatures(IM1,IM2,vPD,vP2D,'montage');
title('LOGOS inliers (C++ implementation)')

%disp((y1'+1)-d1')
%disp((z1'+1)-b1')
%LOGOS(oP1);

%disp([vP1(1,:) oP1(1) sP1(1)])
%disp(oP1(1))

%disp([vP2(end,:) oP2(end) sP2(end)])
%parameters = defaultparameters();

%need to add in parameters!

% same inputs as estimateMatches but also with lengths L1 and L2

% nearestneighbours = getnearestneighbours(vP1,5);
% 
% nn = nearestneighbours(:,1);

%disp([vP1(nn,:) oP1(nn) sP1(nn) w1(nn)']);