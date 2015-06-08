#include "HashingTrick.h"

using namespace std;
using namespace boost;

HashingTrick::HashingTrick(unsigned long dimensions)
{
    this->dimensions = dimensions;
}

vector<tuple<unsigned long, int> > HashingTrick::Hash(vector<string> stringReview){
    vector<tuple<unsigned long, int> > hashedReview;
    for (vector<string>::iterator it = stringReview.begin(); it != stringReview.end(); ++it){
        unsigned long hashValue = hash_value(*it) % this->dimensions;

        tuple<unsigned long, int> reviewTuple = make_tuple(hashValue, 1);
        hashedReview.push_back(reviewTuple);
    }
    return hashedReview;
}

HashingTrick::~HashingTrick()
{
    //dtor
}
