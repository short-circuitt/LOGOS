% load images
addpath(genpath('../../SupportFunctions'));
eval(['mex LOGOS.cpp ../src/Point.cpp ../src/Match.cpp ../src/Logos.cpp ../src/PointPair.cpp']); 

% get features etc.
datadir = '/home/stephanie/Datasets/city_centre/';
imagedir = sprintf('%sImages/',datadir);
fformat = sprintf('%s%%04i.jpg',imagedir);

im1 = 101;
im2 = 101;

% im1 = 1448;
% im2 = 388;


IM1 = imread(sprintf(fformat,im1));
imsize = size(IM1);

%extract features
[f1,vPA] = findFeatures(rgb2gray(IM1));

L1 = size(vPA,1);
vP1 = vPA.Location;
oP1 = vPA.Orientation;
sP1 = vPA.Scale; 

[f2,vPB] = findFeatures(rgb2gray(IM2));

L2 = size(vPB,1);
vP2 = vPB.Location;
oP2 = vPB.Orientation;
sP2 = vPB.Scale; 

w1 = 1:L1;
w2 = 1:L2;

LOGOS(double(vP1'),double(oP1),double(sP1),w1,double(vP2'),double(oP2),double(sP2),w2);

parameters = defaultparameterstest1();
[a1,u,d1,b1,c1,e1,f1,mp] = estimateMatches(vP1,oP1,sP1,vP2,oP2,sP2,w1,w2,parameters);


%LOGOS(oP1);

%disp([vP1(1,:) oP1(1) sP1(1)])
%disp(oP1(1))

%disp([vP2(end,:) oP2(end) sP2(end)])
%parameters = defaultparameters();

%need to add in parameters!

% same inputs as estimateMatches but also with lengths L1 and L2

nearestneighbours = getnearestneighbours(vP1,5);

nn = nearestneighbours(:,1);

%disp([vP1(nn,:) oP1(nn) sP1(nn) w1(nn)']);