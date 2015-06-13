#include "NaiveBayes.h"


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

void NaiveBayes::BayesTrain(std::vector<boost::tuple<std::map<unsigned long,int>,int> > TrainData){
    unsigned long i;
    //boost::tuple <std::map<unsigned long,int>,int> tuplaAux;
    std::map<unsigned long,int> mapAux;
    std::map<unsigned long,int>::iterator it;


    for(i=0;i<boost::size(TrainData);i++){
        //tuplaAux = TrainData[i];
        mapAux = boost::tuples::get<0>(TrainData[i]);
        if (boost::tuples::get<1>(TrainData[i])==1){
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


void NaiveBayes::BayesTest(std::vector<boost::tuple<std::map<unsigned long,int>,std::string> > TestData){

    std::string ID;
    unsigned long i;
    boost::tuple <std::map<unsigned long,int>,std::string> tuplaAux;
    std::map<unsigned long,int> mapAux;
    std::map<unsigned long,int>::iterator it;

    double cantparpositivos;
    double cantparnegativos;
    double cantidadparcial = 1;
    double probpos = pos/total; //Probabilidad de label positivo
    double probneg = neg/total; //Probabilidad de label negativo
    double probreview = 0; //Probabilidad de que el review se encuentre
    double probreviewpos = 0; //Probabilidad de que el review se encuentre dado que el label es positivo
    double probreviewneg = 0; //Probabilidad de que el review se encuentre dado que el label es negativo
    double probposreview = 1; //Probabilidad de que sea positivo dado un review
    double probnegreview = 1; //Probabilidad de que sea negativo dado un review
    double aux;

    for(i=0;i<boost::size(TestData);i++){
        //tuplaAux = TestData[i];
        mapAux = boost::tuples::get<0>(TestData[i]);
        ID = boost::tuples::get<1>(TestData[i]);
        for (it = mapAux.begin();it!=mapAux.end();++it){
            cantparnegativos = hashesneg[it->first];
            cantparpositivos = hashespos[it->first];
            if (cantparnegativos != 0 || cantparpositivos != 0)
                cantidadparcial = cantparnegativos + cantparpositivos;
            if (cantparnegativos != 0)
                probreviewneg = probreviewneg + log(cantparnegativos/neg);
            if (cantparpositivos != 0)
                probreviewpos = probreviewpos + log(cantparpositivos/pos);
            if (cantidadparcial !=0)
                probreview = probreview + log(cantidadparcial/total);
        }
        //std::cout<<"cantparpositivos: "<<cantparpositivos<<" "<<"probreviewpos: "<<probreviewpos<<" "<<"probreview: "<<probreview<<std::endl;
        probnegreview = probreviewneg+probneg;
        probposreview = probreviewpos+probpos;
        aux = Sigmoid(probposreview- probnegreview);
        if (aux > 0.0001)
            resultado[ID] = aux;
        else
            resultado[ID] = 0;
        //std::cout<<"probposreview: "<<probposreview<<std::endl;
        probreview = 1;
        probreviewpos = 1;
        probreviewneg = 1;
        probposreview = 1;
        probnegreview = 1;

    }

}

std::map<std::string,double> NaiveBayes::Resultado(){
    return resultado;

}

NaiveBayes::~NaiveBayes()
{
    //dtor
}
