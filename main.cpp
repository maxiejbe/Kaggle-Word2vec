#include <fstream>
#include <sstream>
#include "include/StringCleaner.h"

using namespace std;

int main()
{
    ifstream readFile("data/labeledTrainData.tsv");
    string id, review, sentiment, line;
    bool firstLine = true;

    if(!readFile.is_open() ){
        cout << "Cannot read the file." << endl ;
    }
    else
    {
        getline(readFile,line, '\n');
        while(getline(readFile,line))
        {
            if(firstLine)
            {
                firstLine = false;
                continue;
            }
            stringstream iss(line);
            getline(iss, id, '\t');
            getline(iss, sentiment, '\t');
            getline(iss, review, '\n');
            StringCleaner::CleanHTML(&review);
            StringCleaner::CleanNonLetters(&review);
            StringCleaner::CollapseWhiteSpaces(&review);
            StringCleaner::ToLowerCase(&review);
            cout << id << endl ;
            cout << sentiment << endl ;
            cout << review << endl ;
            getchar();
        }
        readFile.close();
    }
    return 0;
}
