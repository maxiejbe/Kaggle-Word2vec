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


class NaiveBayes
{
    public:
        NaiveBayes();
        void BayesTrain(std::vector<boost::tuple<std::map<unsigned long,int>,int> >X);
        void BayesTest(std::vector<boost::tuple<std::map<unsigned long,int>,int> >X);
        std::map<int,float> Resultado();
        virtual ~NaiveBayes();
    protected:
    private:
        std::map<unsigned long,int> hashespos;
        std::map<unsigned long,int> hashesneg;
        int pos;
        int neg;
        int total;
        std::map<int,float> resultado;
};

#endif // NAIVEBAYES_H
