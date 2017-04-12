//
//  bisect.cpp
//  assignment5
//
//  Created by Pokey on 4/11/17.
//  Copyright (c) 2017 cop2001. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "bisect.h"

double Bisect::bisect(){
  double xMid;                // midpoint of interval
  double fLeft, fRight;       // function values at xLeft, xRight
  double fMid;                // and xMid
  
  // Compute function values at initial endpoints of interval
  fLeft = f(xLeft);
  fRight = f(xRight);
  
  // If no change of sign in the interval, there is no unique root
  Bisect::error = (fLeft * fRight) > 0;   //test for same sign - set error
  if (Bisect::error) return -999.0;       //no root - return to caller
  
  //Repeat while interval > error tolerance
  while (fabs (Bisect::xLeft - Bisect::xRight) > Bisect::epsilon)
  {
    //Compute function value at midpoint
    xMid = (Bisect::xLeft + Bisect::xRight) / 2.0;
    fMid = f(xMid);
    
    //Test function value and reset interval if root not found
    if (fMid == 0.0) return xMid;               //xMid is the root. Return the root
    else if (fLeft * fMid < 0.0) xRight = xMid; //root in [xLeft, xMid]
    else xLeft = xMid;                          //root in [xMid, xRight]
    
    //Display the next interval
    std::cout << "New interval is [" << Bisect::xLeft << ", " << Bisect::xRight
              << "]" << std::endl;
    
  }
  
  //Return the midpoint of last interval
  return (Bisect::xLeft + Bisect::xRight) / 2.0;
}

// Function whose root is being found.
double Bisect::f(double x){
  return 3 * x * x + 2 * x + 1; // __IvanNote__ 3, 2, 1 are a, b, c
}

int main(){
  
  // Create class object
  Bisect biObj;
  
  // Get endpoints and tolerance
  std::cout << "Enter interval endpoints: ";
  std::cin >> biObj.xLeft >> biObj.xRight;
  std::cout << "Enter tolerance: ";
  std::cin >> biObj.epsilon;
  
  //Use bisect function to look for root of function f
  biObj.root = biObj.bisect();
  
  //Display result
  if (!biObj.error){
    std::cout << "Root found at " << biObj.root
              << "\nValue of f(x) at root is: " << biObj.f(biObj.root);
  } else {
    std::cout << "There may be no root in [" << biObj.xLeft << ", "
              << biObj.xRight << "]" << std::endl;
  }
  
  return 0;
}