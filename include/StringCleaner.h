#ifndef STRINGCLEANER_H
#define STRINGCLEANER_H
#include <string>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

class StringCleaner
{
    public:
        StringCleaner();
        static void CleanHTML(std::string* toClean);
        static void CollapseWhiteSpaces(std::string* toClean);
        static void CleanNonLetters(std::string* toClean);
        static void ToLowerCase(std::string* toClean);
        virtual ~StringCleaner();
    protected:
    private:
};

#endif // STRINGCLEANER_H
