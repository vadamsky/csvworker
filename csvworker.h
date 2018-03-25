#ifndef CSVWORKER_H
#define CSVWORKER_H

#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

typedef std::vector<std::string> row;

class CsvWorker
{
public:
    // If counts of rows and columns !=0, this fills vector of rows "data";
    // each of rows has cols_count empty strings
    CsvWorker(char delim=',', unsigned int rows_n=0, unsigned int cols_n=0);

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
	// This gets row ( typedef std::vector<std::string> row; )
	// in data ( std::vector<row> data; ) with row index row_n.
	row getRow(unsigned int row_n) { return getRowRef(row_n); }
private:
    // This gets reference to row ( typedef std::vector<std::string> row; )
    // in data ( std::vector<row> data; ) with row index row_n.
    row & getRowRef(unsigned int row_n);
	// This loads data from file to readed_data
	void loadFile(std::string filename, std::deque<std::string> &readed_data);
	// This parse readed_data to data
	void parseData(std::deque<std::string> &readed_data);

private:
	unsigned int rows_count{0};
	unsigned int cols_count{0};
    std::deque<row> data;
	char delimiter{','};

	static const int max_field_size{ 1024 };
	static const int BLOCK_SIZE{ 2048 };

	char unparsed_buffer[BLOCK_SIZE];
	int unparsed_buffer_size{ 0 };
};

#endif // CSVWORKER_H