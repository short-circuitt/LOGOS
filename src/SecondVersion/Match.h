#ifndef MATCH_H
#define MATCH_H

#include <stdlib.h> 	// std::abs
#include <algorithm>    // std::min
#include <math.h>       // log, acos
//#include <cmath.h>       // log, acos
#include "PointPair.h"
#include <iostream> 

class Match{

private:
  PointPair* r;
  PointPair* s;
  double relOrientation;
  double relScale;
  double interOrientation;
  double interScale;

  // Internal variables  
  double ro3;
  double rs3; 
  double vijx; 
  double vijy;
  double vmnx;
  double vmny;

 // Internal functions
void calculateInternalVariables();
void setRelOrientation();
void setRelScale();
double anglediff(double a1,double a2);
double angleabsdiff(double a1, double a2);
void interorientationandscale();
double sign(double x);

public:
   Match(){
		
   }

   Match(PointPair* r, PointPair* s);

   ~Match(){
   }

  double getRelOrientation(){ return relOrientation; }
  double getRelScale(){ return relScale; }
  double getInterOrientation(){ return interOrientation; }
  double getInterScale(){ return interScale; }
  double getro3(){ return ro3; }

  void printMatch(){
      std::cout << "Relative Orientation: " << relOrientation << std::endl;
      std::cout << "Relative Scale: " << relScale << std::endl;		
      std::cout << "Inter Orientation: " << interOrientation << std::endl;
      std::cout << "Inter Scale: " << interScale << std::endl;	
      std::cout << "Global Relative Orientation: " << this->r->getrelori() << std::endl;
 }

  void printMatch2(){
      std::cout << vijx << " " << vijy << " " << vmnx << " " << vmny << " " << std::endl;
      double cp =  vijx*vmny-vijy*vmnx; // analogous to 2D cross product
      double nmij = sqrt(vijx*vijx+vijy*vijy);
      double nmnm = sqrt(vmnx*vmnx+vmny*vmny);
      

      double fr = (vijx*vmnx+vijy*vmny)/(nmij*nmnm);  // numerator equivalent to dot product
      fr = std::min(std::max(fr,-1.0),1.0);
      ro3 = acos(fr)*sign(cp); 

      std::cout << cp << " " << nmij << " " << nmnm << " " << fr << " " << sign(cp) << std::endl;
      std::cout << ro3 << std::endl;
 }

};

#endif
