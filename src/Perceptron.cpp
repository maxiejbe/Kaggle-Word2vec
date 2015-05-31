#include "Perceptron.h"

using namespace std;

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

double dotProduct(vector<double>* vec1, vector<int> vec2){

    int dimension = vec2.size();
    double total = 0 ;

    int a, c ;
    int* b;

    c = a*(*b);


    for (int i=0; i<=dimension-1; i++){

        }

}


vector<double>* Perceptron::trainPerceptron(vector<PerceptronEntry> vectorIn, int dimension){

    int vectorDimension = vectorIn.size();
    vector<int> vectorIntAux;
    PerceptronEntry perceptronEntryAux;
    int labelAux;
    int resultado=0;
    double result;


    vector<double>* weights = new vector<double>(dimension);

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








    return weights;
    }

}


