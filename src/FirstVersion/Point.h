#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <algorithm> // std::sort

struct matchPoint {
    double sd;
    int index;
};

class Point;

struct PointPair {
  Point* p1;
  Point* p2;
  int support;
};

class Point{

private:
  double x;
  double y; 
  double orientation;
  double scale;
  std::vector<Point*> nnVector;
  std::vector<Point*>::iterator nnIterator;
  bool nnFound;
  int label;  // Label label;

public:
   Point(){
	this->x = 0.0;
	this->y = 0.0;
	this->orientation = 0.0;
	this->scale = 1.0;
        this->nnFound = false;
        this->label = 0;
   }

   Point(double x, double y, double orientation, double scale,  int label=0){
	this->x = x;
  	this->y = y;
	this->orientation = orientation;
	this->scale = scale;
        this->nnFound = false;
        this->setLabel(label);
   }

   ~Point(){
	//TODO
   }

   double getx(){ return this->x; }
   double gety(){ return this->y; }
   double getorientation(){ return this->orientation; }
   double getscale(){ return this->scale; }  
   double getlabel(){ return this->label; } 
   void setLabel(int label){ this->label = label; }

   void printPoint(){
	std::cout << this->getx() << " " 
		<< this->gety() << " " << this->getorientation() 
		<< " " << this->getscale() << " " << this->getlabel() << std::endl;
   }

   void printNN(){
       for(nnIterator=nnVector.begin();nnIterator!=nnVector.end();++nnIterator){
		(*nnIterator)->printPoint();
	}
   }

   void nearestNeighbours(std::vector<Point*> vP, int index, int N);

   void nearestNeighboursNaive(std::vector<Point*> vP, int index, int N);

   double sqD(double x1, double y1, double x2, double y2);

   void matchLabel(int label, std::vector<Point*>& mNN);

   void computeLocalSupport(Point* q, std::vector<PointPair*>& pp, int N);
};

#endif
