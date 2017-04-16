//assign5.cpp
#include "assign5.h"
#include <iostream>
#include <cmath>

// Assigns address of new arrays to coeffs and roots pointers
Equation::Equation(){
  // These arrays are allocated from the heap and exist until deleted.
  coeffs = new double[coeffSize];
  roots = new double[maxRoots];
}
  
Equation::~Equation() {
    delete[] coeffs;
    delete[] roots;
    
    // not really needed but good practice i think
    coeffs = nullptr;
    roots = nullptr;
}

void Solution::inspectEquation(){
  
  //create test statement from coeffs
  std::string testStatement = "";
  for(int i = 0; i < 3; i++){
    std::string mark = (eq.coeffs[i] > 0)?"+":"-";
    mark = (eq.coeffs[i] == 0)?"0":mark;
    testStatement = testStatement + mark;
  }
  
  // I really wanted to use a switch statement here, but C++ is such an
  // unnecessarily complicated, bloated mess that the code was too hideous
  // to write. Ifs for the lose.
  
  std::string z5 = "0++,0+-,0-+,0--"; // linear equation
  std::string z4 = "+00,-00,0+0,0-0"; // one root at origin
  std::string z3 = "+0-,-0+";         // two roots symmetric about origin
  std::string z2 = "++0,--0,+-0,-+0"; // two roots, one at origin
  std::string z1 = "++-,--+,+--,-++"; // two roots
  std::cout << "z-value: " << testStatement << std::endl;
  if (z5.find(testStatement)!=std::string::npos){
    std::cout << "z-hit: 5\n";
    eq.rootsCount++;
    eq.roots[0] = (eq.coeffs[2] / eq.coeffs[1] * -1);
  } else if (z4.find(testStatement)!=std::string::npos){
    std::cout << "z-hit: 4\n";
    eq.rootsCount++;
    eq.roots[0] = 0.0;
  } else if (z3.find(testStatement)!=std::string::npos){
    // bisect > 0 then if found set roots[1] = roots[0] * -1
    setUnits(maxLeft/2.0, maxRight/2.0);
    maxLeft = .0000001;
    findRoots(maxLeft, maxLeft + unitSize, true);
    std::cout << "z-hit: 3\n";
    if (eq.rootsCount) {
      eq.rootsCount++;
      eq.roots[1] = eq.roots[0] * -1;
    }
  } else if (z2.find(testStatement)!=std::string::npos){
    std::cout << "z-hit: 2\n";
    eq.rootsCount++;
    eq.roots[0] = 0;
    setUnits(maxLeft/2.0, maxRight/2.0);
    if (eq.coeffs[0] * eq.coeffs[1] > 0) {
      // bisect < 0
      maxRight = -.0000001;
    } else {
      // bisect > 0
      maxLeft = .0000001;
    }
    findRoots(maxLeft, maxLeft + unitSize, true);
  } else if (z1.find(testStatement)!=std::string::npos){
    std::cout << "z-hit: 1\n";
    // bisect full
    setUnits(maxLeft, maxRight);
    findRoots(maxLeft, maxLeft + unitSize, false);
  } else {
    // no roots
  }
  return;
}

void Solution::setUnits(double left, double right){
  units = std::ceil((std::abs(left) + std::abs(right))/ unitSize);
}

void Solution::findRoots(double xLeft, double xRight, bool bisectOnce){
  double biRoot = -999.0;

  // search for roots between maxLeft and maxRight one unit interval at time
    for (int i = 0; i < units; i++) {
      if (bisect(xLeft, xRight, biRoot)){
        if (!eq.rootsCount){ 
          eq.roots[eq.rootsCount] = biRoot;
          eq.rootsCount++;
          if (bisectOnce) std::cout<<"r\n";
          return;
        }
        else if (eq.roots[eq.rootsCount-1] != biRoot){
          eq.roots[eq.rootsCount] = biRoot;
          eq.rootsCount++;
          
          std::cout << "biRoot: " << biRoot << std::endl;
          return;
        }                        
      };
      xLeft += unitSize;
      xRight = (xRight + unitSize < maxRight)? xRight + unitSize: maxRight;
    }
  return;
}

//TODO clean up cout statements.
bool Solution::bisect(double xLeft, double xRight, double& biRoot)
{
  double xMid;                // midpoint of interval
  double fLeft, fRight;       // function values at xLeft, xRight
  double fMid;                // and xMid
    
  // Compute function values at initial endpoints of interval
  fLeft = f(xLeft);
  if (fLeft == 0.0) {
    biRoot = xLeft;
    return xLeft;                                 //xLeft is the root
  }
  fRight = f(xRight);
  if (fRight == 0.0) {
    biRoot = xRight;
    return xRight;                                //xRight is the root
  }
    
    // If no change of sign in the interval, there is no unique root
    error = (fLeft * fRight) > 0;   //test for same sign - set error
    if (error) return false;        //no root - return to caller
    
    //Repeat while interval > error tolerance
    while (fabs (xLeft - xRight) > epsilon)
    {
      //Compute function value at midpoint
      xMid = (xLeft + xRight) / 2.0;
      fMid = f(xMid);
      
      //Test function value and reset interval if root not found
      if (fMid == 0.0) {
        biRoot = xMid;
        return xMid;                              //xMid is the root
      }
      else if (fLeft * fMid < 0.0) xRight = xMid; //root in [xLeft, xMid]
      else xLeft = xMid;                          //root in [xMid, xRight]
      
      //Display the next interval
      std::cout << "New interval is [" << xLeft << ", " << xRight
      << "]" << std::endl;
    }
    
    // midpoint of last interval is a root
    biRoot = (xLeft + xRight) / 2.0;
    return true;
};

// Function whose root is being found.
double Solution::f(double x){
  return eq.coeffs[0] * x * x + eq.coeffs[1] * x + eq.coeffs[2];
}
