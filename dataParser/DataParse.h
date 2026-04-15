#ifndef DATAPARSE_H
#define DATAPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <numeric>

class DataParse
{
private:
    std::vector<std::vector<double>> Columns;

    std::vector<std::string> ColumnNames;

    size_t RowNumber = 0;

    size_t ColNumber = 0;

public:
    DataParse(const std::string &fileName, bool hasHeader = true);

    const std::vector<double> &getColumn(size_t colIndex) const;

    const std::vector<double> &getColumn(const std::string &colName) const;

    size_t getRowNumber() const;

    size_t getColNumber() const;

    const std::vector<std::string> &getColumnNames() const;

    void printSummary() const;
};

#endif