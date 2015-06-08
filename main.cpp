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

    ifstream labeledReadFile("data/labeledTrainData.tsv");
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

vector<tuple<map<unsigned long,int>,string> > ReadUnlabeledFile(long dimensions){
    vector<tuple<map<unsigned long,int>,string> > unlabeledReviews;
    UnlabeledReview unlabeledReview;

    map<string, int> stopWords = ReadStopWords();

    ifstream unlabeledReadFile("data/unlabeledTrainData.tsv");
    if(!unlabeledReadFile.is_open() ){
        cout << "Cannot read the unlabeled train data file." << endl ;
    }
    else
    {
        HashingTrick* hashingTrick = new HashingTrick(dimensions);

        bool firstElement = true;
        while(unlabeledReview.FromFileLine(&unlabeledReadFile))
        {
            if(firstElement){
                firstElement = false;
                continue;
            }
            //let me explain myself, I need to get a vector of words + sentiment as a tuple
            vector<string> reviewVector;
            string reviewString = unlabeledReview.GetReview();
            boost::split(reviewVector,reviewString,boost::is_any_of(" "));

            //Diff between reviewVector and stopWords and generate the tuple
            vector<string> cleanedVector;
            for (vector<string>::iterator it = reviewVector.begin(); it != reviewVector.end(); ++it){
                if(stopWords[(*it)] == 1) continue;
                cleanedVector.push_back(*it);
            }
            map<unsigned long, int> hashedReview = hashingTrick->Hash(cleanedVector);
            tuple<map<unsigned long, int>, string> unlabeledReviewTuple = make_tuple(hashedReview, unlabeledReview.GetId());
            unlabeledReviews.push_back(unlabeledReviewTuple);
        }

        delete hashingTrick;
        unlabeledReadFile.close();
    }

    return unlabeledReviews;
}


int main()
{
    long dimensions = 20000;

    cout << "Processing labeled reviews..." << endl ;
    vector<tuple<map<unsigned long,int>,int> > labeledReviews = ReadLabeledFile(dimensions);
    cout << "Done" << endl ;

    cout << "Calculating Perceptron weights..." << endl ;
    vector<double> percentronWeights = Perceptron::TrainPerceptron(labeledReviews, dimensions);
    cout << "Done" << endl ;

    cout << "Processing unlabeled reviews..." << endl ;
    vector<tuple<map<unsigned long,int>,string> > unlabeledReviews = ReadUnlabeledFile(dimensions);
    cout << "Done" << endl ;

    cout << "Calculating Perceptron probabilities..." << endl ;
    vector<tuple<string, double> > evaluatedReviews = Perceptron::TestPerceptron(percentronWeights, unlabeledReviews);
    cout << "Done" << endl ;


    for (vector<tuple<string, double> >::iterator it = evaluatedReviews.begin(); it != evaluatedReviews.end(); ++it)
    {
        cout << get<0>(*it) << endl;
        cout << get<1>(*it) << endl;
    }

    return 0;
}
