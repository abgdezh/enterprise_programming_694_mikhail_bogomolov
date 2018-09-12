#include <utility>
#include <random>
#include <iostream>
#include <gtest/gtest.h>
#include "quadratic_equation_solver.h"

TEST(non_zero_a_tests, small_test_two_roots) {
  for (int x1 = -1000; x1 <= 1000; ++x1) {
    for (int x2 = x1 + 1; x2 <= 1000; ++x2) {
      int a = 1, b = -x1 - x2, c = x1 * x2;
      long double solver_x1, solver_x2;
      int rootsNumber = solveQuadraticEquation(a, b, c, solver_x1, solver_x2);
      if (solver_x1 > solver_x2) {
        std::swap(solver_x1, solver_x2);
      }
      ASSERT_EQ(rootsNumber, 2);
      ASSERT_NEAR(solver_x1, x1, EPS);
      ASSERT_NEAR(solver_x2, x2, EPS);
    }
  }
}

TEST(non_zero_a_tests, small_test_single_root) {
  for (long long x = -1000000; x <= 1000000; ++x) {
    long long a = 1, b = -2 * x, c = x * x;
    long double solver_x, unused;
    int rootsNumber = solveQuadraticEquation(a, b, c, solver_x, unused);
    ASSERT_EQ(rootsNumber, 1);
    ASSERT_NEAR(solver_x, x, EPS);
  }
}

TEST(non_zero_a_tests, random_test_two_roots) {
  for (int i = 0; i < 10000000; ++i) {
    long double x1 = rand(), x2 = rand();
    x1 -= RAND_MAX / 2.0;
    x2 -= RAND_MAX / 2.0;
    if (isZero(x1 - x2)) {
      continue;
    }
    long double a = rand();
    if (isZero(a)) {
      continue;
    }
    long double b = (-x1 - x2) * a, c = (x1 * x2) * a;
    long double solver_x1, solver_x2;
    int rootsNumber = solveQuadraticEquation(a, b, c, solver_x1, solver_x2);
    if ((solver_x1 > solver_x2) ^ (x1 > x2)) {
      std::swap(solver_x1, solver_x2);
    }
    ASSERT_EQ(rootsNumber, 2);
    long double eps = fmax(fabs(x1), fabs(x2)) / 1e9;
    ASSERT_NEAR(solver_x1, x1, eps);
    ASSERT_NEAR(solver_x2, x2, eps);
  }
}

TEST(non_zero_a_tests, random_test_single_root) {
  for (int i = 0; i < 10000000; ++i) {
    long double x = rand() % 1000000;
    long double a = rand() % 1000000;
    if (isZero(a)) {
      continue;
    }
    long double b = -2 * x * a, c = x * x * a;
    long double solver_x, unused;
    int rootsNumber = solveQuadraticEquation(a, b, c, solver_x, unused);
    ASSERT_EQ(rootsNumber, 1);
    long double eps = fabs(x) / 1e9;
    ASSERT_NEAR(solver_x, x, eps);
  }
}

TEST(non_zero_a_tests, random_test_zero_root) {
  for (int i = 0; i < 10000000; ++i) {
    long double point_min = rand() % 1000000;
    long double a = rand() % 1000000;
    if (isZero(a)) {
      continue;
    }
    long double b = -2 * point_min * a, c = point_min * point_min * a + rand() + 1;
    long double unused;
    int rootsNumber = solveQuadraticEquation(a, b, c, unused, unused);
    ASSERT_EQ(rootsNumber, 0);
  }
}

TEST(zero_a_non_zero_b_tests, random_test_linear_equation) {
  for (int i = 0; i < 10000000; ++i) {
    long double b = rand(), c = rand();
    b -= RAND_MAX / 2.0;
    c -= RAND_MAX / 2.0;
    if (b == 0) {
      continue;
    }
    long double solver_x, unused;
    int rootsNumber = solveQuadraticEquation(0, b, c, solver_x, unused);
    ASSERT_EQ(rootsNumber, 1);
    long double eps = fabs(-c / b) / 1e9;
    ASSERT_NEAR(solver_x, -c / b, eps);
  }
}

TEST(zero_a_zero_b_tests, test_constant_equation) {
  for (int c = -1000; c < 1000; ++c) {
    long double unused;
    int rootsNumber = solveQuadraticEquation(0, 0, c, unused, unused);
    if (c == 0) {
      ASSERT_EQ(rootsNumber, INFINITE_ROOTS);
    } else {
      ASSERT_EQ(rootsNumber, 0);
    }
  }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
