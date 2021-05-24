#pragma once
#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class Matrix
{
	int rows;
	int cols;
public:
	int* matrix;
	Matrix();
	Matrix(int _rows, int _cols);
	~Matrix();
	void print();
	int numRows();
	int numCols();
};