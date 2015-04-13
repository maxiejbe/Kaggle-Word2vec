#include "StringCleaner.h"

using namespace std;
using namespace boost;

StringCleaner::StringCleaner()
{
    //ctor
}

StringCleaner::~StringCleaner()
{
    //dtor
}

void StringCleaner::CleanHTML(string* toClean)
{

}

void StringCleaner::CleanNonLetters(string* toClean)
{
    regex lettersRegex("[^A-Za-z\s]");
    cout << *(toClean) << endl;
    *toClean = regex_replace(*toClean, lettersRegex, string(" "));
}

void StringCleaner::ToLowerCase(string* toClean)
{

}


