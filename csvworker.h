#ifndef CSVWORKER_H
#define CSVWORKER_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef std::vector<std::string> row;

class CsvWorker
{
public:
    // If counts of rows and columns !=0, this fills vector of rows "data";
    // each of rows has cols_count empty strings
    CsvWorker(unsigned int rows_n=0, unsigned int cols_n=0);

    // This loads .csv file and fills vector of rows "data";
    // counts of rows and columns determines from file data.
    // The delimiter is always ",".
    void loadFromFile(std::string filename);
    
    // This saves in .csv file vector of rows "this->data".
    // This vector must be already filled.
    // The delimiter is always ",".
    void saveToFile(std::string filename);

    // This gets count of rows.
    unsigned int getRowsCount() { return rows_count; }
    // This gets count of columns.
    unsigned int getColumnsCount() { return cols_count; }
    
    // This gets row's field ( typedef std::vector<std::string> row; )
    // with row index row_n and field(column) index col_n.
    std::string getField(unsigned int row_n, unsigned int col_n);
    // This gets reference to row's field ( typedef std::vector<std::string> row; )
    // with row index row_n and field(column) index col_n.
    std::string & getFieldRef(unsigned int row_n, unsigned int col_n);
private:
    // This gets reference to row ( typedef std::vector<std::string> row; )
    // in data ( std::vector<row> data; ) with row index row_n.
    row & getRowRef(unsigned int row_n);

private:
    unsigned int rows_count;
    unsigned int cols_count;
    std::vector<row> data;
};

#endif // CSVWORKER_H
