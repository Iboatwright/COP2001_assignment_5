//
//  bisect.h
//

#ifndef __assignment5__bisect__
#define __assignment5__bisect__

// Class prototype
class Bisect {
public:
  double xLeft, xRight;   //end points of interval
  double epsilon;         // error tolerance
  double root;            // root found by bisect
  bool error;             // error flag
  
  // Class function prototypes
  double bisect();
  double f(double);

};

#endif /* defined(__assignment5__bisect__) */
