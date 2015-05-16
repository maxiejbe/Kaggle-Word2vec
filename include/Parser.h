#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Parser
{
    public:
        Parser(const char* filePath, char lineSeparator, char dataSeparator);
        virtual ~Parser();
    protected:
    private:
        std::ifstream readFile;
};

#endif // PARSER_H
