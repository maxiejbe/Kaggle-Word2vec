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
    regex htmlRegex("<[^>]*>");
    *toClean = regex_replace(*toClean, htmlRegex, string(" "));
}

void StringCleaner::CollapseWhiteSpaces(string* toClean)
{
    regex collapseSpacesRegex("\\s+");
    *toClean = regex_replace(*toClean, collapseSpacesRegex, string(" "));
}

void StringCleaner::CleanNonLetters(string* toClean)
{
    regex lettersRegex("[^a-zA-Z0-9]");
    *toClean = regex_replace(*toClean, lettersRegex, string(" "));
}

void StringCleaner::ToLowerCase(string* toClean)
{
    cout << *toClean << endl;
    algorithm::to_lower(*toClean);
}


