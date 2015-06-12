#include "Perceptron.h"

using namespace std;
using namespace boost;

const double LEARNINGRATE = 0.1;
const int MAXLOOP = 50;

Perceptron::Perceptron()
{
    //ctor
}

Perceptron::~Perceptron()
{
    //dtor
}

double dotProduct(vector<double> weights, map<unsigned long,int > hashedReview){
    double total = 0 ;

    for (map<unsigned long,int>::iterator it = hashedReview.begin(); it != hashedReview.end(); ++it)
    {
        //from the it: first is the word hash value, second is the amount of hashes
        total += weights[it->first] * it->second;
    }
    return total;
}

void updateWeights(vector<double>* weights,int error,map<unsigned long,int> hashedReview){
    for (map<unsigned long,int>::iterator it = hashedReview.begin(); it != hashedReview.end(); ++it)
    {
        //from the it: first is the word hash value, second is the amount of hashes
        (*weights)[it->first] += LEARNINGRATE * error * it->second;
    }
}

vector<double> Perceptron::TrainPerceptron(vector < tuple < map<unsigned long,int >,int > > reviews, unsigned long dimension){
    int errorCounter = 0;
    int loopCounter = 0;

    vector<double> weights(dimension);

    while (true){
        for (int i=0; i < reviews.size() ; i++){

            //product between weight and review: 1 or 0 depending on the result
            int resultado = dotProduct(weights, get<0>(reviews[i])) > 0.5 ? 1 : 0;

            //if error calculation is != 0
            int error = get<1>(reviews[i]) - resultado;
            if (error != 0 ){
                errorCounter ++;
                updateWeights(&weights, error, get<0>(reviews[i]));
            }
        }
        loopCounter++;

        if ((errorCounter==0) or (loopCounter == MAXLOOP)){
            break;
        }
        errorCounter = 0;
    }
    return weights;
}

map<string, double> Perceptron::TestPerceptron(vector<double> weights, vector<tuple<map<unsigned long,int>,string> > reviewsToPredict){

    map<string, double> valuatedReviews;
    double maxProduct = 0;
    double minProduct = 0;

    for (vector<tuple<map<unsigned long,int>,string> >::iterator revIterator = reviewsToPredict.begin(); revIterator != reviewsToPredict.end(); ++revIterator)
    {
        double product = dotProduct(weights, get<0>(*revIterator));
        if (product>maxProduct) maxProduct=product;
        if (product<minProduct) minProduct=product;

        //first product calculation to review id index
        valuatedReviews[get<1>(*revIterator)] = product;
    }

    //normalize distance
    for (map<string,double>::iterator mapRevIterator = valuatedReviews.begin(); mapRevIterator != valuatedReviews.end(); ++mapRevIterator)
    {
        double currentProbability = mapRevIterator->second;
        mapRevIterator->second = (currentProbability - minProduct) / (maxProduct - minProduct);
    }
    return valuatedReviews;
}


