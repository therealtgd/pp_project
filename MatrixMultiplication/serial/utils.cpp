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
		if (line != "") {
			stringstream ss;
			ss << line;
			int val;
			int j = 0;
			while (ss >> val)
			{
				m->addValue(i, j, val);
				j++;
			}
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


void matrixMultiplicationSerial(Matrix& c, Matrix* a, Matrix* b) {
	for (int i = 0; i < a->getNumRows(); ++i) {
		for (int j = 0; j < b->getNumCols(); ++j) {
			float sum = 0;
			for (int k = 0; k < a->getNumCols(); ++k)
				sum += a->getElement(i, k) * b->getElement(k, j);
			c.addValue(i, j, sum);
		}
	}
}
