#include "include/UnlabeledReview.h"
#include "include/LabeledReview.h"

using namespace std;

void ReadUnlabeledFile(){
    ifstream unlabeledReadFile("data/unlabeledTrainData.tsv");
    if(!unlabeledReadFile.is_open() ){
        cout << "Cannot read the unlabeled train data file." << endl ;
    }
    else
    {
        UnlabeledReview* unlabeledReview = new UnlabeledReview();
        while(unlabeledReview->FromFileLine(&unlabeledReadFile))
        {
            cout << unlabeledReview->GetId() << endl ;
            cout << unlabeledReview->GetReview() << endl ;
            getchar();
        }
        unlabeledReadFile.close();
    }
}

void ReadLabeledFile(){
    ifstream labeledReadFile("data/labeledTrainData.tsv");
    if(!labeledReadFile.is_open() ){
        cout << "Cannot read the labeled train data file." << endl ;
    }
    else
    {
        LabeledReview* labeledReview = new LabeledReview();
        while(labeledReview->FromFileLine(&labeledReadFile))
        {
            cout << labeledReview->GetId() << endl ;
            cout << labeledReview->GetSentiment() << endl ;
            cout << labeledReview->GetReview() << endl ;
            getchar();
        }
        labeledReadFile.close();
    }
}

int main()
{
    ReadLabeledFile();
    ReadUnlabeledFile();
    return 0;
}
