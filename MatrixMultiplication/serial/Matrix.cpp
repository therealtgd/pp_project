#pragma once

#include "Matrix.h"
#include <sstream>

Matrix::Matrix() : rows(0), cols(0)
{
}

Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
{
	for (int i = 0; i < rows; i++) {
		vector<int> v;
		for (int j = 0; j < cols; j++) {
			v.push_back(0);
		}
		matrix.push_back(v);
	}
}

vector<vector<int>> Matrix::getMatrix()
{
	return matrix;
}

void Matrix::addValue(const int row, const int col, const int val)
{
	matrix[row][col] = val;
}

int Matrix::getElement(const int row, const int col) {
	return matrix[row][col];
}

int Matrix::getNumRows()
{
	return rows;
}

int Matrix::getNumCols()
{
	return cols;
}

void Matrix::print()
{
	for (auto& row : matrix) {
		for (auto& col : row)
			cout << col << " ";
		cout << endl;
	}
	cout << endl;
}