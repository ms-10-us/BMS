#include "DataParse.h"

DataParse::DataParse(const std::string &fileName, bool hasHeader)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could Not Open File: " + fileName);
    }

    std::string line;
    std::vector<std::vector<double>> tempColumns;

    if (hasHeader && std::getline(file, line))
    {
        std::stringstream stringStream(line);
        std::string cell;

        while (std::getline(stringStream, cell, ','))
        {
            cell.erase(0, cell.find_first_not_of(" \t\""));
            cell.erase(cell.find_last_not_of(" \t\"") + 1);
            ColumnNames.push_back(cell);
        }
        ColNumber = ColumnNames.size();
    }

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream stringStream(line);
        std::string cell;
        size_t colIndex = 0;

        while (std::getline(stringStream, cell, ','))
        {
            if (tempColumns.size() <= colIndex)
            {
                tempColumns.resize(colIndex + 1);
            }

            try
            {
                double value = std::stod(cell);
                tempColumns[colIndex].push_back(value);
            }
            catch (std::invalid_argument)
            {
                tempColumns[colIndex].push_back(std::numeric_limits<double>::quiet_NaN());
            }
            colIndex++;
        }
    }

    Columns = std::move(tempColumns);
    if (Columns.empty())
    {
        RowNumber = 0;
    }
    else
    {
        RowNumber = Columns[0].size();
    }

    for (auto &col : Columns)
    {
        if (col.size() < RowNumber)
        {
            col.resize(RowNumber, std::numeric_limits<double>::quiet_NaN());
        }
    }

    if (ColumnNames.empty() && ColNumber > 0)
    {
        for (size_t i = 0; i < ColNumber; i++)
        {
            ColumnNames.push_back("Colmun_" + std::to_string(i));
        }
    }

    std::cout << "Successfully loaded " << RowNumber << " Rows\n"
              << "Successfully loaded " << ColNumber << " Columns\n"
              << "From file " + fileName << "\n";
}

const std::vector<double> &DataParse::getColumn(size_t colIndex) const
{
    if (colIndex >= Columns.size())
    {
        throw std::out_of_range("Column Index Out of Range");
    }
    return Columns[colIndex];
}

const std::vector<double> &DataParse::getColumn(const std::string &colName) const
{
    for (size_t i = 0; i < ColumnNames.size(); i++)
    {
        if (colName == ColumnNames[i])
        {
            return Columns[i];
        }
    }
    throw std::invalid_argument("Column Name Was Not Found: " + colName);
}

size_t DataParse::getRowNumber() const
{
    return RowNumber;
}

size_t DataParse::getColNumber() const
{
    return ColNumber;
}

const std::vector<std::string> &DataParse::getColumnNames() const
{
    return ColumnNames;
}

void DataParse::printSummary() const
{
    std::cout << "DataParse Summary:\n"
              << "  Rows: " << RowNumber << "\n"
              << "  Columns: " << ColNumber << "\n"
              << "  Column Names: ";
    for (const auto &name : ColumnNames)
    {
        std::cout << name << "  ";
    }
    std::cout << std::endl;
}