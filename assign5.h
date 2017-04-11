//assign5.h

#ifndef __ASSIGN5_H_INCLUDED__
#define __ASSIGN5_H_INCLUDED__

class solution {
  
  private:
    int m_coeffSize;
    int m_rootSize;
    bool m_rootsExist;  // if true then real roots exist
    double* coeffs;  // pointer to coefficient array
    double* roots;  // pointer to roots array

  public:
    solution(const int coeffSize = 3, const int rootSize = 2,
             bool rootsExist = false);
    
    ~solution();
    
    double* getCoeffs();
    double* getRoots();
};

#endif  // __ASSIGN5_H_INCLUDED__