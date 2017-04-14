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

Solution::Solution(double setMaxLeft = -10, double setMaxRight = 10,
                   double setUnitSize = 1.0){
  maxLeft = setMaxLeft;
  maxRight = setMaxRight;
  unitSize = setUnitSize;
  units = (std::abs(maxLeft) + std:abs(maxRight))/ unitSize;
}

void Solution::findRoots(){
  
  // If coefficient a is 0 then there is only one root.
  eq.linearEq = (*eq.coeffs) ? false : true;  
  if (eq.linearEq){
    eq.rootsExist = true;
    eq.rootsCount++;
    eq.roots[0] = (eq.coeffs[2] / eq.coeffs[1] * -1);
  }
  
  double xLeft = maxLeft;
  double xRight = xLeft + unitSize;
  double biRoot = -999.0;

  // search for roots between maxLeft and maxRight one unit interval at time
  if (!eq.linearEq){
    for (int i = 0; i < units; i++) {
      if (bisect(xLeft, xRight)){
        if (!eq.rootsCount){ 
          eq.roots[eq.rootsCount] = biRoot; 
          eq.rootsCount++;
        }
        else if (eq.roots[eq.rootsCount] != biRoot){
          eq.rootsCount++;
          eq.roots[eq.rootsCount] = biRoot;
          return;
        }                        
      };
      xLeft += unitSize;
      xRight += unitSize;
    }
  }
  return;
}

double Solution::bisect(double& xLeft, double& xRight, double& biRoot)
{
  double xMid;                // midpoint of interval
  double fLeft, fRight;       // function values at xLeft, xRight
  double fMid;                // and xMid
    
  // Compute function values at initial endpoints of interval
  fLeft = f(xLeft);
  fRight = f(xRight);
    
    // If no change of sign in the interval, there is no unique root
    error = (fLeft * fRight) > 0;   //test for same sign - set error
    if (error) return false;              //no root - return to caller
    
    //Repeat while interval > error tolerance
    while (fabs (xLeft - xRight) > epsilon)
    {
      //Compute function value at midpoint
      xMid = (xLeft + xRight) / 2.0;
      fMid = f(xMid);
      
      //Test function value and reset interval if root not found
      if (fMid == 0.0) return xMid;               //xMid is the root. Return the root
      else if (fLeft * fMid < 0.0) xRight = xMid; //root in [xLeft, xMid]
      else xLeft = xMid;                          //root in [xMid, xRight]
      
      //Display the next interval
      std::cout << "New interval is [" << xLeft << ", " << xRight
      << "]" << std::endl;
    }
    
    //Return the midpoint of last interval
    biRoot = (xLeft + xRight) / 2.0;
    return true;
};

// Function whose root is being found.
double Solution::f(double x){
  return eq.coeffs * x * x + eq.coeffs[1] * x + eq.coeffs[2];
}
