//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

// simplified to model only quadratic equations
struct Equation {
  int coeffSize = 3;        // coeffs array size
  int maxRoots = 2;         // roots array size
  int rootsCount = 0;       // increments for each root found
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
    double maxLeft,   // end points of interval
           maxRight;
    double epsilon = 0;     // error tolerance, passed from cmdln
    double unitSize = 1.0;  // bisect search interval
    int units;              // (|maxLeft| + |maxRight|) / unitSize
    bool error;             // no root found flag
  
  public:
  
    // Every Solution needs an Equation
    Equation eq;
  
    // Class function prototypes
    void findRoots();
    bool bisect(double&, double&, double&);
    double f(double);
    Solution(double setMaxLeft = -10, double setMaxRight = 10,
           double setUnitSize = 0.4);
    void setEpsilon(double e){ epsilon = e; };

};

#endif  // __ASSIGN5_H_INCLUDED__