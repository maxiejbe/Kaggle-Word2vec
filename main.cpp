#include <cstdlib>
#include "include/UnlabeledReview.h"
#include "include/LabeledReview.h"
#include "include/Perceptron.h"
#include "include/HashingTrick.h"
#include <boost/algorithm/string.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/lexical_cast.hpp"
#include <list>
#include <map>

using namespace std;
using namespace boost;

map<string, int> ReadStopWords(){
    map<string, int> stopWords;

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
            stopWords[word] = 1;
        }
        labeledReadFile.close();
    }
    return stopWords;
}

vector<tuple<map<unsigned long,int>,int> > ReadLabeledFile(long dimensions){
    vector<tuple<map<unsigned long,int>,int> > labeledReviews;
    LabeledReview labeledReview;

    map<string, int> stopWords = ReadStopWords();

    ifstream labeledReadFile("data/labeledTrainDataTest.tsv");
    if(!labeledReadFile.is_open() ){
        cout << "Cannot read the labeled train data file." << endl ;
    }
    else
    {
        HashingTrick* hashingTrick = new HashingTrick(dimensions);

        bool firstElement = true;
        while(labeledReview.FromFileLine(&labeledReadFile))
        {
            if(firstElement){
                firstElement = false;
                continue;
            }
            //let me explain myself, I need to get a vector of words + sentiment as a tuple
            vector<string> reviewVector;
            string reviewString = labeledReview.GetReview();
            boost::split(reviewVector,reviewString,boost::is_any_of(" "));

            //Diff between reviewVector and stopWords and generate the tuple
            vector<string> cleanedVector;
            for (vector<string>::iterator it = reviewVector.begin(); it != reviewVector.end(); ++it){
                if(stopWords[(*it)] == 1) continue;
                cleanedVector.push_back(*it);
            }
            map<unsigned long, int> hashedReview = hashingTrick->Hash(cleanedVector);
            tuple<map<unsigned long, int>, int> labeledReviewTuple = make_tuple(hashedReview, lexical_cast<int>(labeledReview.GetSentiment()));
            labeledReviews.push_back(labeledReviewTuple);
        }

        delete hashingTrick;
        labeledReadFile.close();
    }


    return labeledReviews;
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


int main()
{
    long dimensions = 20000;

    vector<tuple<map<unsigned long,int>,int> > labeledReviews = ReadLabeledFile(dimensions);

    vector<double> percentronWeights = Perceptron::trainPerceptron(labeledReviews, dimensions);

    for (vector<double>::iterator it=percentronWeights.begin(); it!=percentronWeights.end(); ++it){
        cout << *it << endl;
        //getchar();
    }

    vector<tuple<map<unsigned long,int>, int> >::iterator reviewedIterator;
    for (reviewedIterator=labeledReviews.begin(); reviewedIterator!=labeledReviews.end(); ++reviewedIterator){

        for (map<unsigned long,int>::iterator it = get<0>(*reviewedIterator).begin(); it != get<0>(*reviewedIterator).end(); ++it)
        {
            cout << it->first << endl;
            cout << it->second << endl;
        }
        cout << get<1>(*reviewedIterator) << endl ;
        //getchar();
    }

    return 0;
}
