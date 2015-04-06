#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

int main()
{
    ifstream readFile("data/unlabeledTrainData.tsv");
    string id, review, line;
    bool firstLine = true;

    if(!readFile.is_open() ){
        cout << "Cannot read the file." << endl ;
    }
    else
    {
        while(getline(readFile,line))
        {
            if(firstLine)
            {
                firstLine = false;
                continue;
            }
            stringstream iss(line);
            getline(iss, id, '\t');
            getline(iss, review, '\n');
            cout << id << endl ;
            cout << review << endl ;
            getch();
        }
        readFile.close();
    }
    return 0;
}
