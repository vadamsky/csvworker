#include <iostream>
#include "csvworker.h"

using namespace std;

int main()
{
    // Load file "example.csv"
    CsvWorker csv;
    csv.loadFromFile("example.csv");
    // view rows and columns counts from it
    cout << csv.getRowsCount() << "  " << csv.getColumnsCount() << endl;
    // change part of reading data
    csv.getFieldRef(0, 2) = "0";
    csv.getFieldRef(1, 1) = "0";
    csv.getFieldRef(1, 3) = "0";
    csv.getFieldRef(2, 0) = "0";
    csv.getFieldRef(2, 4) = "0";
    csv.getFieldRef(3, 1) = "0";
    csv.getFieldRef(3, 3) = "0";
    csv.getFieldRef(4, 2) = "0";
    // view changed data
    for(unsigned int i = 0; i < csv.getRowsCount(); ++i)
    {
        cout << csv.getRow(i) << endl;
        for(unsigned int j = 0; j < csv.getColumnsCount(); ++j)
        {
            cout << csv.getField(i, j) << ",";
        }
        cout << endl;
    }
    // save changed data in "test.csv"
    csv.saveToFile("test.csv");

    // Create new class instance (4*4)
    CsvWorker csv2(4,4);
    // Fill data of this instance
    csv2.getFieldRef(0, 0) = "a";
    csv2.getFieldRef(0, 1) = "b";
    csv2.getFieldRef(0, 2) = "r";
    csv2.getFieldRef(0, 3) = "a";
    csv2.getFieldRef(1, 0) = "c";
    csv2.getFieldRef(1, 1) = "a";
    csv2.getFieldRef(1, 2) = "d";
    csv2.getFieldRef(2, 0) = "a";
    csv2.getFieldRef(2, 1) = "b";
    csv2.getFieldRef(2, 2) = "r";
    csv2.getFieldRef(2, 3) = "a";
    // save data in "test2.csv"
    csv2.saveToFile("test2.csv");

    return 0;
}

