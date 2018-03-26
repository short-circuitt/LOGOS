#include "Match.h"

Match::Match(Point* p, Point* q, Point* r, Point* s){
        this->p = p;
        this->q = q;
        this->r = r;
        this->s = s;
	calculateInternalVariables();
        setRelOrientation();
        setRelScale();
        interorientationandscale();
}


void Match::calculateInternalVariables(){
	ro1 = anglediff(p->getorientation(),q->getorientation());
	ro2 = anglediff(r->getorientation(),s->getorientation());
	rs1 = log(p->getscale())-log(q->getscale());
	rs2 = log(r->getscale())-log(s->getscale());
	vijx = p->getx()-r->getx();
        vijy = p->gety()-r->gety();
	vmnx = q->getx()-s->getx();
        vmny = q->gety()-s->gety();
}

void Match::setRelOrientation(){ 
	relOrientation = angleabsdiff(ro1,ro2);
}

void Match::setRelScale(){ 
	relScale = abs(rs1-rs2);
}

double Match::anglediff(double a1,double a2){

    double ad = a1-a2;
    while (ad>PI){
        ad = ad-2*PI;
    }
    while (ad<-PI){
        ad = ad+2*PI;
    }
    return ad;
}

double Match::angleabsdiff(double a1, double a2){

    double ad = abs(a1-a2);
    while (ad>2*PI){
        ad = ad-2*PI;
    }
    ad = std::min(abs(ad),abs(2*PI-abs(ad)));
    
    return ad;    
}


void Match::interorientationandscale(){
    
      double cp =  vijx*vmnx-vijy*vmny; // analogous to 2D cross product
      double nmij = sqrt(vijx*vijx+vijy*vijy);
      double nmnm = sqrt(vmnx*vmnx+vmny*vmny);
      

      double fr = (vijx*vmnx+vijy*vmny)/(nmij*nmnm);  // numerator equivalent to dot product
      fr = std::min(std::max(fr,-1.0),1.0);
      ro3 = acos(fr)*sign(cp);  
      
      rs3 = log(nmij)-log(nmnm);

      //std::cout << ro1 << std::endl;
      //std::cout << ro3 << std::endl;

      //std::cout << sign(cp) << std::endl;
      //std::cout << (vijx*vmnx+vijy*vmny) << std::endl;
      //std::cout << (nmij*nmnm) << std::endl;
      //std::cout << (vijx*vmnx+vijy*vmny)/(nmij*nmnm) << std::endl;
      //std::cout << acos((vijx*vmnx+vijy*vmny)/(nmij*nmnm)) << std::endl;

      interOrientation = angleabsdiff(ro1,ro3);
      interScale = abs(rs1-rs3);
}

double Match::sign(double x){
	return (x > 0) - (x < 0);
}


