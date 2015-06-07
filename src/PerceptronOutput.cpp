#include "PerceptronOutput.h"

using namespace std;

PerceptronOutput::PerceptronOutput()
{
    //ctor
}

PerceptronOutput::~PerceptronOutput()
{
    //dtor
}

void PerceptronOutput::setMovieID(string movieIDIn){
    this->movieID = movieIDIn;
}
void PerceptronOutput::setProbability(double probabilityIn){
    this->probability = probabilityIn;
}
void PerceptronOutput::setProduct(double prob){
    this->product=prob;
}
string PerceptronOutput::getMovieID(){
    return this->movieID;
}
double PerceptronOutput::getProbability(){
    return this->probability;
}
double PerceptronOutput::getProduct(){
    return this->product;
}
