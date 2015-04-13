#ifndef STRINGCLEANER_H
#define STRINGCLEANER_H
#include <string>
#include <iostream>
#include <boost/regex.hpp>

class StringCleaner
{
    public:
        StringCleaner();
        void CleanHTML(std::string* toClean);
        static void CleanNonLetters(std::string* toClean);
        void ToLowerCase(std::string* toClean);
        virtual ~StringCleaner();
    protected:
    private:
};

#endif // STRINGCLEANER_H
