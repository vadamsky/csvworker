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
    CsvWorker(unsigned int rows_n=0, unsigned int cols_n=0);

    void loadFromFile(std::string filename);
    void saveToFile(std::string filename);

    unsigned int getRowsNumber() { return rows; }
    unsigned int getColumnsNumber() { return columns; }
    std::string getField(unsigned int row_n, unsigned int col_n);
    std::string & getFieldRef(unsigned int row_n, unsigned int col_n);
private:
    row & getRow(unsigned int row_n);

private:
    unsigned int rows;
    unsigned int columns;
    std::vector<row> data;
};

#endif // CSVWORKER_H
