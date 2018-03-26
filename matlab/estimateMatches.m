function [a1,u,d1,b1,c1,e1,f1,mp] = estimateMatches(vP1,oP1,sP1,vP2,oP2,sP2,w1,w2,parameters)

% process parameters
[NUMN1,NUMN2,INTRAORILIMIT,INTRASCALELIMIT,INTERORILIMIT,INTERSCALELIMIT,GLOBALORILIMIT] = parseInputs(parameters);

np1 = size(vP1,1);

% select nearest neighbours
NN1 = getnearestneighbours(vP1,NUMN1);
NN2 = getnearestneighbours(vP2,NUMN2);

results = [];
for pts = 1:np1
    
    p1 = vP1(pts,:);
    o1 = oP1(pts);
    s1 = sP1(pts);
    
    nn1 = vP1(NN1(:,pts),:);
    on1 = oP1(NN1(:,pts));
    sn1 = sP1(NN1(:,pts));  
       
   % match words 
   pms = find(w2==w1(pts));
    
   for pmx = 1:length(pms)
    pm = pms(pmx);
     
    p2 = vP2(pm,:);
    o2 = oP2(pm);
    s2 = sP2(pm);
    
    nn2 = vP2(NN2(:,pm),:);
    on2 = oP2(NN2(:,pm));
    sn2 = sP2(NN2(:,pm));
    
    nw1 = w1(NN1(:,pts));
    nw2 = w2(NN2(:,pm));
           
    % compute local support  
    sr = computeLocalSupport(p1,o1,s1,nn1,on1,sn1,p2,o2,s2,nn2,on2,sn2,nw1,nw2);

    % count matches
    if size(sr,1)>0
        support = sum(abs(sr(:,1))<INTRAORILIMIT & abs(sr(:,3))<INTERORILIMIT & abs(log(sr(:,2)))<INTRASCALELIMIT & abs(log(sr(:,4)))<INTERSCALELIMIT);
    else
        support = 0;
    end
    
    if support>0
        results = [results; pts pm support sr(1,5) sr(1,6)];
    end
   end
end

% support format
% intra orientation & intra scale & inter orientation & inter scale &
% relative ori & relative scale

% results format
% p & p' & number of support matches & relative ori & relative scale

% global orientation
a1 = zeros(1,np1);
d1 = [];
b1 = [];
c1 = [];
e1 = [];
f1 = [];
mp = 0;
u = 0;
if size(results,1)>0
    [m,mp] = computeGlobalOrientation(results(:,4),GLOBALORILIMIT);
    a1(results(m,1)) = 1;
    d1 = results(m,1); % point number
    b1 = results(m,2); % matched point
    c1 = results(m,3); % number of support matches
    e1 = results(m,4); % relative ori
    f1 = results(m,5); % relative scale
    % uniqueness
    x1 = sum(a1);
    x2 = length(unique(results(m,2)));

    u = min(x1,x2); % Still an overestimation....
end

end

function results = computeLocalSupport(p1,o1,s1,nn1,on1,sn1,p2,o2,s2,nn2,on2,sn2,nw1,nw2)

ro1 = anglediff(o1,o2); % relative orientation
rs1 = s1./s2; % relative scale

results = [];

for n = 1:size(nn1,1)
    nnc = nn1(n,:);
    onc = on1(n);
    snc = sn1(n);
        
    nwc = nw1(n);
   
    nnm = find(nw2==nwc);
    for n2 = 1:length(nnm)
        ncp = nn2(nnm(n2),:);
        ocp = on2(nnm(n2));
        scp = sn2(nnm(n2));
        % relative orientation
        ro2 = anglediff(onc,ocp);         
        % relative scale
        rs2 = snc./scp;
        % inter versus intra scale and orientation
        [t,s] = interorientationandscale(p1,nnc,p2,ncp);
        a1 = angleabsdiff(ro1,ro2);
        a2 = rs1./rs2;
        a3 = angleabsdiff(ro1,t);
        a4 = rs1./s;
       
        results = [results; a1 a2 a3 a4 ro1 rs1];
    end
end

end

function [t,s] = interorientationandscale(x1,x2,y1,y2)

      vij = [x1(1)-x2(1) x1(2)-x2(2)];
      vmn = [y1(1)-y2(1) y1(2)-y2(2)];
     
      cp =  vij(:,1).*vmn(:,2)-vij(:,2).*vmn(:,1); % analogous to 2D cross product
      nmij = sqrt(sum(vij.^2,2));
      nmnm = sqrt(sum(vmn.^2,2));
      
      t = acos(sum(vij.*vmn,2)./(nmij.*nmnm)).*sign(cp);  % sum(vij.*vmn,2) equivalent to dot product
      
      s = nmij./nmnm;
end

function ad = angleabsdiff(a1,a2)

    ad = abs(a1-a2);
    while ad>2*pi
        ad = ad-2*pi;
    end
    ad = min(abs(ad),abs(2*pi-abs(ad)));
    
end

function ad = anglediff(a1,a2)

    ad = a1-a2;
    while ad>pi
        ad = ad-2*pi;
    end
    while ad<-pi
        ad = ad+2*pi;
    end
    
end

function [m,mp] = computeGlobalOrientation(globalorient,GLOBALORILIMIT)

    if GLOBALORILIMIT>= 2*pi
        m = true(size(globalorient));
        mp = 0;
    else
        gsize = GLOBALORILIMIT/3; 
        [a,b,~] = histcounts(globalorient,-pi:gsize:pi);

            ss = zeros(1,length(a));
            for jj = 2:(length(a)-1)
               ss(jj) = sum(a((jj-1):(jj+1)));
            end

            ss(1) = a(end)+a(1)+a(2);
            ss(end) = a(end-1)+a(end)+a(1);

            [~,z] = max(ss);    

            mp = (b(z)+b(z+1))/2;
            m = (abs(globalorient-mp)<GLOBALORILIMIT);
    end
end

function [NUMN1,NUMN2,INTRAORILIMIT,INTRASCALELIMIT,INTERORILIMIT,INTERSCALELIMIT,GLOBALORILIMIT] = parseInputs(parameters)

NUMN1 = parameters.NUMN1;
NUMN2 = parameters.NUMN2;
INTRAORILIMIT = parameters.INTRAORILIMIT;
INTRASCALELIMIT = parameters.INTRASCALELIMIT;
INTERORILIMIT = parameters.INTERORILIMIT;
INTERSCALELIMIT = parameters.INTERSCALELIMIT;
GLOBALORILIMIT = parameters.GLOBALORILIMIT;

end

function nearestneighbours = getnearestneighbours(vP,NUMN)

    NN = sqrt(bsxfun(@minus,vP(:,1),vP(:,1)').^2+bsxfun(@minus,vP(:,2),vP(:,2)').^2);
   [A,B] = sort(NN);
   
   sz = size(B,1);
   if sz>(NUMN+1)
        nearestneighbours = B(2:(NUMN+1),:);
   else
        nearestneighbours = B(2:sz,:);  
   end


end