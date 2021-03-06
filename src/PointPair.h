#ifndef POINTPAIR_H
#define POINTPAIR_H

#include <iostream>
#include <vector>
#include <math.h>       // log
#include "Point.h"

#ifndef PI_H
#define PI_H
const double PI  =3.141592653589793238463;
#endif

class PointPair{

private:
  Point* p;
  Point* q;
  int support;
  double relori;
  double relscale;
  std::vector<Point*>::iterator nnIterator;

  int pos1;
  int pos2;

  double anglediff(double a1,double a2);

public:
   PointPair(){
   }

   PointPair(Point* p, Point* q){
	this->p = p;
  	this->q = q;
	this->support = 0;
        calculateInternalVariables();
        this->pos1 = 0;
        this->pos2 = 0;
   }

   ~PointPair(){
   }

   void computeLocalSupport(std::vector<PointPair*>& pp, int N);

   void calculateInternalVariables();

   double getrelori(){ return this->relori; }
   double getrelscale(){ 
	return this->relscale; }

   void setsupport(int support){ this->support = support; }

   double getx1(){ return this->p->getx(); }
   double getx2(){ return this->q->getx(); }
   double gety1(){ return this->p->gety(); }
   double gety2(){ return this->q->gety(); }
   Point* getp(){ return p; }
   Point* getq(){ return q; }

   void addPositions(int pos1, int pos2){  this->pos1 = pos1; this->pos2 = pos2; }
   int getpos1(){ return this->pos1; }
   int getpos2(){ return this->pos2; }
   int getsupport(){ return this->support; }

};

#endif
