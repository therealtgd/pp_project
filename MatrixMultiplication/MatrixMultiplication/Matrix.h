#pragma once

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix
{
	vector<vector<int>> matrix;
	int rows, cols;
public:
	Matrix();
	Matrix(int _rows, int _cols);
	vector<vector<int>> getMatrix();
	void addValue(const int row, const int col, const int val);
	int getElement(const int row, const int col);
	int getNumRows();
	int getNumCols();
	void print();
};