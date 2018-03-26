

#include "Logos.h"

int Logos::estimateMatches(std::vector<Point*> vP1, std::vector<Point*> vP2, std::vector<PointPair*> &globalmatches){

matches.clear();

//// for each point
int count1 = 0;

for (pit1=vP1.begin(); pit1<vP1.end(); ++pit1,count1++){
	(*pit1)->nearestNeighbours(vP1,count1,this->getNum1());
	int count2 = 0;
        // find possible matches
        for (pit2=vP2.begin(); pit2<vP2.end(); ++pit2,count2++){
		if ((*pit1)->getlabel()!= (*pit2)->getlabel()){
			continue;
		}
		// this is a possible match in Image 2
                // get nearest neighbours
	        (*pit2)->nearestNeighbours(vP2,count2,this->getNum2());

                PointPair* ptpr = new PointPair((*pit1),(*pit2));
		ptpr->addPositions(count1,count2); 
                pp.clear();
		ptpr->computeLocalSupport(pp,this->getNum2());
                
               // calc matches
               int support = 0;
               //std::cout << pp.size() << std::endl;
//  		if (count1==105 && count2== 95){   // and 118 / 95
//			std::cout << pp.size() << std::endl;
// 		}
	       for (it=pp.begin(); it<pp.end(); ++it){
		    Match* m = new Match(ptpr,(*it));
//  		if (count1==105 && count2== 95){
//			//m->printMatch();
//                        //std::cout << m->getro3() << std::endl;
// 		}
                    if (evaluateMatch(m)){
                           support++;	
                           //std::cout << ptpr->getrelori() << " " << (*it)->getrelori() << std::endl;
                           //m->printMatch();
                    } 
	       }
              if (support>0){
                ptpr->setsupport(support);
                //std::cout << ptpr->getrelori() << std::endl; 
                matches.push_back(ptpr);
                updatebin(ptpr->getrelori());
              } 
	}
}

//std::cout << "Matches found" << std::endl;
//std::cout << matches.size() << std::endl;

//for (it=matches.begin(); it!=matches.end(); ++it){
// std::cout << (*it)->getpos1()+1 << " " << (*it)->getpos2()+1 << " " << (*it)->getsupport() << " " << std::endl;
//}

// do global orientation
double maxang = calcGlobalOrientation();
// find which matches are within global ori limit
int numinliers=0;
globalmatches.clear();
//std::cout << maxang << std::endl;
for (it=matches.begin(); it!=matches.end(); ++it){
       //std::cout << std::abs((*it)->getrelori()-maxang) << std::endl;
       if (std::abs((*it)->getrelori()-maxang)<GLOBALORILIMIT){
	     numinliers++;
             globalmatches.push_back(*it);
	}
}

return numinliers;

}

bool Logos::evaluateMatch(Match* m){
 return  ((m->getRelOrientation()<getIntraOriLimit()) && 
       (m->getRelScale()<getIntraScaleLimit()) && 
       (m->getInterOrientation()<getInterOriLimit()) && 
       (m->getInterScale()<getInterScaleLimit()));
}


void Logos::updatebin(double input){
   double binnumber=floor((input-LB)/BINSIZE);
   // compare binnumber to BINNUMBER
   if (binnumber<BINNUMBER){
	bins[(unsigned int)binnumber]++;
   } else {
        std::cout << "PROBLEM: ";
	std::cout << binnumber << " " << BINNUMBER << std::endl;
   }
}

double Logos::calcGlobalOrientation(){
	// find max bin
	// Need to check BINNUMBER is big enough
        if (BINNUMBER<3){
		std::cout << "Binnumber: " << BINNUMBER << std::endl;
                return 0.0;
        }
	int* bins2 = new int[BINNUMBER];
	int maxval = 0;
	unsigned int maxix = 0;
	bins2[0] = bins[0]+bins[1]+bins[BINNUMBER-1];
	maxval = bins2[0];
	for (unsigned int i=1; i<BINNUMBER; i++){
	  if (i==BINNUMBER-1){
		bins2[i] = bins[i]+bins[i-1]+bins[0];
	  } else {
		  bins2[i] = bins[i]+bins[i-1]+bins[i+1];
	  } 
          //std::cout << i << " " << bins[i] << " " << bins2[i] << std::endl;
	  if (bins2[i]>maxval){
	    maxval = bins2[i];
	    maxix = i;
            //std::cout << maxval << std::endl;
	  }
	}
      // convert to an angle 
      //return LB+((double)maxix)*BINSIZE;
      return LB+((double)maxix)*BINSIZE+BINSIZE/2;
}

//void Logos::setParameters(parameters){

//this.NUMN1 = parameters.NUMN1;
//this.NUMN2 = parameters.NUMN2;
//this.INTRAORILIMIT = parameters.INTRAORILIMIT;
//this.INTRASCALELIMIT = parameters.INTRASCALELIMIT;
//this.INTERORILIMIT = parameters.INTERORILIMIT;
//this.INTERSCALELIMIT = parameters.INTERSCALELIMIT;
//this.GLOBALORILIMIT = parameters.GLOBALORILIMIT;
//}

