#include <iostream>
#include "csvworker.h"


extern "C" {

CsvWorker::CsvWorker(unsigned int rows_n, unsigned int cols_n)
{
    rows = rows_n;
    columns = cols_n;
    row rw(columns);
    for(unsigned int j=0;j<columns;++j)
        rw.push_back("");
    for(unsigned int i=0;i<rows;++i)
        data.push_back(rw);
}

void CsvWorker::loadFromFile(std::string filename)
{
    ifstream in(filename.c_str());
    if( !in )
    {
        cout << "Can't open file \"" << filename << '\"' << endl;
        throw;
    }

    std::string ln;
    std::string str;
    std::string temp;
    int i = 0;
    while( !in.eof() )
    {
        std::getline( in, ln );
        if(ln[ln.size()-1]==10 || ln[ln.size()-1]==13)
            ln = ln.substr(0, ln.size()-1);
        str = ln;
        row rw;
        int p = 0;
        while( 1 )
        {
            p = str.find(',');
            if(p<=0) break;
            temp = str.substr( 0, p );
            str = str.substr( p+1, str.size()-1-p );
            rw.push_back(temp);
        }
        rw.push_back(str);
        if(i==0)
        columns=rw.size();
        else if(columns!=rw.size())
        {
            cout << "Wrong data format: \"" << ln << '\"' << endl;
            in.close();
            throw;
        }
        data.push_back(rw);
        i++;
    }
    rows = data.size();
    in.close();
}

void CsvWorker::saveToFile(std::string filename)
{
    if(columns==0)
    {
        cout << "Wrong csv format: columns=0" << endl;
        throw;
    }
    if(rows==0)
    {
        cout << "Wrong csv format: rows=0" << endl;
        throw;
    }

    ofstream out(filename.c_str());
    if( !out )
    {
        cout << "Can't create or open file \"" << filename << '\"' << endl;
        throw;
    }

    for(unsigned int i=0;i<rows;++i)
    {
        row & rw = data[i];
        unsigned int c1 = columns-1;
        for(unsigned int j=0;j<columns;++j)
        {
            out << rw[j];
            j<c1 ? out << "," : out << endl;
        }
    }
    out.close();
}

row &CsvWorker::getRow(unsigned int row_n)
{
    if(row_n>=rows)
    {
        cout << "Wrong row index: " << row_n << ", but max index is: " << rows-1 << endl;
        throw;
    }
    return data[row_n];
}

std::string & CsvWorker::getFieldRef(unsigned int row_n, unsigned int col_n)
{
    row &rw = getRow(row_n);
    if(col_n>=columns)
    {
        cout << "Wrong column index: " << col_n << ", but max index is: " << columns-1 << endl;
        throw;
    }
    return rw[col_n];
}

std::string CsvWorker::getField(unsigned int row_n, unsigned int col_n)
{
    return getFieldRef(row_n, col_n);
}

}

