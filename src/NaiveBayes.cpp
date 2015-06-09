#include "NaiveBayes.h"

NaiveBayes::NaiveBayes()
{
    //ctor
    pos = 0;
    neg = 0;
    total = 0;
}

void NaiveBayes::BayesTrain(std::vector<boost::tuple<std::map<unsigned long,int>,int> > TrainData){
    unsigned long i;
    boost::tuple <std::map<unsigned long,int>,int> tuplaAux;
    std::map<unsigned long,int> mapAux;
    std::map<unsigned long,int>::iterator it = mapAux.begin();


    for(i=0;i<boost::size(TrainData);i++){
        tuplaAux = TrainData[i];
        mapAux = boost::tuples::get<0>(tuplaAux);
        if (boost::tuples::get<1>(tuplaAux)==0){
            pos++;
            for(it;it!=mapAux.end();++it)
                hashespos[it->first]=it->second;
            }
        else {
            neg++;
            for(it;it!=mapAux.end();++it)
                hashesneg[it->first]=it->second;
            }
    }
    total = pos + neg;
}

void NaiveBayes::BayesTest(std::vector<boost::tuple<std::map<unsigned long,int>,int> > TestData){

    int ID;
    unsigned long i;
    boost::tuple <std::map<unsigned long,int>,int> tuplaAux;
    std::map<unsigned long,int> mapAux;
    std::map<unsigned long,int>::iterator it = mapAux.begin();

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

    for(i=0;i<boost::size(TestData);i++){
        tuplaAux = TestData[i];
        mapAux = boost::tuples::get<0>(tuplaAux);
        ID = boost::tuples::get<1>(tuplaAux);
        for (it;it!=mapAux.end();++it){
            cantparnegativos = hashesneg[it->first];
            cantparpositivos = hashespos[it->first];
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
        resultado[ID] = probposreview;

    }

}

std::map<int,float> NaiveBayes::Resultado(){
    return resultado;

}

NaiveBayes::~NaiveBayes()
{
    //dtor
}
