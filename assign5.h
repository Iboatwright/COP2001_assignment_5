/***************************************************************************
 file   : assign5.h
 title  : COP 2001 Assignment #5 - 2017
 author : Ivan Boatwright
 email  : ijboatwright5153@eagle.fgcu.edu
 version: 5.23 4/16/17
 
 Equation Struct prototype
 Solution Class prototype
 ***************************************************************************/

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

// simplified to model only quadratic equations
struct Equation {
  const int coeffSize = 3;        // coeffs array size
  const int maxRoots = 2;         // roots array size
  int rootsCount = 0;       // increments for each root found
  double* coeffs;           // pointer to coefficient array
  double* roots;            // pointer to roots array
  bool rootDNE = false;     // if one or both roots does not exist
  
  // [Con|De]structors
  Equation();
  ~Equation();

};

// tries to find the roots of a quadratic equation through bisection
class Solution {
  
  private:
    double maxLeft = -10,   // end points of interval
           maxRight = 10;
    double epsilon = 0;     // error tolerance, passed from cmdln
    double unitSize = 0.4;  // bisect search interval, smaller = more accuracy
    int units;              // ceil((|maxLeft| + |maxRight|) / unitSize)
    bool error;             // no root found flag
  
  public:
  
    // Every Solution needs an Equation
    Equation eq;
  
    // Class function prototypes
    void inspectEquation();
    void setUnits(double, double);
    void setEpsilon(double e){ epsilon = e; };
    void findRoots(double, double, bool);
    bool bisect(double, double, double&);
    double f(double);
};

#endif  // __ASSIGN5_H_INCLUDED__