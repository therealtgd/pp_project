#include "MainProgram.h"
#include <iostream>
#include <stdio.h>
#include "utils.h"
#include "tbb/tick_count.h"

using namespace std;
using namespace tbb;

// prints programs title
void printTitle()
{
    cout << "**********Matrix Multiplication serial**********";
    cout << endl;
    cout << endl;
}


// prints program usage info
void printUsage()
{
    cout << endl;
    cout << "Execute program like: \"serial.exe <matrix_file1> <matrix_file2> <output_file_name>\"." << endl;
    cout << endl;
    cout << endl;
}


// argv[1] - in file 1 name (matrix 1)
// argv[2] - in file 2 name (matrix 2)
// argv[3] - out file name
int mainSerial(int argc, char* argv[])
{
    char* inFileName1;
    char* inFileName2;
    char* outFileName;

    printTitle();

    if (argc != 4)
    {
        cout << "Error. Wrong number of arguments passed." << endl;
        printUsage();
        return -1;
    }

    inFileName1 = argv[1];
    inFileName2 = argv[2];
    outFileName = argv[3];
    
    // init matrix
    Matrix* m1 = initMatrix(inFileName1);
    Matrix* m2 = initMatrix(inFileName2);
    Matrix resMatrix(m1->getNumRows(), m2->getNumCols());
    
    // run program
    tick_count startTime = tick_count::now();
    matrixMultiplicationSerial(resMatrix, m1, m2);
    tick_count endTime = tick_count::now();

    m1->print();
    m2->print();
    resMatrix.print();
    cout << endl << "Execution time: " << (endTime - startTime).seconds() * 1000 << "ms." << endl;

    // free memory
    delete m1;
    delete m2;
    
    return 0;
}
