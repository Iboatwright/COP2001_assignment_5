/***************************************************************************
 file   : assign5test.cpp
 title  : COP 2001 Assignment #5 - 2017
 author : Ivan Boatwright
 email  : ijboatwright5153@eagle.fgcu.edu
 version: 5.23 4/16/17
 
 solve quadratic equations of the form:
        a*x^2 + b*x + c = 0
 
 The values for a, b, and c are entered by the operator when prompted.
 If non-numeric values are entered for a, b, or c an error message is
 displayed.
 Roots are found using an optimized form of the bisect method utilizing
 a tolerance value (epsilon) entered from the commandline. If epsilon does
 not pass validation an error message is displayed and program exits.
 If roots exist the results are printed to a file. If no roots exist a
 message is printed to stdout.
 ***************************************************************************/

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <limits>
#include "assign5.h"


// commandline argument validation (must be a positive integer)
double validateEpsilon(int, char*);

// returns the prog_name from argv[0]
std::string getProgName(char*);

// Requests user to input the coefficients
void coeffInput(double&, char);

// Reads and returns valid coefficients from stdin.
void readCoeffs(Solution&);

// Appends real roots to the file. Otherwise prints a message
// to stdout that no real roots exists.
void outResults(std::ofstream&, Solution&);


int main(int argc, char* argv[]) {
  
  // local constants
  const char* OUTPUT_FILE = "results.dat";
  const std::string prog_name = getProgName(argv[0]);
  
  // minimum interval to bisect
  double epsilon = validateEpsilon(argc, argv[1]);
  
  // check for invalid epsilon entries
  if (!epsilon || epsilon > 10) {
    std::cout << "\t\t Execution: " << prog_name << " ";
    
    if (argc < 2) std::cout << "no epsilon" << std::endl;
    else if ( epsilon > 10 ) {
      std::cout << epsilon << ". Epsilon must be: 10 > epsilon > 0.\n";
    } else std::cout << argv[1] << std::endl;
    
    return 1;
  }
  
  std::ofstream outStream;
  outStream.open(OUTPUT_FILE);  // if file exists, it is overwritten
  
  // instantiate Solution object
  Solution quad;
  quad.setEpsilon(epsilon);
  
  // Operator enters values for the coefficients.
  readCoeffs(quad);
  
  // Determines if there are real roots. If so calculates the roots.
  quad.inspectEquation();
  
  // Directs output to the file or stdout respectively, based on rootsExist.
  outResults(outStream, quad);
  
  outStream.close();
  
  // Friendly end of program message.
  std::cout << "Have a nice day!" << std::endl;
  
  return 0;
}

std::string getProgName(char* argv0){
  std::string fname = std::string(argv0);
  fname = fname.substr(fname.find_last_of('/')+1);
  //std::cout << "Execution: >> " << fname << std::endl;
  return fname;
}

// For invalid input 0.0 is returned
double validateEpsilon(int argc, char* argv1){
  
  // atof returns 0 for anything it can't convert to a double
  double epsilon = (argc > 1)?std::atof(argv1):0.0;
  
  if (argc > 1 && epsilon < 0) { // not a positive double
    epsilon = 0.0; // discards any negative values
  }
  
  return epsilon; // postive int or 0
}


// User input is requested and validated
void coeffInput(double& d, char c){
  std::cout << "\nEnter coefficient " << c << ": ";
  std::cin >> d;
  
  // the program wasn't able to assign the user input as a double
  while (!std::cin){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << "\nError! Please enter a valid number for the coefficient.\n";
    std::cout << "\nEnter coefficient " << c << ": ";
    std::cin >> d;
  }
  
  // clear the input buffer of everything after the double is assigned
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

// Inputs are validated and stored in the Solution::Equation coeffs array.
void readCoeffs(Solution &quad){
  
  coeffInput(*quad.eq.coeffs, 'a');
  coeffInput(*(quad.eq.coeffs + 1), 'b');
  coeffInput(*(quad.eq.coeffs + 2), 'c');
  return;
}

void outResults(std::ofstream& outStream, Solution &quad){
  if (quad.eq.rootsCount){
    // Results are appended to the opened file.
    outStream << "\nQuadratic equation with the following coefficients:"
    << std::endl << "a: " << quad.eq.coeffs[0] << "; b: " << quad.eq.coeffs[1]
    << "; c: " << quad.eq.coeffs[2] << std::endl
    << "has the following roots" << std::endl << "Root1: "
    << quad.eq.roots[0] << "; Root2: ";
    if (quad.eq.rootsCount > 1){
      outStream << quad.eq.roots[1];
    } else {
      outStream << "Not found";
    }
    outStream << ";\n" << std::endl;
  } else {
    std::cout << "\nThe solution of a quadratic equation with coefficients:"
    << std::endl << "a=" << quad.eq.coeffs[0] << ", b=" << quad.eq.coeffs[1]
    << ", c=" << quad.eq.coeffs[2]  << std::endl
    << "has not been found.\n" << std::endl;
  }
  return;
}

