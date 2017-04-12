//assign5.cpp
#include "assign5.h"
#include <iostream>
#include <cmath>


Equation_t::Equation_t(){
  Equation_t::init();
}
  
Equation_t::~Equation_t() {
    delete[] coeffs;
    delete[] roots;
    
    // not really needed but good practice i think
    coeffs = nullptr;
    roots = nullptr;
}


// Assigns address of new arrays to coeffs and roots pointers
void Equation_t::init() {
  // These arrays are allocated from the heap and exist until deleted.
  coeffs = new double[coeffsCount];
  roots = new double[rootsCount];
  return;
}

double Solution::bisect()
{

  double xMid;                // midpoint of interval
  double fLeft, fRight;       // function values at xLeft, xRight
  double fMid;                // and xMid
    
  // Compute function values at initial endpoints of interval
  fLeft = f(xLeft);
  fRight = f(xRight);
    
    // If no change of sign in the interval, there is no unique root
    error = (fLeft * fRight) > 0;   //test for same sign - set error
    if (error) return -999.0;       //no root - return to caller
    
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
    return (xLeft + xRight) / 2.0;
};

// Function whose root is being found.
double Solution::f(double x){
  return 3 * x * x + 2 * x + 1; // __IvanNote__ 3, 2, 1 are a, b, c
}
