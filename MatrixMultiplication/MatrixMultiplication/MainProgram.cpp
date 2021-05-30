#include "MainProgram.h"
#include "MatrixMultiplier.h"
#include "MatrixLoader.h"
#include "tbb/tick_count.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace tbb;

// prints programs title
void printTitle()
{
    cout << "**********Matrix Multiplication parallel**********";
    cout << endl;
    cout << endl;
}


// prints program usage info
void printUsage()
{
    cout << endl;
    cout << "Execute program like: \"parallel.exe <matrix_file1> <matrix_file2> <output_file_name>\"." << endl;
    cout << endl;
    cout << endl;
}


int decideReps(int size)
{
    int repeat = 1;
    if (size < 200)
        repeat = 5;
    else if (size < 650)
        repeat = 4;
    else if (size < 1000)
        repeat = 3;
    else if (size < 1500)
        repeat = 2;
    return repeat;
}

// argv[1] - in file 1 name (matrix 1)
// argv[2] - in file 2 name (matrix 2)
// argv[3] - out file name
int mainParallel(int argc, char* argv[])
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
    Matrix* m1 = loadMatrix(inFileName1);
    Matrix* m2 = loadMatrix(inFileName2);

    int reps = decideReps(m1->getNumRows());
    for (int i = 0; i < reps; i++)
    {
        Matrix resMatrix(m1->getNumRows(), m2->getNumCols());

        // run program
        tick_count startTime = tick_count::now();
        resMatrix = parallelMatrixMultiply(resMatrix, m1, m2);
        tick_count endTime = tick_count::now();

        /*m1->print();
        m2->print();
        resMatrix.print();*/
        cout << endl << "Execution time: " << (endTime - startTime).seconds() * 1000 << "ms." << endl;

        // save exec time to output file
        ofstream outdata;
        outdata.open(outFileName, std::ios_base::app);
        outdata << "parallel " << m1->getNumCols() << " " << m2->getNumRows() << " " << (endTime - startTime).seconds() * 1000 << endl;
        outdata.close();
    }

    // free memory
    delete m1;
    delete m2;

    return 0;
}
