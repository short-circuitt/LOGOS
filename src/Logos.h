#ifndef LOGOS_H
#define LOGOS_H

#include <vector>
#include <cstdlib>
#include "Point.h"
#include "Match.h"
#include "PointPair.h"

#ifndef PI_H
#define PI_H
const double PI  =3.141592653589793238463;
#endif

struct LogosParameters {
 double INTRAORILIMIT = 0.1;
 double INTRASCALELIMIT = 0.1;
 double INTERORILIMIT = 0.1;
 double INTERSCALELIMIT = 0.1;
 double GLOBALORILIMIT = 0.1;
 double NUM1 = 5;
 double NUM2 = 5; 
};

class Logos{

private:
  std::vector<Point*>::iterator pit1;
  std::vector<Point*>::iterator pit2;
  std::vector<PointPair*> pp;
  std::vector<PointPair*>::iterator it;
  std::vector<PointPair*> matches;

  double INTRAORILIMIT;
  double INTRASCALELIMIT;
  double INTERORILIMIT;
  double INTERSCALELIMIT;
  double GLOBALORILIMIT;
  double NUM1;
  double NUM2;
  double LB;
  double BINSIZE;
  unsigned int BINNUMBER;
  int* bins;

public:
   Logos(){
    LogosParameters* defaultParams = new LogosParameters();
    init(defaultParams);	
   }

   Logos(LogosParameters* p){
    init(p);
   }

   ~Logos(){
   }

  void init(LogosParameters* p){
    setParams(p);
    LB = -PI;
    BINSIZE = GLOBALORILIMIT/3;
    BINNUMBER = (unsigned int)ceil(2*PI/BINSIZE);
    bins = new int[BINNUMBER];
    for (int i=0; i<BINNUMBER; i++){
	bins[i]=0;
    }
  }

   int estimateMatches(std::vector<Point*> vP1, std::vector<Point*> vP2, std::vector<PointPair*> &globalmatches);
   bool evaluateMatch(Match* m);

   double getIntraOriLimit(){ return INTRAORILIMIT; }
   double getIntraScaleLimit(){ return INTRASCALELIMIT; }
   double getInterOriLimit(){ return INTERORILIMIT; }
   double getInterScaleLimit(){ return INTERSCALELIMIT; }
   double getGlobalOriLimit(){ return GLOBALORILIMIT; }
   double getNum1(){ return NUM1; }
   double getNum2(){ return NUM2; }

   void updatebin(double input);
   double calcGlobalOrientation();

   void setParams(LogosParameters* p){
    INTRAORILIMIT = p->INTRAORILIMIT;
    INTRASCALELIMIT = p->INTRASCALELIMIT;
    INTERORILIMIT = p->INTERORILIMIT;
    INTERSCALELIMIT = p->INTERSCALELIMIT;
    GLOBALORILIMIT = p->GLOBALORILIMIT;
    NUM1 = p->NUM1;
    NUM2 = p->NUM2;  
  }
 
};

#endif
