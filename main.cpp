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
        cout << "Could not read the stop words data file." << endl ;
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
        cout << "Could not read the labeled train data file." << endl ;
    }
    else
    {
        //single words and phrases of two words
        HashingTrick* hashingTrick = new HashingTrick(dimensions, 1, 2);

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

    ifstream unlabeledReadFile("data/testData.tsv");
    if(!unlabeledReadFile.is_open() ){
        cout << "Could not read the unlabeled test data file." << endl ;
    }
    else
    {
        //single words and phrases of two words
        HashingTrick* hashingTrick = new HashingTrick(dimensions, 1, 2);

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

void ToOutputFile(map<string, double> evaluatedReviews){
    ofstream outputFile ("output/generatedFile.csv");
    if(!outputFile.is_open() ){
        cout << "Cannot read the output data file." << endl ;
    }
    else
    {
        outputFile << "\"id\",\"sentiment\"\n";

        for (map<string, double>::iterator it = evaluatedReviews.begin(); it != evaluatedReviews.end(); ++it)
        {
            outputFile << it->first + ",";
            outputFile << it->second;
            outputFile << "\n";
        }
        outputFile.close();
    }
}

int main()
{
    unsigned long dimensions = 4000000;

    cout << "Processing labeled reviews..." << endl ;
    vector<tuple<map<unsigned long,int>,int> > labeledReviews = ReadLabeledFile(dimensions);
    cout << "Done" << endl ;

    cout << "Processing unlabeled reviews..." << endl ;
    vector<tuple<map<unsigned long,int>,string> > unlabeledReviews = ReadUnlabeledFile(dimensions);
    cout << "Done" << endl ;

    Perceptron* perceptron = new Perceptron(dimensions);

    cout << "Training Perceptron algorithm..." << endl ;
    perceptron->TrainPerceptron(labeledReviews);
    cout << "Done" << endl ;

    cout << "Calculating Perceptron probabilities..." << endl ;
    map<string, double> evaluatedReviews = perceptron->TestPerceptron(unlabeledReviews);
    cout << "Done" << endl ;

    ToOutputFile(evaluatedReviews);

    delete perceptron;

    return 0;
}
