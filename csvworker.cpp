#include <iostream>
#include "csvworker.h"

// If counts of rows and columns !=0, this fills vector of rows "data";
// each of rows has cols_count empty strings
CsvWorker::CsvWorker(unsigned int rows_count, unsigned int cols_count)
{
    this->rows_count = rows_count;
    this->cols_count = cols_count;
    row rw(cols_count);
    for(unsigned int j=0;j<cols_count;++j)
        rw.push_back("");
    for(unsigned int i=0;i<rows_count;++i)
        data.push_back(rw);
}

// This loads .csv file and fills vector of rows "data";
// counts of rows and columns determines from file data.
// The delimiter is always ",".
void CsvWorker::loadFromFile(std::string filename)
{
    // Try to open file
    ifstream in(filename.c_str());
    if( !in )
    {
        cout << "Can't open file \"" << filename << '\"' << endl;
        throw;
    }
    // temporary strings
    std::string ln; // in this string reads lines from file
    std::string str; // this string uses for parsing line string
    std::string temp; // this too
    int i = 0; // number of row (from 0)
    // reading and parsing file
    while( !in.eof() )
    {
        std::getline( in, ln ); // read line from file in string "ln"
		if (ln.size() == 0) break; // if string is empty, believe that the file is complete
		if(ln[ln.size()-1]==10 || ln[ln.size()-1]==13) // erasing endline symbols
            ln = ln.substr(0, ln.size()-1);
        str = ln;
        row rw; // create new row ( typedef std::vector<std::string> row; )
        int p = 0; // position of "," symbol in string
        while( 1 ) // parsing line
        {
            p = str.find(',');
            if(p <= 0) break;
            temp = str.substr( 0, p );
            str = str.substr( p+1, str.size()-1-p );
            rw.push_back(temp);
        }
        rw.push_back(str); // adding last row part in row
        if(i == 0) // determine columns count from first row
            this->cols_count = rw.size();
        else if(this->cols_count != rw.size()) // if columns count of other row not equals
        {                                      // columns count from first row, generate error
            cout << "Wrong data format: \"" << ln << '\"' << endl;
            in.close();
            throw;
        }
        data.push_back(rw); // adding row part in data ( std::vector<row> data; )
        i++;
    }
    this->rows_count = data.size(); // determine rows count
    in.close(); // close file
}

// This saves in .csv file vector of rows "this->data".
// This vector must be already filled.
// The delimiter is always ",".
void CsvWorker::saveToFile(std::string filename)
{
    if(this->cols_count == 0) // if count of columns equals 0, generate error
    {
        cout << "Wrong csv format: columns=0" << endl;
        throw;
    }
    if(this->rows_count == 0) // if count of rows equals 0, generate error
    {
        cout << "Wrong csv format: rows=0" << endl;
        throw;
    }
    // Try to open file
    ofstream out(filename.c_str());
    if( !out )
    {
        cout << "Can't create or open file \"" << filename << '\"' << endl;
        throw;
    }
    // write "data" in file
    for(unsigned int i = 0; i < this->rows_count; ++i)
    {
        row & rw = data[i]; // create reference to part of data 
        unsigned int delimiters_count = this->cols_count - 1; // count of delimiters
        // write row in file
        for(unsigned int j = 0; j < this->cols_count; ++j)
        {
            out << rw[j];
            if(j < delimiters_count)
                out << ",";
        }
        // if row is not last, write endline
        if(i < this->rows_count - 1)
            out << endl;
    }
    out.close(); // close file
}

// This gets reference to row ( typedef std::vector<std::string> row; )
// in data ( std::vector<row> data; ) with row index row_n.
row &CsvWorker::getRowRef(unsigned int row_n)
{
    if(row_n >= this->rows_count) // if row index is wrong, generate error
    {
        cout << "Wrong row index: " << row_n << ", but max index is: " << this->rows_count - 1 << endl;
        throw;
    }
    return data[row_n];
}

// This gets reference to row's field ( typedef std::vector<std::string> row; )
// with row index row_n and field(column) index col_n.
std::string & CsvWorker::getFieldRef(unsigned int row_n, unsigned int col_n)
{
    row &rw = getRowRef(row_n);
    if(col_n >= this->cols_count) // if field index is wrong, generate error
    {
        cout << "Wrong field index: " << col_n << ", but max index is: " << this->cols_count - 1 << endl;
        throw;
    }
    return rw[col_n];
}

// This gets row's field ( typedef std::vector<std::string> row; )
// with row index row_n and field(column) index col_n.
std::string CsvWorker::getField(unsigned int row_n, unsigned int col_n)
{
    return getFieldRef(row_n, col_n);
}