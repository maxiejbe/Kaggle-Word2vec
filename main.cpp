#include "include/UnlabeledReview.h"
#include "include/LabeledReview.h"
#include "include/Perceptron.h"
#include <boost/algorithm/string.hpp>
#include "boost/tuple/tuple.hpp"
#include <list>

using namespace std;
using namespace boost;

vector<string> ReadStopWords(){
    vector<string> stopWords;

    ifstream labeledReadFile("data/stopwords.txt");
    if(!labeledReadFile.is_open() ){
        cout << "Cannot read the stop words data file." << endl ;
    }
    else
    {
        std::string line;
        while (std::getline(labeledReadFile, line))
        {
            std::istringstream iss(line);
            string word;
            if (!(iss >> word)) { break; }
            stopWords.push_back(word);
        }
        labeledReadFile.close();
    }
    return stopWords;
}

list<tuple<vector<string>, string> > ReadLabeledFile(){
    list<tuple<vector<string>, string> > labeledReviews;
    LabeledReview labeledReview;

    vector<string> stopWords = ReadStopWords();

    ifstream labeledReadFile("data/labeledTrainDataTest.tsv");
    if(!labeledReadFile.is_open() ){
        cout << "Cannot read the labeled train data file." << endl ;
    }
    else
    {
        while(labeledReview.FromFileLine(&labeledReadFile))
        {
            //let me explain myself, I need to get a vector of words + sentiment as a tuple
            vector<string> reviewVector;
            string reviewString = labeledReview.GetReview();
            boost::split(reviewVector,reviewString,boost::is_any_of(" "));

            //TODO: Diff between reviewVector and stopWords and generate the tuple

            tuple<vector<string>, string> labeledReviewTuple = make_tuple(reviewVector, labeledReview.GetSentiment());

            labeledReviews.push_back(labeledReviewTuple);
        }
        labeledReadFile.close();
    }
    return labeledReviews;
}

int main()
{
    list<tuple<vector<string>, string> > labeledReviews = ReadLabeledFile();

    for (list<tuple<vector<string>, string> >::iterator reviewedIterator=labeledReviews.begin(); reviewedIterator!=labeledReviews.end(); ++reviewedIterator){

        for (vector<string>::iterator it = get<0>(*reviewedIterator).begin(); it != get<0>(*reviewedIterator).end(); ++it)
        {
            cout << *it << endl;
        }
        cout << get<1>(*reviewedIterator) << endl ;
        getchar();
    }

    return 0;
}

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
