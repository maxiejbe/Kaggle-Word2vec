#ifndef PERCEPTRONOUTPUT_H
#define PERCEPTRONOUTPUT_H

#include <string>

class PerceptronOutput{
    public:
        PerceptronOutput();
        virtual ~PerceptronOutput();

        void setProduct(double prod);
        void setMovieID(std::string movieIDIn);
        void setProbability(double probabilityIn);
        double getProduct();
        std::string getMovieID();
        double getProbability();
    private:
        std::string movieID;
        double probability;
        double product;
};

#endif // PERCEPTRONOUTPUT_H
