#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "KmkString.h"

using Kmk::String;
using std::vector;

std::ostream &PrintLikeTable(std::ostream &out, const String &cell1, const String &cell2);
vector<String> GetWordsFromFile(char *pathToFile);
vector<String> GetWordsFromArgv(int argc, char *argv[]);
bool StringCompareWithoutCase(const String &lhs, const String &rhs);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        PrintLikeTable(std::cout, "-h, --help", "Show help.");
        return 0;
    }

    if (argc == 2 && (String(argv[1]) == String("-h") || String(argv[1]) == String("--help")))
    {
        PrintLikeTable(std::cout, "-f <pathToFile>", "Read words from file.");
        PrintLikeTable(std::cout, "<string1> <string2> ...", "Read words from argv");
        return 0;
    }

    vector<String> words =
        argv[1] == String("-f") ? GetWordsFromFile(argv[2]) : GetWordsFromArgv(argc, argv);

    std::sort(words.begin(), words.end(), StringCompareWithoutCase);

    for (auto current = words.rbegin(); current != words.rend(); ++current)
    {
        std::cout << *current << std::endl;
    }

    return 0;
}

std::ostream &PrintLikeTable(std::ostream &out, const String &cell1, const String &cell2)
{
    out
        << std::left
        << std::setw(32)
        << cell1
        << std::left
        << std::setw(64)
        << cell2
        << std::endl;

    return out;
}

vector<String> GetWordsFromFile(char *pathToFile)
{
    vector<String> result;
    String tmp;

    std::ifstream in(pathToFile);
    if (in.is_open())
    {
        while (in >> tmp)
        {
            result.push_back(std::move(tmp));
        }
    }

    return result;
}

vector<String> GetWordsFromArgv(int argc, char *argv[])
{
    vector<String> result;

    for (int i = 1; i < argc; ++i)
    {
        result.push_back(std::move(String(argv[i])));
    }

    return result;
}

bool StringCompareWithoutCase(const String &lhs, const String &rhs)
{
    for (auto lhsPtr = lhs.Begin(), rhsPtr = rhs.Begin();
         (lhsPtr != lhs.End()) && (rhsPtr != rhs.End()); ++lhsPtr, ++rhsPtr)
    {
        if (*lhsPtr != *rhsPtr)
        {
            return *lhsPtr < *rhsPtr;
        }
    }

    return lhs.GetSize() < rhs.GetSize();
}