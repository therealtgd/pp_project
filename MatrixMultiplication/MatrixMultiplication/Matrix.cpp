#pragma once

#include "Matrix.h"
#include <sstream>

Matrix::Matrix() : rows(0), cols(0)
{
	matrix = (int*)malloc(sizeof(int) * (rows * cols));
}

Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
{
	matrix = (int*)malloc(sizeof(int) * (rows * cols));
}

Matrix::~Matrix()
{
	free(this->matrix);
}

void Matrix::print()
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++)
			cout << matrix[i * this->cols + j] << "\t";
		cout << endl;
	}
	cout << endl;
}

int Matrix::numRows()
{
	return this->rows;
}

int Matrix::numCols()
{
	return this->cols;
}
