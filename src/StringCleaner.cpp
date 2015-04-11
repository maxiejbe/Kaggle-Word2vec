#include "StringCleaner.h"

using namespace std;

StringCleaner::StringCleaner()
{
    //ctor
}

StringCleaner::~StringCleaner()
{
    //dtor
}

void StringCleaner::CleanHTML(std::string* toClean)
{

}

void StringCleaner::CleanNonLetters(std::string* toClean)
{
    try
    {
        std::regex lettersRegex("[^A-Za-z\s]");
        std::cout << *(toClean) << std::endl;
        *toClean = std::regex_replace(*toClean, lettersRegex, std::string(""));
    }
    catch (std::regex_error& e) {
        // Syntax error in the regular expression
        std::cout << e.code() << std::endl;
    }
}

void StringCleaner::ToLowerCase(std::string* toClean)
{

}


