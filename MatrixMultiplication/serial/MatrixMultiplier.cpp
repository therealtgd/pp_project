#include "MatrixMultiplier.h"
#include <cassert>

void validateMatrixDimensions(Matrix a, Matrix b);
void matrixMultiplicationSerial(Matrix& c, Matrix* a, Matrix* b) {
	validateMatrixDimensions((*a), (*b));
	for (int i = 0; i < a->getNumRows(); ++i) {
		for (int j = 0; j < b->getNumCols(); ++j) {
			float sum = 0;
			for (int k = 0; k < a->getNumCols(); ++k)
				sum += a->getElement(i, k) * b->getElement(k, j);
			c.addValue(i, j, sum);
		}
	}
}

void validateMatrixDimensions(Matrix a, Matrix b)
{
	if (a.getNumCols() != b.getNumRows()) {
		cout << "Error.\nThe number of columns of the 1st matrix must equal to the number of rows of the 2nd.";
		exit(0);
	}
}
