#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <map>
#include <list>
#include <string>
#include "boost/tuple/tuple.hpp"

class Perceptron{

    public:
        Perceptron(unsigned long dimensions);
        virtual ~Perceptron();

        void TrainPerceptron(std::vector < boost::tuple < std::map < unsigned long, int >,int > > reviews);
        std::map<std::string,double> TestPerceptron(std::vector<boost::tuple<std::map<unsigned long,int>,std::string> > reviewsToPredict);
    protected:
    private:
        double DotProduct(std::map<unsigned long,int > hashedReview);
        void UpdateWeights(int error, std::map<unsigned long,int> hashedReview);

        std::map<unsigned long,double> weights;

};

#endif // PERCEPTRON_H
