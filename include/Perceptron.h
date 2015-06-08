#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <list>
#include "PerceptronOutput.h"
#include "boost/tuple/tuple.hpp"

class Perceptron{

    public:
        Perceptron();
        virtual ~Perceptron();
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro su label de opinion positiva o negativa
        //Deuvlve un vector de double que representa la "pendiente" de la recta que crea perceptron para dividir el espacio.

        static std::vector<double> trainPerceptron(std::vector < boost::tuple < std::vector < boost::tuple < unsigned long, int > >,int > > reviews, unsigned long dimension);
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro un string con su ID correspondiente.
        //Devuelve un vector de Tuplas que representa el primer campo el ID y el segundo la probabilidad.
        static std::vector<boost::tuple<std::string,double> > testPerceptron(std::vector<double> weights, std::vector<boost::tuple<std::vector<int>,std::string> > entryToPredict);
    protected:
    private:



};

#endif // PERCEPTRON_H
