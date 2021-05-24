#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix* initMatrix(char* inFileName);

void matrixMultiplicationParallel(Matrix& outM, Matrix* m1, Matrix* m2);

bool check_results(int* matrix1, int* matrix2, int m, int n);


#endif /* UTILS_H */#pragma once
