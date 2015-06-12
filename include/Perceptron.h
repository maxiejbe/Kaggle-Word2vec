#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <map>
#include <list>
#include <string>
#include "boost/tuple/tuple.hpp"

class Perceptron{

    public:
        Perceptron();
        virtual ~Perceptron();
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro un string con su ID correspondiente.
        //Devuelve un vector de Tuplas que representa el primer campo el ID y el segundo la probabilidad.
        static std::map<std::string,double> TestPerceptron(std::vector<double> weights, std::vector<boost::tuple<std::map<unsigned long,int>,std::string> > entryToPredict);
        //Toma un vector de tuplas que en el primer campo tiene la review hasheada con hashingTrick y en el otro su label de opinion positiva o negativa
        //Devuelve un vector de double que representa la "pendiente" de la recta que crea perceptron para dividir el espacio.
        static std::vector<double> TrainPerceptron(std::vector < boost::tuple < std::map < unsigned long, int >,int > > reviews, unsigned long dimension);
    protected:
    private:



};

#endif // PERCEPTRON_H
