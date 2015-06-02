#ifndef PERCEPTRON_H
#define PERCEPTRON_H


#include <vector>
#include<string>

using namespace std;



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

    static vector<double> trainPerceptron(vector<PerceptronEntry> vectorIn, int dimension);
    static vector<PerceptronOutput> testPerceptron(vector<double> weights, vector<PerceptronEntry> entryToPredict);

    protected:
    private:

};

#endif // PERCEPTRON_H
