#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

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

class Naive_Bayes
{
    public:
        Naive_Bayes();
        void bayesTrain(list<tuple<vector<string>, string> >X);
        void bayesTest(list<tuple<vector<string>, string> >X);
        vector<tuple<string, float> > Resultado();
        virtual ~Naive_Bayes();
    protected:
    private:
    vector<tuple<string, float> > vectorResultados;
    vector<string> hashespos;
    vector<string> hashesneg;
    int pos;
    int neg;
    int total;
    float buscarenvector(vector<string>hashes,string x);
};

#endif // NAIVE_BAYES_H
