#include "utils.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
ifstream openInFile(char* fileName);
Matrix* initMatrix(char* inFileName) {
	ifstream inFile = openInFile(inFileName);

	int rows, cols;
	inFile >> rows >> cols;
	Matrix* m = new Matrix(rows, cols);
	string line;
	int i = 0;
	while (getline(inFile, line))
	{
		stringstream ss;
		ss << line;
		int val;
		while (ss >> val)
		{
			m->matrix[i] = val;
			i++;
		}
	}
	return m;
}

ifstream openInFile(char* fileName) {
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
		cout << "File \"" << fileName << "\" couldn't be opened." << endl;
	else
		return file;
}


void matrixMultiplicationSerial(Matrix& outM, Matrix* m1, Matrix* m2) {
	int row1 = m1->numRows();
	int col1 = m1->numCols();
	int col2 = m2->numCols();
	int row2 = m2->numRows();
	assert(col1 == row2);

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			int value = 0;
			for (int k = 0; k < col1; k++) {
				value += m1->matrix[i * col1+ k] * m2->matrix[k * col2+ j];
			}
			outM.matrix[i * col2 + j] = value;
		}
	}
}
