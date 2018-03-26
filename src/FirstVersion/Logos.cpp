// Use OpenCV, FLANN, Eigen....
// Need to keep a careful check on which points have had their NN calculated!
// Fix logs!!!!!

#include "Logos.h"

void Logos::estimateMatches(std::vector<Point*> vP1, std::vector<Point*> vP2){

matches.clear();

// for each point
int count1 = 0;

for (pit1=vP1.begin(); pit1<vP1.end(); ++pit1,count1++){
	(*pit1)->nearestNeighbours(vP1,count1,this->getNum1());
	int count2 = 0;
        // find possible matches
        for (pit2=vP2.begin(); pit2<vP2.end(); ++pit2,count2++){
		if ((*pit1)->getlabel()!= (*pit2)->getlabel()){
			continue;
		}
                int support = 0;
		// this is a possible match in Image 2
                // get nearest neighbours
	        (*pit2)->nearestNeighbours(vP2,count2,this->getNum2());
                pp.clear();
		(*pit1)->computeLocalSupport((*pit2),pp,this->getNum2());
               // calc matches
	       for (it=pp.begin(); it<pp.end(); ++it){
		    Match* m = new Match((*pit1),(*pit2),(*it)->p1,(*it)->p2);
                    if (evaluateMatch(m)){
                           support++;
		           // matches.push_back(m);
                    }
	       }
              if (support>0){
		PointPair* ptpr = new PointPair();
                ptpr->p1 = (*pit1);
                ptpr->p2 = (*pit2);
                ptpr->support = support;
                matches.push_back(ptpr);
              }
	}
}

std::cout << "Matches found" << std::endl;
std::cout << matches.size() << std::endl;

// do global orientation

//determineglobalorientation

//for (int f=0; f<matches.size(); f++){
//   if (abs(ro1-globalOrientation)>GLOBALORILIMIT){
//	matches.erase(f);
//   }
//}

}

bool Logos::evaluateMatch(Match* m){
 return  ((m->getRelOrientation()<this->getIntraOriLimit()) && 
       (m->getRelScale()<this->getIntraScaleLimit()) && 
       (m->getInterOrientation()<this->getInterOriLimit()) && 
       (m->getInterScale()<this->getInterScaleLimit()));
}



//setParameters(parameters);



//    
//    if support>0
//        results = [results; pts pm support sr(1,5) sr(1,6)];
//    end
//   }
//}

//% global orientation
//% fprintf(fid,'testh\n');
//a1 = zeros(1,np1);
//d1 = [];
//b1 = [];
//c1 = [];
//e1 = [];
//f1 = [];
//mp = 0;
//u = 0;
//if size(results,1)>0
//    [m,mp] = computeGlobalOrientation(results(:,4),GLOBALORILIMIT);
//    a1(results(m,1)) = 1;
//    d1 = results(m,1); % point number
//    b1 = results(m,2); % matched point
//    c1 = results(m,3); % number of support matches
//    e1 = results(m,4); % relative ori
//    f1 = results(m,5); % relative scale
//    % uniqueness
//    x1 = sum(a1);
//    x2 = length(unique(results(m,2)));

//    u = min(x1,x2); % Still an overestimation....
//end

//end

//void Logos::computeGlobalOrientation(){

//          double gsize = GLOBALORILIMIT/3;  // bit lazy, should split into 6
//          double numbins = 2*PI/gsize;
//  
          // go through matches
          // put each ro1 in the correct bin
          // then sum up the best bin
          // globalorientation is the max value
 
//        [a,b,cc] = histcounts(globalorient,-pi:gsize:pi);

//            ss = zeros(1,length(a));
//            for jj = 2:(length(a)-1)

//               ss(jj) = sum(a((jj-1):(jj+1)));

//            end

//            ss(1) = a(end)+a(1)+a(2);
//            ss(end) = a(end-1)+a(end)+a(1);

//            [t,z] = max(ss);    

//            mp = (b(z)+b(z+1))/2;
//            m = (abs(globalorient-mp)<GLOBALORILIMIT);
//    }

//    //return (m,mp);
//}

//void Logos::setParameters(parameters){

//this.NUMN1 = parameters.NUMN1;
//this.NUMN2 = parameters.NUMN2;
//this.INTRAORILIMIT = parameters.INTRAORILIMIT;
//this.INTRASCALELIMIT = parameters.INTRASCALELIMIT;
//this.INTERORILIMIT = parameters.INTERORILIMIT;
//this.INTERSCALELIMIT = parameters.INTERSCALELIMIT;
//this.GLOBALORILIMIT = parameters.GLOBALORILIMIT;
//}

