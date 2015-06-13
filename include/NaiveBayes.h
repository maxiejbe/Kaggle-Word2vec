#ifndef NAIVEBAYES_H
#define NAIVEBAYES_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "boost/tuple/tuple.hpp"
#include <list>
#include <map>
#include <math.h>


class NaiveBayes
{
    public:
        NaiveBayes();
        void BayesTrain(std::vector<boost::tuple<std::map<unsigned long,int>,int> >TrainData);
        void BayesTest(std::vector<boost::tuple<std::map<unsigned long,int>,std::string> >TestData);
        std::map<std::string,double> Resultado();
        double Sigmoid(double num);
        virtual ~NaiveBayes();
    protected:
    private:
        std::map<unsigned long,int> hashespos;
        std::map<unsigned long,int> hashesneg;
        double pos;
        double neg;
        double total;
        std::map<std::string,double> resultado;
};

#endif // NAIVEBAYES_H
