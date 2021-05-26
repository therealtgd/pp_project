#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix initMatrix(char* inFileName);

void matrixMultiplicationTG(Matrix& c, Matrix& a, Matrix& b);



#endif /* UTILS_H */