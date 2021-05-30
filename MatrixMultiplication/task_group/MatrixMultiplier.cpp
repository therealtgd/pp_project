#include "MatrixMultiplier.h"
#include <cassert>
#include <tbb/task_group.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

using namespace tbb;

void validateMatrixDimensions(Matrix a, Matrix b);
void matrixMultiplicationParallel(Matrix& c, Matrix& a, Matrix& b, int cutOff);
void matrixMultiplicationTG(Matrix& c, Matrix& a, Matrix& b) {
	validateMatrixDimensions(a, b);
	matrixMultiplicationParallel(c, a, b, 0);
}

void validateMatrixDimensions(Matrix a, Matrix b)
{
	if (a.getNumCols() != b.getNumRows()) {
		cout << "Error.\nThe number of columns of the 1st matrix must equal to the number of rows of the 2nd.";
		exit(0);
	}
}


bool checkDimensionRequirements(Matrix* a, Matrix* b);
void fillSubmatrix(Matrix, Matrix&, Matrix&, Matrix&, Matrix&);
void stitchSubmatrixes(Matrix& m, Matrix* m11, Matrix* m12, Matrix* m21, Matrix* m22);
void matrixMultiplicationSerial(Matrix& c, Matrix a, Matrix b);
void parallelForTask(Matrix& c, Matrix* a, Matrix* b);

void matrixMultiplicationParallel(Matrix& c, Matrix& a, Matrix& b, int cutOff)
{
	/*int n = a.getNumRows();
	if (n == 1)
		c.addValue(0, 0, (a.getElement(0, 0) * b.getElement(0, 0)));*/
	/*else*/
	//{
	task_group g;
	Matrix t(a.getNumRows(), b.getNumCols());
	if (cutOff == 4 || checkDimensionRequirements(&a, &b))
		matrixMultiplicationSerial(c, a, b);
	else
	{
		cutOff++;
		//spliting matrix a, b, c to matrix dimension n/2*n/2
		Matrix a11(a.getNumRows() / 2, a.getNumCols() / 2);
		Matrix a12(a.getNumRows() / 2, a.getNumCols() - (a.getNumCols() / 2));
		Matrix a21(a.getNumRows() - a.getNumRows() / 2, a.getNumCols() / 2);
		Matrix a22(a.getNumRows() - a.getNumRows() / 2, a.getNumCols() - (a.getNumCols() / 2));

		Matrix b11(b.getNumRows() / 2, b.getNumCols() / 2);
		Matrix b12(b.getNumRows() / 2, b.getNumCols() - (b.getNumCols() / 2));
		Matrix b21(b.getNumRows() - b.getNumRows() / 2, b.getNumCols() / 2);
		Matrix b22(b.getNumRows() - b.getNumRows() / 2, b.getNumCols() - (b.getNumCols() / 2));

		Matrix c11(c.getNumRows() / 2, c.getNumCols() / 2);
		Matrix c12(c.getNumRows() / 2, c.getNumCols() - (c.getNumCols() / 2));
		Matrix c21(c.getNumRows() - c.getNumRows() / 2, c.getNumCols() / 2);
		Matrix c22(c.getNumRows() - c.getNumRows() / 2, c.getNumCols() - (c.getNumCols() / 2));

		Matrix t11(t.getNumRows() / 2, t.getNumCols() / 2);
		Matrix t12(t.getNumRows() / 2, t.getNumCols() - (t.getNumCols() / 2));
		Matrix t21(t.getNumRows() - t.getNumRows() / 2, t.getNumCols() / 2);
		Matrix t22(t.getNumRows() - t.getNumRows() / 2, t.getNumCols() - (t.getNumCols() / 2));

		fillSubmatrix(a, a11, a12, a21, a22);
		fillSubmatrix(b, b11, b12, b21, b22);
		fillSubmatrix(c, c11, c12, c21, c22);
		fillSubmatrix(t, t11, t12, t21, t22);

		g.run([&] { matrixMultiplicationParallel(c11, a11, b11, cutOff); });
		g.run([&] { matrixMultiplicationParallel(c12, a11, b12, cutOff); });
		g.run([&] { matrixMultiplicationParallel(c21, a21, b11, cutOff); });
		g.run([&] { matrixMultiplicationParallel(c22, a21, b12, cutOff); });
		g.run([&] { matrixMultiplicationParallel(t11, a12, b21, cutOff); });
		g.run([&] { matrixMultiplicationParallel(t12, a12, b22, cutOff); });
		g.run([&] { matrixMultiplicationParallel(t21, a22, b21, cutOff); });
		matrixMultiplicationParallel(t22, a22, b22, cutOff);
		g.wait();

		stitchSubmatrixes(c, &c11, &c12, &c21, &c22);
		stitchSubmatrixes(t, &t11, &t12, &t21, &t22);

		Matrix res(c.getNumRows(), t.getNumCols());
		parallelForTask(res, &c, &t);
	}

	 
}

void multiplyFC(Matrix& c, Matrix& a, Matrix& b, int row, int col);
void matrixMultiplicationTGFirstCase(Matrix& c, Matrix& a, Matrix& b)
{
	task_group g;
	// creates tasks that calculate only 1 element of result matrix
	for (int i = 0; i < a.getNumRows(); ++i) {
		for (int j = 0; j < b.getNumCols(); ++j)
			g.run([&, i, j] { multiplyFC(c, a, b, i, j); });
	}
	g.wait();
}

void multiplyFC(Matrix& c, Matrix& a, Matrix& b, int row, int col) {
	float sum = 0;
	// creates tasks that calculate only 1 row of result matrix
	for (int i = 0; i < a.getNumCols(); ++i) {
		sum += a.getElement(row, i) * b.getElement(i, col);
	}
	c.addValue(row, col, sum);
}

void multiplySC(Matrix& c, Matrix& a, Matrix& b, int row);
void matrixMultiplicationTGSecondCase(Matrix& c, Matrix& a, Matrix& b)
{
	task_group g;
	for (int i = 0; i < a.getNumRows(); ++i) {
		g.run([&, i] { multiplySC(c, a, b, i); });
	}
	g.wait();
}

void multiplySC(Matrix& c, Matrix& a, Matrix& b, int row) {
	for (int i = 0; i < a.getNumRows(); ++i) {
		for (int j = 0; j < b.getNumCols(); ++j) {
			float sum = 0;
			for (int k = 0; k < a.getNumCols(); ++k)
				sum += a.getElement(i, k) * b.getElement(k, j);
			c.addValue(i, j, sum);
		}
	}
}


bool checkDimensionRequirements(Matrix* a, Matrix* b)
{
	return a->getNumRows() <= 4 || a->getNumCols() <= 4
		|| b->getNumRows() <= 4 || b->getNumCols() <= 4;
}

void fillSubmatrix(Matrix m, Matrix& m11, Matrix& m12, Matrix& m21, Matrix& m22)
{
	//filling m11 and m12
	for (int i = 0; i < m.getNumRows() / 2; ++i)
	{
		for (int j = 0; j < m.getNumCols() / 2; ++j)
			m11.addValue(i, j, m.getElement(i, j));
		for (int j = 0; j < m.getNumCols() - (m.getNumCols() / 2); ++j)
			m12.addValue(i, j, m.getElement(i, (m.getNumCols() / 2) + j));
	}
	//filling m21 and m22
	for (int i = 0; i < m.getNumRows() - (m.getNumRows() / 2); ++i)
	{
		for (int j = 0; j < m.getNumCols() / 2; ++j)
			m21.addValue(i, j, m.getElement((m.getNumRows() / 2) + i, j));
		for (int j = 0; j < m.getNumCols() - (m.getNumCols() / 2); ++j)
			m22.addValue(i, j, m.getElement((m.getNumRows() / 2) + i, (m.getNumCols() / 2) + j));
		
	}
}

void stitchSubmatrixes(Matrix& m, Matrix* m11, Matrix* m12, Matrix* m21, Matrix* m22)
{
	for (int i = 0; i < m.getNumRows() / 2; ++i)
	{
		for (int j = 0; j < m.getNumCols() / 2; ++j)
			m.addValue(i, j, m11->getElement(i, j));
		for (int j = m.getNumCols() / 2; j < m.getNumCols(); ++j)
			m.addValue(i, j, m12->getElement(i, j - (m.getNumCols() / 2)));
	}
	for (int i = m.getNumRows() / 2; i < m.getNumRows(); ++i)
	{
		for (int j = 0; j < m.getNumCols() / 2; ++j)
			m.addValue(i, j, m21->getElement(i - (m.getNumRows() / 2), j));
		for (int j = m.getNumCols() / 2; j < m.getNumCols(); ++j)
			m.addValue(i, j, m22->getElement(i - (m.getNumRows() / 2), j - (m.getNumCols() / 2)));
	}

}

void matrixMultiplicationSerial(Matrix& c, Matrix a, Matrix b) {
	for (int i = 0; i < a.getNumRows(); ++i) {
		for (int j = 0; j < b.getNumCols(); ++j) {
			float sum = 0;
			for (int k = 0; k < a.getNumCols(); ++k)
				sum += a.getElement(i, k) * b.getElement(k, j);
			c.addValue(i, j, sum);
		}
	}
}

struct MatrixMultiplyBody
{
	Matrix* my_c;
	Matrix* my_a, * my_b;

	void operator( )(const blocked_range2d<size_t>& r) const {
		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i) {
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j) {
				my_c->addValue(i, j, my_c->getElement(i, j) + my_a->getElement(i, j) * my_b->getElement(i, j));
				//int sum = 0;
				/*for (size_t k = 0; k < my_a->getNumCols(); ++k)
					sum += my_a->getElement(i, k) * my_b->getElement(k, j);*/
			}
		}
	}
};


void parallelForTask(Matrix& c, Matrix* a, Matrix* b)
{
	MatrixMultiplyBody body;
	body.my_a = a;
	body.my_b = b;
	body.my_c = &c;

	parallel_for(blocked_range2d<size_t>(0, a->getNumRows(), 16, 0, b->getNumCols(), 32),
		body, auto_partitioner());
}

