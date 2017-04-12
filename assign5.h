//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

// simplified program to model only quadratic equations
struct Equation_t {
  int coeffsCount = 3;
  int rootsCount = 2;
  double* coeffs;           // pointer to coefficient array
  double* roots;            // pointer to roots array
  bool linearEq = false;    // if first coefficient == 0 this is true
  bool rootsExist = false;  // if true then real roots exist
  
  Equation_t();
  ~Equation_t();
  
  void init();
};

class Solution {
  
  private:
    double xLeft, xRight;   // end points of interval
    double epsilon;         // error tolerance
    double root;            // root found by bisect
    bool error;             // error flag
  
  public:
  
    // Class function prototypes
    double bisect();
    double f(double);
  
    // [Con|De]structors
    Solution();
    ~Solution();
};

#endif  // __ASSIGN5_H_INCLUDED__