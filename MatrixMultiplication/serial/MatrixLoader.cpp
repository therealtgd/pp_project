#include "MatrixLoader.h"
#include <fstream>
#include <string>
#include <sstream>

ifstream openInFile(char* fileName);
Matrix* loadMatrix(char* inFileName) {
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