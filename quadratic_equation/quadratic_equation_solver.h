/** @file */ 

#include <cmath>

const long double EPS = 1e-50L;
const int INFINITE_ROOTS = -1;

/*! Checks whether a long double number equals zero (with accuracy equal to EPS)
 */
bool isZero(long double d) {
  return fabs(d) < EPS;
}

/*! Checks whether a long double number is less than zero (with accuracy equal to EPS)
 */
bool belowZero(long double d) {
  return d < -EPS;
}

/*! Solves a linear equation ax + b = 0.
 * \param [in] a - first coefficient of the linear equation
 * \param [in] b - second coefficient of the linear equation
 * \param [in] x0 - a variable which will be assigned to a root
 * \return roots number
 */
int solveLinearEquation(long double a, long double b, long double& x0) {
  if (isZero(a)) {
    return isZero(b)? INFINITE_ROOTS : 0;
  }
  x0 = -b / a;
  return 1;
}

/*! Solves a quadratic equation ax^2 + bx + c = 0.
 * \param [in] a - first coefficient of the quadratic equation
 * \param [in] b - second coefficient of the quadratic equation
 * \param [in] c - third coefficient of the quadratic equation
 * \param [in] x1 - a variable which will be assigned to a first root
 * \param [in] x2 - a variable which will be assigned to a second root
 * \return roots number
 */
int solveQuadraticEquation(long double a, long double b, long double c, long double &x1, long double &x2) {
  if (isZero(a)) {
    return solveLinearEquation(b, c, x1);
  }
  long double d = b * b - 4 * a * c;
  
  if (belowZero(d)) {
    return 0;
  }
  if (isZero(d)) {
    x1 = -b / 2 / a;
    return 1;
  }
  x1 = -(b + sqrt(d)) / 2 / a;
  x2 = -(b - sqrt(d)) / 2 / a;
  return 2;
}
