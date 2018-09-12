#include <iostream>
#include "quadratic_equation_solver.h"


int main() {
  double a, b, c;
  std::cout << "Enter a, b and c separated with a space: ";
  std::cin >> a >> b >> c;
  double x1, x2;
  int rootsNumber = solveQuadraticEquation(a, b, c, x1, x2);
  switch (rootsNumber) {
    case 0: 
      std::cout << "No roots" << std::endl;
      break;
    case 1: 
      std::cout << "x = " << x1 << std::endl;
      break;
    case 2: 
      std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;
      break;
    case INFINITE_ROOTS: 
      std::cout << "Any real number" << std::endl;
      break;
    default:
      std::cerr << "INVALID QUADRATIC SOLUTION SOLVER, rootsNumber = " << rootsNumber << std::endl;
  }
}
