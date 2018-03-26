#ifndef LOGOS_H
#define LOGOS_H

#include <vector>
#include "Point.h"
#include "Match.h"

class Logos{

private:
  std::vector<Point*>::iterator pit1;
  std::vector<Point*>::iterator pit2;
  std::vector<PointPair*> pp;
  std::vector<PointPair*>::iterator it;
  //std::vector<Match*> matches;
  //std::vector<Match*>::iterator mit;
  std::vector<PointPair*> matches;

  double INTRAORILIMIT;
  double INTRASCALELIMIT;
  double INTERORILIMIT;
  double INTERSCALELIMIT;
  double GLOBALORILIMIT;
  double NUM1;
  double NUM2;

public:
   Logos(){
    INTRAORILIMIT = 0.1;
    INTRASCALELIMIT = 0.1;
    INTERORILIMIT = 0.1;
    INTERSCALELIMIT = 0.1;
    GLOBALORILIMIT = 0.1;
    NUM1 = 5;
    NUM2 = 5;  
   }

   ~Logos(){
   }


   void estimateMatches(std::vector<Point*> vP1, std::vector<Point*> vP2);
   bool evaluateMatch(Match* m);

   double getIntraOriLimit(){ return INTRAORILIMIT; }
   double getIntraScaleLimit(){ return INTRASCALELIMIT; }
   double getInterOriLimit(){ return INTERORILIMIT; }
   double getInterScaleLimit(){ return INTERSCALELIMIT; }
   double getGlobalOriLimit(){ return GLOBALORILIMIT; }
   double getNum1(){ return NUM1; }
   double getNum2(){ return NUM2; }

};

#endif
