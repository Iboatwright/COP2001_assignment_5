//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

// simplified to model only quadratic equations
struct Equation {
  int coeffsCount = 3;
  int rootsCount = 2;
  double* coeffs;           // pointer to coefficient array
  double* roots;            // pointer to roots array
  bool linearEq = false;    // if first coefficient == 0 this is true
  bool rootsExist = false;  // if true then real roots exist
  
  // [Con|De]structors
  Equation();
  ~Equation();

};

class Solution {
  
  private:
    double xLeft = -10,     // end points of interval
           xRight = 10;
    double epsilon;         // error tolerance
    double root;            // root found by bisect
    bool error;             // no root found flag
  
  public:
  
    // Every Solution needs an Equation
    Equation eq;
  
    // Class function prototypes
    double bisect();
    double f(double);

};

#endif  // __ASSIGN5_H_INCLUDED__