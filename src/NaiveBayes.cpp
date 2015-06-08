#include "NaiveBayes.h"

NaiveBayes::NaiveBayes()
{
    //ctor
    pos = 0;
    neg = 0;
    total = 0;
}

void NaiveBayes::BayesTrain(list<tuple<vector<string>, string> >X){
    int i;
    list<tuple<vector<string>, string> >::iterator k = X.begin();
    tuple <vector<string>,string> tuplaAux;
    vector<string> vectorAux;
    while (k != X.end()){
        tuplaAux = *k++;
        vectorAux = get<0>(tuplaAux);
        if (get<1>(tuplaAux).compare("1")==0){
            pos++;
            for(i=0;i<size(vectorAux);i++)
                hashespos.push_back(vectorAux[i]);
            }
        else {
            neg++;
            for(i=0;i<size(vectorAux);i++)
                hashesneg.push_back(vectorAux[i]);
            }
    }
    total = pos + neg;
}

float NaiveBayes::BuscarEnVector(vector<string>hashes,string x){
    int cantidad = 0;
    for (int i=0;i<size(hashes);i++)
        if (hashes[i].compare(x))
            cantidad++;
    return cantidad;
}

void NaiveBayes::BayesTest(list<tuple<vector<string>, string> >X){
    vector<string> resultado;
    vector<string> vectorAux;
    tuple <vector<string>,string> tuplaAux;
    string stringAux;
    list<tuple<vector<string>, string> >::iterator k = X.begin();
    float cantparpositivos = 0;
    float cantparnegativos = 0;
    float cantidadparcial = 0;
    float probpos = (float) pos/total; //Probabilidad de label positivo
    float probneg = (float) neg/total; //Probabilidad de label negativo
    float probreview = 1; //Probabilidad de que el review se encuentre
    float probreviewpos = 1; //Probabilidad de que el review se encuentre dado que el label es positivo
    float probreviewneg = 1; //Probabilidad de que el review se encuentre dado que el label es negativo
    float probposreview; //Probabilidad de que sea positivo dado un review
    float probnegreview; //Probabilidad de que sea negativo dado un review

    while (k != X.end()){
        tuplaAux = *k++;
        vectorAux = get<0>(tuplaAux);
        stringAux = get<1>(tuplaAux);
        for (int i=0;i<size(vectorAux);i++){
            cantparnegativos = BuscarEnVector(hashesneg,vectorAux[i]);
            cantparpositivos = BuscarEnVector(hashespos,vectorAux[i]);
            if (cantparnegativos != 0 || cantparpositivos != 0)
                cantidadparcial = cantparnegativos + cantparpositivos;
            if (cantparnegativos != 0)
                probreviewneg = probreviewneg * (cantparnegativos/neg);
            if (cantparpositivos != 0)
                probreviewpos = probreviewpos * (cantparpositivos/pos);
            if (cantidadparcial !=0)
                probreview = probreview * (cantidadparcial/total);
        }
        probnegreview = (probreviewneg*probneg)/probreview;
        probposreview = (probreviewpos*probpos)/probreview;
        tuple<string, float> idprob = make_tuple(stringAux, probposreview);
        vectorResultados.push_back(idprob);

    }

}

vector<tuple<string, float> > NaiveBayes::Resultado(){
    return vectorResultados;

}

NaiveBayes::~NaiveBayes()
{
    //dtor
}
