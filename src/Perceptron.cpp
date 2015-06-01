#include "Perceptron.h"

using namespace std;

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

void PerceptronEntry::setVectorReview(vector<int> vectorReviewIn){
    this->vectorReview = vectorReviewIn;
}

void PerceptronEntry::setLabel(int labelIn){
    this->label = labelIn;
}
vector<int> PerceptronEntry::getVectorReview(){

    return this->vectorReview;
}
int PerceptronEntry::getLabel(){
    return this->label;
}


void PerceptronOutput::setMovieID(string movieIDIn){
    this->movieID = movieIDIn;
}
void PerceptronOutput::setProbability(double probabilityIn){
    this->probability = probabilityIn;
}
string PerceptronOutput::getMovieID(){
    return this->movieID;
}
double PerceptronOutput::getProbability(){
    return this->probability;
}

double dotProduct(vector<double> vec1, vector<int> vec2){

    int dimension = vec2.size();
    double total = 0 ;

    for (int i=0; i<=dimension-1; i++){
            total += vec1[i] * vec2[i];
        }

    return total;
}

void updateWeights(vector<double>* weights,int error,PerceptronEntry hashedReview){

    for (int i = 0; i<weights->size(); i++){
        (*weights)[i] = LEARNINGRATE * error * hashedReview.getVectorReview()[i];
    }

}


vector<double> Perceptron::trainPerceptron(vector<PerceptronEntry> vectorIn, int dimension){

    int vectorDimension = vectorIn.size();
    vector<int> vectorIntAux;
    PerceptronEntry perceptronEntryAux;
    int labelAux;
    int resultado=0;
    int error = 0;
    int errorCounter = 0;
    int loopCounter = 0;
    vector<double> weights(dimension);

    while (true){
        for (int i=0; i <= vectorDimension ; i++){
            perceptronEntryAux = vectorIn[i];
            vectorIntAux = perceptronEntryAux.getVectorReview();
            labelAux = perceptronEntryAux.getLabel();

            if (dotProduct(weights, vectorIntAux)>0,5){
                resultado = 1;
            }
            else{

                resultado = 0;
            };
            error = perceptronEntryAux.getLabel() - resultado;
                if (error != 0 ){
                    errorCounter += 1;
                    updateWeights(&weights, error, perceptronEntryAux);
                }
        };
        if ((errorCounter==0) or (loopCounter == MAXLOOP)){
            break;
        };
    }

return weights;
}


