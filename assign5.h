//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

class solution {
private:
  int m_coeffSize = 3;
  int m_rootSize = 2;  
  double* coeffs;  // pointer to coefficient array
  double* roots;  // pointer to roots array
  bool rootsExist = false;  // if true then real roots exist

public:
  solution(){
    // These arrays are allocated from the heap and exist until deleted.
    coeffs = new double[m_coeffSize];  
    roots = new double[m_rootSize];
  }
  
  ~solution(){
    delete[] coeffs; 
    delete[] roots;
    
    // not really needed but good practice i think
    coeffs = nullptr;
    roots = nullptr;
  }
  
  int* getCoeffs() return { &coeffs; }
  int* getroots() return { &roots; }
  int get 
};

#endif  // __ASSIGN5_H_INCLUDED__