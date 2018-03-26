#ifndef MATCH_H
#define MATCH_H

#include <stdlib.h> 	// std::abs
#include <algorithm>    // std::min
#include <math.h>       // log, acos
#include "Point.h"
#include <iostream> 

const double PI  =3.141592653589793238463;

class Match{

private:
  Point* p;
  Point* q;
  Point* r;
  Point* s;
  double relOrientation;
  double relScale;
  double interOrientation;
  double interScale;
  double ro1;
  double rs1;

  // Internal variables  
  double ro2;
  double ro3;
  double rs2;
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

   Match(Point* p, Point* q, Point* r, Point* s);

   ~Match(){
   }

  double getRelOrientation(){ return relOrientation; }
  double getRelScale(){ return relScale; }
  double getInterOrientation(){ return interOrientation; }
  double getInterScale(){ return interScale; }

  void printMatch(){
      std::cout << "Relative Orientation: " << relOrientation << std::endl;
      std::cout << "Relative Scale: " << relScale << std::endl;		
      std::cout << "Inter Orientation: " << interOrientation << std::endl;
      std::cout << "Inter Scale: " << interScale << std::endl;	
      std::cout << "Global Relative Orientation: " << ro1 << std::endl;
 }

};

#endif
