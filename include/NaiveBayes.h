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

using namespace std;
using namespace boost;

class NaiveBayes
{
    public:
        NaiveBayes();
        void BayesTrain(list<tuple<vector<string>, string> >X);
        void BayesTest(list<tuple<vector<string>, string> >X);
        vector<tuple<string, float> > Resultado();
        virtual ~NaiveBayes();
    protected:
    private:
        vector<tuple<string, float> > vectorResultados;
        vector<string> hashespos;
        vector<string> hashesneg;
        int pos;
        int neg;
        int total;
        float BuscarEnVector(vector<string>hashes,string x);
};

#endif // NAIVEBAYES_H
