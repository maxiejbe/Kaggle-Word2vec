#ifndef PERCEPTRON_H
#define PERCEPTRON_H


#include <vector>
#include<string>

using namespace std;



class PerceptronEntry{

    public: vector<int> vectorReview;
    public: int label;

    public:
        void setVectorReview(vector<int> vectorReviewIn);
        void setLabel(int labelIn);
        vector<int> getVectorReview();
        int getLabel();
};

class PerceptronOutput{
    public: string movieID;
    public: double probability;

    public:
        void   setMovieID(string movieIDIn);
        void   setProbability(double probabilityIn);
        string getMovieID();
        double getProbability();

};

class Perceptron{
    public:
        Perceptron();
        virtual ~Perceptron();

    static vector<double>* trainPerceptron(vector<PerceptronEntry> vectorIn, int dimension);
    static vector<PerceptronOutput> testPerceptron(vector<double> weights, vector<PerceptronEntry> entryToPredict);

    protected:
    private:

};

#endif // PERCEPTRON_H
