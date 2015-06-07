#include "Perceptron.h"

using namespace std;
using namespace boost;

const double LEARNINGRATE = 0.05;
const int MAXLOOP = 50;

Perceptron::Perceptron()
{
    //ctor
}

Perceptron::~Perceptron()
{
    //dtor
}

double dotProduct(vector<double> vec1, vector<int> vec2){

    int dimension = vec2.size();
    double total = 0 ;

    for (int i=0; i<=dimension-1; i++){
            total += vec1[i] * vec2[i];
        }

    return total;
}

void updateWeights(vector<double>* weights,int error,vector<int> hashedReview){

    for (unsigned int i = 0; i<=weights->size()-1; i++){
        (*weights)[i] = LEARNINGRATE * error * hashedReview[i];
    }

}

vector<double> Perceptron::trainPerceptron(vector<tuple<vector<int>,int> > reviews, int dimension){

    int reviewsCount = reviews.size();
    vector<int> vectorIntAux;
    tuple<vector<int>, int> tupleAux();
    int resultado=0;
    int error = 0;
    int errorCounter = 0;
    int loopCounter = 0;
    double dp = 0;
    vector<double> weights(dimension);

    while (true){
        for (int i=0; i <= reviewsCount ; i++){

            vectorIntAux = get<0>(reviews[i]);
            dp = dotProduct(weights, vectorIntAux);
            if (dp > 0.5) {
                resultado = 1;
            }
            else{
                resultado = 0;
            };
            error = get<1>(reviews[i]) - resultado;
                if (error != 0 ){
                    errorCounter += 1;
                    updateWeights(&weights, error, vectorIntAux);
                }
        };
        if ((errorCounter==0) or (loopCounter == MAXLOOP)){
            break;
        };
    }
    return weights;
}

vector<tuple<string, double> > testPerceptron(vector<double> weights, vector < tuple < vector<int>,string> > entryToPredict){
    vector<PerceptronOutput> auxVectorOfOutput(weights.size());
    vector<tuple<string, double> > vectorToReturn(weights.size());
    tuple<string, double> tupleAux;
    PerceptronOutput pOutputAux;
    double dp = 0;
    double dpMax = 0;
    double dpMin = 0;
    double probabilityAux = 0;

    for (unsigned int i=0;i<=weights.size()-1;i++){
        //calculo producto entre weights y la entrada
        dp = dotProduct(weights, get<0>(entryToPredict[i]));

        if (dp>dpMax) dpMax=dp;
        if (dp<dpMin) dpMin=dp;

        pOutputAux.setProduct(dp);
        pOutputAux.setMovieID(get<1>(entryToPredict[i]));
        auxVectorOfOutput[i] = pOutputAux;
    }

    for (unsigned int j=0;j<=entryToPredict.size()-1;j++){
        //normalizo distancia
        probabilityAux = ((auxVectorOfOutput[j].getProduct() - dpMin) / (dpMax-dpMin));
        vectorToReturn[j] = make_tuple(auxVectorOfOutput[j].getMovieID(), probabilityAux);

    }
    return vectorToReturn;
}


