/*
 */

//#include <ctime>
//#include <string>
#include <iostream>
#include <vector>
#include "../src/Point.h"
#include "../src/Match.h"
#include "../src/Logos.h"
#include "../src/PointPair.h"
#include <ctime>
//#include <fstream>

//using std::string;

#include <mex.h>

void processParameters(double* params, double nfields, double NStructElems){
    /* allocate memory  for storing classIDflags */
    classIDflags = mxCalloc(nfields, sizeof(mxClassID));
    
    /* check empty field, proper data type, and data type consistency;
     * and get classID for each field. */
    for(ifield=0; ifield<nfields; ifield++) {
        for(jstruct = 0; jstruct < NStructElems; jstruct++) {
            tmp = mxGetFieldByNumber(prhs[0], jstruct, ifield);
            if(tmp == NULL) {
                mexPrintf("%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1);
                mexErrMsgIdAndTxt( "MATLAB:phonebook:fieldEmpty",
                        "Above field is empty!");
            }
            if(jstruct==0) {
                if( (!mxIsChar(tmp) && !mxIsNumeric(tmp)) || mxIsSparse(tmp)) {
                    mexPrintf("%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1);
                    mexErrMsgIdAndTxt( "MATLAB:phonebook:invalidField",
                            "Above field must have either string or numeric non-sparse data.");
                }
                classIDflags[ifield]=mxGetClassID(tmp);
            } else {
                if (mxGetClassID(tmp) != classIDflags[ifield]) {
                    mexPrintf("%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1);
                    mexErrMsgIdAndTxt( "MATLAB:phonebook:invalidFieldType",
                            "Inconsistent data type in above field!");
                } else if(!mxIsChar(tmp) &&
                        ((mxIsComplex(tmp) || mxGetNumberOfElements(tmp)!=1))){
                    mexPrintf("%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1);
                    mexErrMsgIdAndTxt( "MATLAB:phonebook:fieldNotRealScalar",
                            "Numeric data in above field must be scalar and noncomplex!");
                }
            }
        }
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

//    if (nlhs!=10)
 //   mexErrMsgTxt("LOGOS requires one output argument.");
     
 // if (nrhs!=10)
 //   mexErrMsgTxt("LOGOS requires ten input arguments, \
 //   ARRAY_IN and VECTOR_IN.");
    
// Error check: types, sizes, etc
        
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
    params = mxGetPr(prhs[8]);
    
    
    std::vector<Point*> points1;
    points1.reserve(nPts1);

    std::vector<Point*> points2;
    points2.reserve(nPts2);
    
    for (int p=0; p<nPts1; p++){
     // create new point
     // add to vector
       // std::cout << w1[p] << std::endl;
        Point* pt = new Point(vP1[p*2+0],vP1[p*2+1],oP1[p],sP1[p],w1[p]);
        //pt->printPoint();
        
        points1.push_back(pt);
      //  std::cout << vP1[p*2+0] << " " << vP1[p*2+1] << " " << oP1[p] << " " << sP1[p] << std::endl;
    } 

    for (int p=0; p<nPts2; p++){
     // create new point
     // add to vector
        //std::cout << w2[p] << std::endl;
        Point* pt = new Point(vP2[p*2+0],vP2[p*2+1],oP2[p],sP2[p],w2[p]);
        //pt->printPoint();
        
        points2.push_back(pt);
        //std::cout << vP1[p*2+0] << " " << vP1[p*2+1] << " " << oP1[p] << " " << sP1[p] << std::endl;
    }     
    
    LogosParameters* lp = new LogosParameters();
    lp->INTRAORILIMIT = 0.5;
    lp->INTRASCALELIMIT = 0.5;
    lp->INTERORILIMIT = 0.5;
    lp->INTERSCALELIMIT = 0.5;
    lp->GLOBALORILIMIT = 0.5;
    lp->NUM1 = 5;
    lp->NUM2 = 5;
    
    Logos* logos = new Logos(lp);  // need to set parameters
       
    std::vector<PointPair*> globalmatches;
    std::vector<PointPair*>::iterator it;
    
    struct timespec start,finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    //clock_t begintime = clock();
    int inliers = logos->estimateMatches(points1,points2,globalmatches);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 
    std::cout << "C++ code takes " << elapsed << " secs " << std::endl;
    
    //clock_t endtime = clock();
    //double elapsed_secs = double(endtime-begintime)/ CLOCKS_PER_SEC;
    //std::cout << elapsed_secs << std::endl;
    //std::cout << inliers << std::endl;
     
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL); 
    plhs[1] = mxCreateDoubleMatrix(inliers, 1, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(inliers, 1, mxREAL); 
    
    double* ms0 = mxGetPr(plhs[0]);
    double* ms1 = mxGetPr(plhs[1]);
    double* ms2 = mxGetPr(plhs[2]);
    
    // go through global matches
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
   
    // if unique increment plhs[0] by 1
    
    
    //std::cout << points1.size() << std::endl;
    //int i=0;
    //for (std::vector<Point*>::iterator it=points1.begin(); it<points1.end(); ++it,i++){
    //(*it)->printPoint();
    //std::cout << i << std::endl;
    //}
    
/*    int NN = 5;
    
    int up = 0;
    
    Point* pt = points1.at(up);
    //pt->sqD(1.0,2.0,3.0,4.0);
    pt->nearestNeighbours(points1,up,NN);
    //pt->printNN();
    //std::vector<Point*> mmnn;
    
    //pt->matchLabel(323,mmnn);
    //std::cout<<mmnn.size()<<std::endl;
    //for (std::vector<Point*>::iterator it=mmnn.begin(); it<mmnn.end(); ++it){
    //(*it)->printPoint();
    //}
    
    Point* ptp = points2.at(up);
    ptp->nearestNeighbours(points2,up,NN);
    
    std::vector<PointPair*> pp;
    
    pt->computeLocalSupport(ptp,pp,NN);
    
    //std::cout << pp.size() << std::endl;
    
    //for (std::vector<PointPair*>::iterator it=pp.begin(); it<pp.end(); ++it){
    //(*it)->p1->printPoint();
    //(*it)->p2->printPoint();
    //}
    */
/*    std::vector<Match*> matches;
    matches.reserve(pp.size());
    
    for (std::vector<PointPair*>::iterator it=pp.begin(); it<pp.end(); ++it){
        Match* m = new Match(pt,ptp,(*it)->p1,(*it)->p2);
        matches.push_back(m);
        m->printMatch();
    }*/    
    
    
}



