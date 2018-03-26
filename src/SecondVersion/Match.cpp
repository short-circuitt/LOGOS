#include "Match.h"

Match::Match(PointPair* r, PointPair* s){
        this->r = r;
        this->s = s;
	calculateInternalVariables();
        setRelOrientation();
        setRelScale();
        interorientationandscale();
}

void Match::calculateInternalVariables(){
	vijx = r->getx1()-s->getx1();
        vijy = r->gety1()-s->gety1();
	vmnx = r->getx2()-s->getx2();
        vmny = r->gety2()-s->gety2();
}

void Match::setRelOrientation(){ 
	relOrientation = angleabsdiff(r->getrelori(),s->getrelori());
}

void Match::setRelScale(){ 
	relScale = std::abs(r->getrelscale()-s->getrelscale());
}


double Match::angleabsdiff(double a1, double a2){

    double ad = std::abs(a1-a2); 
    while (ad>2*PI){
        ad = ad-2*PI;
    }
    ad = std::min(std::abs(ad),std::abs(2*PI-std::abs(ad)));   

    return ad;    
}


void Match::interorientationandscale(){
    
      double cp =  vijx*vmny-vijy*vmnx; // analogous to 2D cross product
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
      
      interOrientation = angleabsdiff((r->getrelori()),ro3);
      interScale = std::abs((r->getrelscale())-rs3);
}

double Match::sign(double x){
	return (x > 0) - (x < 0);
}


