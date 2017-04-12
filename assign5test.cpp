/***************************************************************************
 file   : boatwright3.cpp
 title  : COP 2001 Assignment #3 - 2017
 author : Ivan Boatwright
 email  : ijboatwright5153@eagle.fgcu.edu
 version: 3.14 3/22/17
 
 Solves quadratic equations of the form:
 a*x^2 + b*x + c = 0
 The number of equations to calculate is passed from the commandline.
 Only a positive integer is accepted from the commandline. Otherwise the
 program terminates early.
 The values for a, b, and c are entered by the operator when prompted.
 If zero is entered for the 'a' variable an error message is displayed.
 If non-numeric values are entered for a, b, or c an error message is
 displayed.
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
int validateNumber(int, char*);


// Requests user to input the coefficients
void coeffInput(double&, char);

// Reads and returns valid coefficients from stdin.
void readCoeffs();


// If the discriminant is zero or greater, the roots are computed,
// stored in the equation object, and rootsExist is set to true.
void equSolver();

// Appends real roots to the file. Otherwise prints a message
// to stdout that no real roots exists.
void outResults(std::ofstream&);


int main(int argc, char* argv[]) {
  
  // local constants
  const char* OUTPUT_FILE = "results.dat";
  
  // number of equations to calculate
  int number = validateNumber(argc, argv[1]);
  
  
  std::ofstream outStream;
  outStream.open(OUTPUT_FILE);  // if file exists, it is overwritten

    // Operator enters values for the coefficients.
    readCoeffs();
    
    // Determines if there are real roots. If so calculates the roots.
    equSolver();
    
    // Directs output to the file or stdout respectively, based on rootsExist.
    outResults(outStream);
  
  outStream.close();
  
  // Friendly end of program message.
  if ( number > 1){
    std::cout << "( " << number << " ) equation" << ((number == 1)?" ":"s ")
    << "calculated. Have a nice day!" << std::endl;
  }
  
  return 0;
}

// For invalid input, a message is displayed and 0 is returned
int validateNumber(int argc, char* argv1){
  // atoi returns 0 for anything it can't convert to an int
  int number = (argc > 1)?std::atoi(argv1):0;
  if (argc > 1 && number < 1) { // not a positive integer
    number = 0; // discards any negative values
    std::cout << "Program terminated.\n" << argv1 << " is an invalid "\
    "number of equations.\nPlease enter a positive integer "\
    "for the number of equations to calculate\n\tand run the program again." << std::endl;
  } else if (argc == 1) { // nothing entered on the commandline
    std::cout << "Program terminated.\nCommandline argument missing.\n"\
    "Please enter a positive integer for the number of equations"\
    " to calculate\n\tand run the program again.\n" << std::endl;
  }
  
  return number; // postive int or 0
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

// Operator inputs coefficients.  If zero is entered for coeffiecient a, an
// error message is displayed requesting a new entry.
void readCoeffs(){
  
  while (true){  // Runs ad-infinitum until break condition is met.
    coeffInput(*eq.coeffs, 'a');
    if (*eq.coeffs) {break;}  // a must not equal zero
    else {  // operator entered zero for coefficient a
      std::cout << "\nInvalid entry. Please enter a non-zero "\
      "value for a." << std::endl;
      coeffInput(*eq.coeffs, 'a');
    }
  }
  
  coeffInput(*(eq.coeffs + 1), 'b');
  coeffInput(*(eq.coeffs + 2), 'c');
  return;
}


void equSolver(){

  return;
}

void outResults(std::ofstream& outStream){
  if (eq.rootsExist){
    // Results are appended to the opened file.
    outStream << "\nQuadratic equation with the following coefficients:"
    << std::endl << "a: " << eq.coeffs[0] << "; b: " << eq.coeffs[1]
    << "; c: " << eq.coeffs[2] << std::endl
    << "has the following roots" << std::endl << "Root1: "
    << eq.roots[0] << "; Root2: " << eq.roots[1] << ";\n"
    << std::endl;
  } else {
    std::cout << "\nQuadratic equation with the following coefficients:"
    << std::endl << "a: " <<eq.coeffs[0] << "; b: " << eq.coeffs[1]
    << "; c: " << eq.coeffs[2]  << std::endl
    << "has no roots in the real domain.\n" << std::endl;
  }
  return;
}

