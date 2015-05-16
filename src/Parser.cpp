#include "Parser.h"
using namespace std;

Parser::Parser(const char* filePath, char lineSeparator, char dataSeparator)
{
    readFile(filePath);
    if(!readFile.is_open() ){
        throw invalid_argument("Cannot read the file path");
    }
}

Parser::~Parser()
{
    readFile.close();
}
