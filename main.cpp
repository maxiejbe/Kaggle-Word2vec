#include <cstdlib>
#include "include/UnlabeledReview.h"
#include "include/LabeledReview.h"
#include "include/Perceptron.h"
#include "include/NaiveBayes.h"
#include "include/HashingTrick.h"
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

vector<tuple<map<unsigned long,int>,int> > HashLabeledFile(vector<LabeledReview>* labeledReviews,
                                                           HashingTrick* hashingTrick, map<string, int>* stopWords){
    vector<tuple<map<unsigned long,int>,int> > labeledReviewsHash;
    for (vector<LabeledReview>::iterator it = labeledReviews->begin(); it != labeledReviews->end(); ++it)
    {
        labeledReviewsHash.push_back(it->ToReviewHashTuple(stopWords, hashingTrick));
    }
    return labeledReviewsHash;
}

vector<tuple<map<unsigned long,int>,string> > HashUnlabeledFile(vector<UnlabeledReview>* unlabeledReviews,
                                                                HashingTrick* hashingTrick, map<string, int>* stopWords){
    vector<tuple<map<unsigned long,int>,string> > unlabeledReviewsHash;
    for (vector<UnlabeledReview>::iterator it = unlabeledReviews->begin(); it != unlabeledReviews->end(); ++it)
    {
        unlabeledReviewsHash.push_back(it->ToReviewHashTuple(stopWords, hashingTrick));
    }
    return unlabeledReviewsHash;
}

vector<UnlabeledReview> ReadUnlabeledFile(){
    vector<UnlabeledReview> unlabeledReviews;

    ifstream unlabeledReadFile("data/testData.tsv");
    if(!unlabeledReadFile.is_open() ){
        cout << "Could not read the unlabeled test data file." << endl ;
    }
    else
    {
        UnlabeledReview unlabeledReview;

        bool firstElement = true;
        while(unlabeledReview.FromFileLine(&unlabeledReadFile))
        {
            if(firstElement){
                firstElement = false;
                continue;
            }
            unlabeledReviews.push_back(unlabeledReview);
        }
        unlabeledReadFile.close();
    }
    return unlabeledReviews;
}

vector<LabeledReview> ReadLabeledFile(){
    vector<LabeledReview> labeledReviews;

    ifstream labeledReadFile("data/labeledTrainData.tsv");
    if(!labeledReadFile.is_open() ){
        cout << "Could not read the labeled train data file." << endl ;
    }
    else
    {
        LabeledReview labeledReview;

        bool firstElement = true;
        while(labeledReview.FromFileLine(&labeledReadFile))
        {
            if(firstElement){
                firstElement = false;
                continue;
            }
            labeledReviews.push_back(labeledReview);
        }
        labeledReadFile.close();
    }
    return labeledReviews;
}

void ToOutputFile(map<string, double>* evaluatedReviews){
    ofstream outputFile ("output/generatedFile.csv");
    if(!outputFile.is_open() ){
        cout << "Cannot read the output data file." << endl ;
    }
    else
    {
        outputFile << "\"id\",\"sentiment\"\n";

        for (map<string, double>::iterator it = evaluatedReviews->begin(); it != evaluatedReviews->end(); ++it)
        {
            outputFile << it->first + ",";
            outputFile << it->second;
            outputFile << "\n";
        }
        outputFile.close();
    }
}

void ToOutputFile2(map<string, double>* evaluatedReviews, vector<UnlabeledReview>* unlabeledReview){
    ofstream outputFile ("output/grupo12_probs.csv");
    double result;
    string id;

    if(!outputFile.is_open() ){
        cout << "Cannot read the output data file." << endl ;
    }
    else
    {
        for (unsigned int i = 0 ; i< unlabeledReview->size(); i++){
                id = (*unlabeledReview)[i].GetId();
                result = (*evaluatedReviews)[id];
                outputFile << result;
                outputFile << "\n";
        }
    outputFile.close();
    }
}
map<string, double> RunPerceptron(vector<tuple<map<unsigned long,int>,int> >* labeledReviews,
                                  vector<tuple<map<unsigned long,int>,string> >* unlabeledReviews,
                                  unsigned long dimensions){
    Perceptron* perceptron = new Perceptron(dimensions);

    cout << "Training Perceptron algorithm..." << endl ;
    perceptron->TrainPerceptron(*labeledReviews);
    cout << "Done" << endl ;

    cout << "Calculating Perceptron probabilities..." << endl ;
    map<string, double> perceptronResults = perceptron->TestPerceptron(*unlabeledReviews);
    cout << "Done" << endl ;

    delete perceptron;

    return perceptronResults;
}

map<string, double> RunBayes(vector<tuple<map<unsigned long,int>,int> >* labeledReviews,
                                  vector<tuple<map<unsigned long,int>,string> >* unlabeledReviews){
    NaiveBayes* bayes = new NaiveBayes();

    cout << "Training Naive Bayes algorithm..." << endl ;
    bayes->TrainBayes(*labeledReviews);
    cout << "Done" << endl ;

    cout << "Calculating Naive Bayes probabilities..." << endl ;
    map<string, double> bayesResults = bayes->TestBayes(*unlabeledReviews);
    cout << "Done" << endl ;

    delete bayes;

    return bayesResults;
}

int main(){
    unsigned long dimensions = 20000;


    map<string, int> stopWords = ReadStopWords();

    cout << "Reading labeled reviews..." << endl ;
    vector<LabeledReview> labeledReviews = ReadLabeledFile();
    cout << "Done" << endl ;

    cout << "Reading unlabeled reviews..." << endl ;
    vector<UnlabeledReview> unlabeledReviews = ReadUnlabeledFile();
    cout << "Done" << endl ;

    HashingTrick* perceptronHashingTrick = new HashingTrick(dimensions, 1, 2);

    cout << "Hashing labeled reviews for Perceptron..." << endl ;
    vector<tuple<map<unsigned long,int>,int> > perceptronLabeledReviewsHash;
    perceptronLabeledReviewsHash = HashLabeledFile(&labeledReviews, perceptronHashingTrick, &stopWords);
    cout << "Done" << endl ;

    cout << "Hashing unlabeled reviews for Perceptron..." << endl ;
    vector<tuple<map<unsigned long,int>,string> > perceptronUnlabeledReviewsHash;
    perceptronUnlabeledReviewsHash = HashUnlabeledFile(&unlabeledReviews, perceptronHashingTrick, &stopWords);
    cout << "Done" << endl ;

    delete perceptronHashingTrick;

    HashingTrick* bayesHashingTrick = new HashingTrick(dimensions, 2, 2);

    cout << "Hashing labeled reviews for Naive Bayes..." << endl ;
    vector<tuple<map<unsigned long,int>,int> > bayesLabeledReviewsHash;
    bayesLabeledReviewsHash = HashLabeledFile(&labeledReviews, bayesHashingTrick, &stopWords);
    cout << "Done" << endl ;

    cout << "Hashing unlabeled reviews for Naive Bayes..." << endl ;
    vector<tuple<map<unsigned long,int>,string> > bayesUnlabeledReviewsHash;
    bayesUnlabeledReviewsHash = HashUnlabeledFile(&unlabeledReviews, bayesHashingTrick, &stopWords);

    cout << "Done" << endl ;

    delete bayesHashingTrick;

    map<string, double> perceptronResults = RunPerceptron(&perceptronLabeledReviewsHash, &perceptronUnlabeledReviewsHash, dimensions);
    map<string, double> bayesResults = RunBayes(&bayesLabeledReviewsHash, &bayesUnlabeledReviewsHash);

    double perceptronWeight = 1;
    double bayesWeigth = 0;

    cout << "Merging calculated probabilities..." << endl ;

    map<string, double> completeResults;
    vector<tuple<map<unsigned long,int>,string> >::iterator revIterator;
    //it's taking perceptron hashes to retrieve ids, but it could be any other. Or even iterate a result map
    for (revIterator = perceptronUnlabeledReviewsHash.begin(); revIterator != perceptronUnlabeledReviewsHash.end(); ++revIterator){
        string reviewId = get<1>(*revIterator);
        completeResults[reviewId] = perceptronWeight * perceptronResults[reviewId] + bayesWeigth * bayesResults[reviewId];
    }

    cout << "Done" << endl ;

    ToOutputFile(&completeResults);
    ToOutputFile2(&completeResults, &unlabeledReviews);

    return 0;
}
