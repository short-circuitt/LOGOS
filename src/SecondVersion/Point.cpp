#include "Point.h"

bool cMP(matchPoint m, matchPoint n){
	return (m.sd<n.sd);
}

void Point::nearestNeighbours(std::vector<Point*> vP, int index, int N){
	nearestNeighboursNaive(vP, index, N);
}

void Point::nearestNeighboursNaive(std::vector<Point*> vP, int index, int N){

      // only want to calculate once.
      if (this->nnFound){
	return;
      }
      matchPoint mP;
      std::vector<matchPoint> minMatch;
      std::vector<matchPoint>::iterator mmit;

      minMatch.reserve(vP.size());

      double sd = 0.0;
      int i = 0;
      for (std::vector<Point*>::iterator it=vP.begin(); it!=vP.end(); ++it, i++){
	   // A point is not it's own neighbour
	   if (i==index){
		continue;
	   }
          sd = sqD(this->getx(),this->gety(),(*it)->getx(),(*it)->gety());
          mP.sd = sd;
          mP.index = i; 
          minMatch.push_back(mP);
      }
   
      std::sort(minMatch.begin(),minMatch.end(),cMP);
      nnVector.clear();
      int count = 0;
      for (mmit=minMatch.begin(); count<N; ++mmit,count++){
        nnVector.push_back(vP.at((*mmit).index));
     }	

     this->nnFound = true;
}

double Point::sqD(double x1, double y1, double x2, double y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}


void Point::matchLabel(int label, std::vector<Point*>& matchNN){
        matchNN.clear();
	for (nnIterator=nnVector.begin(); nnIterator!=nnVector.end(); ++nnIterator){
                //std::cout << (*nnIterator)->label << " " << label << std::endl;
		if ((*nnIterator)->label==label){
 			matchNN.push_back((*nnIterator));
	 	}
        }
}

