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

double dotProduct(vector<double> vec1, vector < tuple<unsigned long,int > > vec2){

    int dimension = vec2.size();
    unsigned long posicionVec2 = 0;
    int cantPosicionVec2 = 0;
    double total = 0 ;


    for (int i=0; i<dimension; i++){
            posicionVec2 = get<0>(vec2[i]);
            cantPosicionVec2 = get<1>(vec2[i]);
            total += vec1[posicionVec2] * cantPosicionVec2;
        }

    return total;
}

void updateWeights(vector<double>* weights,int error,vector<tuple<unsigned long,int> > hashedReview){

    unsigned long hashAux;
    int cantHash;

    for (unsigned long i = 0; i<hashedReview.size();i++){

        hashAux = get<0>(hashedReview[i]);
        cantHash = get<1>(hashedReview[i]);

        (*weights)[hashAux] += LEARNINGRATE * error * cantHash;
    }
  //  for (unsigned int i = 0; i<=weights->size()-1; i++){
  //      (*weights)[i] = LEARNINGRATE * error * hashedReview[i];
  //  }

}

vector<double> Perceptron::trainPerceptron(vector < tuple < vector < tuple < unsigned long,int > >,int > > reviews, unsigned long dimension){


    int reviewsCount = reviews.size();
    vector<tuple<unsigned long,int> > vectorLongYCantAux;
   // tuple<vector<unsigned long>, int> tupleAux();
    int resultado=0;
    int error = 0;
    int errorCounter = 0;
    int loopCounter = 0;
    double product = 0;

    vector<double> weights(dimension);

    while (true){
        for (int i=0; i <= reviewsCount-1 ; i++){

            vectorLongYCantAux = get<0>(reviews[i]);
            product = dotProduct(weights, vectorLongYCantAux);
            if (product > 0.5) {
                resultado = 1;
            }
            else{
                resultado = 0;
            };
            error = get<1>(reviews[i]) - resultado;
            if (error != 0 ){
                errorCounter += 1;
                updateWeights(&weights, error, vectorLongYCantAux);
            }
        }
        loopCounter+=1;

        if ((errorCounter==0) or (loopCounter == MAXLOOP)){
            break;
        }
        errorCounter = 0;
    }
    return weights;
}

vector<tuple<string, double> > testPerceptron(vector<double> weights, vector < tuple < vector < tuple < unsigned long,int > >,string > > entryToPredict){

    vector<PerceptronOutput> auxVectorOfOutput(weights.size());
    vector<tuple<string, double> > vectorToReturn(weights.size());
    tuple<string, double> tupleAux;
    PerceptronOutput pOutputAux;
    double product = 0;
    double productMax = 0;
    double productMin = 0;
    double probabilityAux = 0;

    for (unsigned long i=0;i<weights.size();i++){
        //calculo producto entre weights y la entrada
        product = dotProduct(weights, get<0>(entryToPredict[i]));

        if (product>productMax) productMax=product;
        if (product<productMin) productMin=product;

        pOutputAux.setProduct(product);
        pOutputAux.setMovieID(get<1>(entryToPredict[i]));
        auxVectorOfOutput[i] = pOutputAux;
    }

    for (unsigned long j=0;j<entryToPredict.size();j++){
        //normalizo distancia
        probabilityAux = ((auxVectorOfOutput[j].getProduct() - productMin) / (productMax-productMin));
        vectorToReturn[j] = make_tuple(auxVectorOfOutput[j].getMovieID(), probabilityAux);

    }
    return vectorToReturn;
}


