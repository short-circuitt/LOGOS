/*
 */

#include <string>
#include <iostream>
#include <vector>
#include "../src/Point.h"
#include "../src/Match.h"
#include "../src/Logos.h"
#include "../src/PointPair.h"
#include <ctime>

#include <mex.h>

void processParameters(const mxArray* params, double nfields, double NStructElems, LogosParameters* lp);
void processParameters2(LogosParameters* lp, std::string fname, double p);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
     
    if (nrhs!=9)
        mexErrMsgTxt("LOGOS requires nine input arguments");
            
    double* vP1; 
    double* vP2;
    double* oP1; 
    double* oP2;
    double* sP1; 
    double* sP2;
    double* w1;
    double* w2;
    double* params;
    
    mwSize nPts1 = mxGetN(prhs[0]);
    vP1 = mxGetPr(prhs[0]);
    oP1 = mxGetPr(prhs[1]);
    sP1 = mxGetPr(prhs[2]);
    w1 = mxGetPr(prhs[3]);
 
    mwSize nPts2 = mxGetN(prhs[4]);
    vP2 = mxGetPr(prhs[4]);
    oP2 = mxGetPr(prhs[5]);
    sP2 = mxGetPr(prhs[6]);
    w2 = mxGetPr(prhs[7]);
    
    double nfields = mxGetNumberOfFields(prhs[8]);
    double NStructElems = mxGetNumberOfElements(prhs[8]);
    
    LogosParameters* lp = new LogosParameters();
        
    processParameters(prhs[8],nfields,NStructElems,lp);
           
    std::vector<Point*> points1;
    points1.reserve(nPts1);

    std::vector<Point*> points2;
    points2.reserve(nPts2);
    
    for (int p=0; p<nPts1; p++){
        Point* pt = new Point(vP1[p*2+0],vP1[p*2+1],oP1[p],sP1[p],w1[p]);
        points1.push_back(pt);
    } 

    for (int p=0; p<nPts2; p++){
        Point* pt = new Point(vP2[p*2+0],vP2[p*2+1],oP2[p],sP2[p],w2[p]);
        points2.push_back(pt);
    }     
        
    Logos* logos = new Logos(lp); 
       
    std::vector<PointPair*> globalmatches;
    std::vector<PointPair*>::iterator it;
    
    struct timespec start,finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int inliers = logos->estimateMatches(points1,points2,globalmatches);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 
    std::cout << "C++ implementation takes " << elapsed << " secs " << std::endl;
       
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL); 
    plhs[1] = mxCreateDoubleMatrix(inliers, 1, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(inliers, 1, mxREAL); 
    
    double* ms0 = mxGetPr(plhs[0]);
    double* ms1 = mxGetPr(plhs[1]);
    double* ms2 = mxGetPr(plhs[2]);
    
    // iterate through global matches
    int count=0;
    for (it=globalmatches.begin(); it!=globalmatches.end(); ++it,count++){
       ms1[count]=(*it)->getpos1();
       ms2[count]=(*it)->getpos2();
       
       // uniqueness count
       if (count>0 && ms1[count]!=ms1[count-1]){
           (*ms0)++;
       } else if (count==0) {
           (*ms0)=1;   
       }
    }
}

void processParameters(const mxArray* params, double nfields, double NStructElems, LogosParameters* lp){
    mxArray *tmp;
    int ifield;
    int jstruct;  
    std::string fname; 
    for(ifield=0; ifield<nfields; ifield++) {
        for(jstruct = 0; jstruct < NStructElems; jstruct++) {
            fname = mxGetFieldNameByNumber(params,ifield);
            tmp = mxGetFieldByNumber(params,jstruct,ifield);
            processParameters2(lp, fname, *mxGetPr(tmp));
        }
    }   
}

void processParameters2(LogosParameters* lp, std::string fname, double p){
    if (!fname.compare("INTRAORILIMIT")){
        lp->INTRAORILIMIT = p;   
    } else if (!fname.compare("INTRASCALELIMIT")){
        lp->INTRASCALELIMIT = p;  
    } else if (!fname.compare("INTERORILIMIT")){
        lp->INTERORILIMIT = p;   
    } else if (!fname.compare("INTERSCALELIMIT")){
        lp->INTERSCALELIMIT = p;   
    } else if (!fname.compare("GLOBALORILIMIT")){
        lp->GLOBALORILIMIT = p;  
    } else if (!fname.compare("NUMN1")){
        lp->NUM1 = p;    
    } else if (!fname.compare("NUMN2")){
        lp->NUM2 = p;   
    }
}
