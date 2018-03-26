#include "PointPair.h"

void PointPair::computeLocalSupport(std::vector<PointPair*>& pp, int N){

std::vector<Point*> nnVector;
this->p->getnnVector(nnVector); // Exposes the nearest neighbours

// for each nearest neighbour
for (nnIterator=nnVector.begin(); nnIterator!=nnVector.end(); ++nnIterator){
    // is there a matching nearestNeighbour?
    std::vector<Point*> matchNN;
    matchNN.reserve(N);
    this->q->matchLabel((*nnIterator)->getlabel(),matchNN);
    for (std::vector<Point*>::iterator mit=matchNN.begin(); mit!=matchNN.end(); ++mit){
        PointPair* m = new PointPair((*nnIterator),(*mit)); 
        pp.push_back(m);
    }
}

}

void PointPair::calculateInternalVariables(){
	this->relori = anglediff(p->getorientation(),q->getorientation());
	this->relscale = log(p->getscale())-log(q->getscale());
}

double PointPair::anglediff(double a1,double a2){

    double ad = a1-a2;
    while (ad>PI){
        ad = ad-2*PI;
    }
    while (ad<-PI){
        ad = ad+2*PI;
    }
    return ad;
}

