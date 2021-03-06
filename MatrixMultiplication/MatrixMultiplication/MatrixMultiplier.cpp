#include "MatrixMultiplier.h"
#include <cassert>
#include<tbb/blocked_range2d.h>
#include<tbb/parallel_for.h>

using namespace tbb;

struct MatrixMultiplyBody
{
	Matrix* my_c;
	Matrix *my_a, *my_b;

	void operator( )(const blocked_range2d<size_t>& r) const {
		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i) {
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j) {
				int sum = 0;
				for (size_t k = 0; k < my_a->getNumCols(); ++k)
					sum += my_a->getElement(i, k) * my_b->getElement(k, j);
				my_c->addValue(i, j, sum);
			}
		}
	}
};

void validateMatrixDimensions(Matrix a, Matrix b);
Matrix parallelMatrixMultiply(Matrix c, Matrix* a, Matrix* b)
{
	validateMatrixDimensions((*a), (*b));

	MatrixMultiplyBody body;
	body.my_a = a;
	body.my_b = b;
	body.my_c = &c;
	//parallel_for(blocked_range2d<size_t>(0, a->getNumRows(), 0, b->getNumCols()), body, auto_partitioner());
	parallel_for(blocked_range2d<size_t>(0, a->getNumRows(), 16, 0, b->getNumCols(), 32),
		body, auto_partitioner());
	return c;
}

void validateMatrixDimensions(Matrix a, Matrix b)
{
	if (a.getNumCols() != b.getNumRows()) {
		cout << "Error.\nThe number of columns of the 1st matrix must equal to the number of rows of the 2nd.";
		exit(0);
	}
}
