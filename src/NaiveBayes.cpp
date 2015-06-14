#include "NaiveBayes.h"

using namespace std;
using namespace boost;

NaiveBayes::NaiveBayes()
{
    //ctor
    pos = 0;
    neg = 0;
    total = 0;
}

double NaiveBayes::Sigmoid(double num){
    return 1/(1+exp(num));
}

void NaiveBayes::TrainBayes(vector<tuple<map<unsigned long,int>,int> > reviews){
    unsigned long i;
    map<unsigned long,int> mapAux;
    map<unsigned long,int>::iterator it;

    for(i=0;i<reviews.size();i++){
        mapAux = get<0>(reviews[i]);
        if (tuples::get<1>(reviews[i])==1){
            pos++;
            for(it = mapAux.begin();it!=mapAux.end();++it)
                hashespos[it->first]+=it->second;
            }
        else {
            neg++;
            for(it = mapAux.begin();it!=mapAux.end();++it)
                hashesneg[it->first]+=it->second;
            }
    }
    total = pos + neg;
}


map<string,double> NaiveBayes::TestBayes(vector<tuple<map<unsigned long,int>,string> > reviewsToPredict){

    string reviewId;
    unsigned long i;
    tuple<map<unsigned long,int>,string> tuplaAux;
    map<unsigned long,int> mapAux;
    map<unsigned long,int>::iterator it;

    double cantparpositivos;
    double cantparnegativos;
    double cantidadparcial = 1;
    double probpos = pos/total; //Probabilidad de label positivo
    double probneg = neg/total; //Probabilidad de label negativo
    double probreview = 0; //Probabilidad de que el review se encuentre
    double probreviewpos = 0; //Probabilidad de que el review se encuentre dado que el label es positivo
    double probreviewneg = 0; //Probabilidad de que el review se encuentre dado que el label es negativo
    double probposreview; //Probabilidad de que sea positivo dado un review
    double probnegreview; //Probabilidad de que sea negativo dado un review
    double aux;

    for(i=0;i<reviewsToPredict.size();i++){
        mapAux = get<0>(reviewsToPredict[i]);
        reviewId = get<1>(reviewsToPredict[i]);
        for (it = mapAux.begin();it!=mapAux.end();++it){
            cantparnegativos = hashesneg[it->first];
            cantparpositivos = hashespos[it->first];
            if (cantparnegativos != 0 || cantparpositivos != 0)
                cantidadparcial = cantparnegativos + cantparpositivos;
            if (cantparnegativos != 0)
                probreviewneg = probreviewneg + log(cantparnegativos/neg);
            else
                probreviewneg = probreviewneg + log(1/neg);
            if (cantparpositivos != 0)
                probreviewpos = probreviewpos + log(cantparpositivos/pos);
            else
                probreviewpos = probreviewpos + log(1/pos);
            if (cantidadparcial !=0)
                probreview = probreview + log(cantidadparcial/total);
            else
                probreview = probreview + log(1/total);
        }
        //std::cout<<"cantparpositivos: "<<cantparpositivos<<" "<<"probreviewpos: "<<probreviewpos<<" "<<"probreview: "<<probreview<<std::endl;
        probnegreview = probreviewneg+probneg;
        probposreview = probreviewpos+probpos;
        aux = Sigmoid(probposreview - probnegreview);
        if (aux > 0.0001)
            resultado[reviewId] = aux;
        else
            resultado[reviewId] = 0;
        //std::cout<<"probposreview: "<<probposreview<<std::endl;
        probreview = 0;
        probreviewpos = 0;
        probreviewneg = 0;

    }
    return resultado;
}

NaiveBayes::~NaiveBayes()
{
    //dtor
}
