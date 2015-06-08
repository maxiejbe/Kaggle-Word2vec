#include "HashingTrick.h"

using namespace std;
using namespace boost;

HashingTrick::HashingTrick(unsigned long dimensions)
{
    this->dimensions = dimensions;
}

map<unsigned long, int> HashingTrick::Hash(vector<string> stringReview){
    map<unsigned long, int> hashedReview;
    for (vector<string>::iterator it = stringReview.begin(); it != stringReview.end(); ++it){
        unsigned long hashValue = hash_value(*it) % this->dimensions;
        if(hashedReview[hashValue] == NULL){
            hashedReview[hashValue] = 1;
            continue;
        }
        hashedReview[hashValue]++;
    }
    return hashedReview;
}

HashingTrick::~HashingTrick()
{
    //dtor
}
