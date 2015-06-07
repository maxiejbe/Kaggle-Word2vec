#ifndef PERCEPTRON_H
#define PERCEPTRON_H


#include <vector>
#include <list>
#include <string>
#include "boost/tuple/tuple.hpp"

using namespace std;
using namespace boost;



class PerceptronEntry{
    public: string movieID;
    public: vector<int> vectorReview;
    public: int label;

    public:
        void setMovieID(string movieIDIn);
        void setVectorReview(vector<int> vectorReviewIn);
        void setLabel(int labelIn);
        vector<int> getVectorReview();
        int getLabel();
        string getMovieID();
};

class PerceptronOutput{
    public: string movieID;
    public: double probability;
    public: double product;

    public:
        void   setProduct(double prod);
        void   setMovieID(string movieIDIn);
        void   setProbability(double probabilityIn);
        double getProduct();
        string getMovieID();
        double getProbability();

};

class Perceptron{
    public:
        Perceptron();
        virtual ~Perceptron();
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro su label de opinion positiva o negativa
        //Deuvlve un vector de double que representa la "pendiente" de la recta que crea perceptron para dividir el espacio.
        static vector<double> trainPerceptron(vector < tuple < vector<int>,int> > vectorIn, int dimension);
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro un string con su ID correspondiente.
        //Devuelve un vector de Tuplas que representa el primer campo el ID y el segundo la probabilidad.
        static vector<tuple<string, double> > testPerceptron(vector<double> weights, vector < tuple < vector<int>,string> > entryToPredict);
    protected:
    private:

};

#endif // PERCEPTRON_H
