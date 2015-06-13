#include "Perceptron.h"

using namespace std;
using namespace boost;

const double LEARNINGRATE = 0.1;
const int MAXLOOP = 50;

Perceptron::Perceptron(unsigned long dimensions)
{
    this->weights = new vector<double>(dimensions);
}

Perceptron::~Perceptron()
{
    delete this->weights;
}

double Perceptron::DotProduct(map<unsigned long,int > hashedReview){
    double total = 0 ;

    for (map<unsigned long,int>::iterator it = hashedReview.begin(); it != hashedReview.end(); ++it)
    {
        //from the it: first is the word hash value, second is the amount of hashes
        total += (*this->weights)[it->first] * it->second;
    }
    return total;
}

void Perceptron::UpdateWeights(int error, map<unsigned long,int> hashedReview){
    for (map<unsigned long,int>::iterator it = hashedReview.begin(); it != hashedReview.end(); ++it)
    {
        //from the it: first is the word hash value, second is the amount of hashes
        (*this->weights)[it->first] += LEARNINGRATE * error * it->second;
    }
}

void Perceptron::TrainPerceptron(vector < tuple < map<unsigned long,int >,int > > reviews){
    int errorCounter = 0;
    int loopCounter = 0;

    while (true){
        for (int i=0; i < reviews.size() ; i++){

            //product between weight and review: 1 or 0 depending on the result
            int resultado = DotProduct(get<0>(reviews[i])) > 0.5 ? 1 : 0;

            //if error calculation is != 0
            int error = get<1>(reviews[i]) - resultado;
            if (error != 0 ){
                errorCounter ++;
                UpdateWeights(error, get<0>(reviews[i]));
            }
        }
        loopCounter++;

        if ((errorCounter==0) or (loopCounter == MAXLOOP)){
            break;
        }
        errorCounter = 0;
    }
}

map<string, double> Perceptron::TestPerceptron(vector<tuple<map<unsigned long,int>,string> > reviewsToPredict){

    map<string, double> valuatedReviews;
    double maxProduct = 0;
    double minProduct = 0;

    for (vector<tuple<map<unsigned long,int>,string> >::iterator revIterator = reviewsToPredict.begin(); revIterator != reviewsToPredict.end(); ++revIterator)
    {
        double product = DotProduct(get<0>(*revIterator));
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


