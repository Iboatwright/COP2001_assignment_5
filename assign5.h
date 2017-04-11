//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

// simplified program to model only quadratic equations
struct equation_t {     
  int coeffsCount = 3;  
  int rootsCount = 2;  
  double[coeffsCount] coeffs;  
  double[rootsCount] roots;
  bool linearEq = false;    // if first coefficient == 0 this is true
  bool rootsExist = false;  // if true then real roots exist
  
  equation_t(double a, double b, double c){}
  
  equation_t(){}
};

class solution {
  
  private:
    equation_t eq;

  public:
    solution(equation_t& eq);
    
    ~solution();
    
    double* getCoeffs();
    double* getRoots();
};

#endif  // __ASSIGN5_H_INCLUDED__