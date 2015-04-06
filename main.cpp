#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
            cout << id << endl ;
            cout << sentiment << endl ;
            cout << review << endl ;
            getchar();
        }
        readFile.close();
    }
    return 0;
}
