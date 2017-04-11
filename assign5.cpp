//assign5.cpp
#include "assign5.h"


// simplified program to model only quadratic equations
struct equation_t {
  
  equation_t(double a, double b, double c){
    coeffs = {a, b, c};
    roots = {0, 0};
  }
  
  equation_t(){
    coeffs = {0, 0, 0};
    roots = {0, 0};
  }
};

solution::solution(const int coeffSize, const int rootSize, bool rootsExist)
{
  m_coeffSize = coeffSize;    //default: 3
  m_rootSize = rootSize;      //default: 2
  m_rootsExist = rootsExist;  //default: false
  
};
 
//double* solution::getCoeffs(){ return &solution::coeffs;}
//int* solution::getRoots(){ return &roots;}

class complex {
  double re, im; // representation: two doubles
public:
  complex(double r, double i) :re{r}, im{i} {}  // construct complex from two scalars
  complex(double r) :re{r}, im{0} {}            // construct complex from one scalar
  complex() :re{0}, im{0} {}                    // default complex: {0,0}
  
  double real() const { return re; }
  void real(double d) { re=d; }
  double imag() const { return im; }
  void imag(double d) { im=d; }
  
  complex& operator+=(complex z) { re+=z.re, im+=z.im; return *this; }  // add to re and im
                                                                        // and return the result
  complex& operator-=(complex z) { re-=z.re, im-=z.im; return *this; }
  
  complex& operator*=(complex); // defined out-of-class somewhere
  complex& operator/=(complex); // defined out-of-class somewhere
};