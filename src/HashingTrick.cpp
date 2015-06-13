#include "HashingTrick.h"

using namespace std;
using namespace boost;

HashingTrick::HashingTrick(unsigned long dimensions, int minWords, int maxWords)
{
    this->dimensions = dimensions;
    this->minWords = minWords;
    this->maxWords = maxWords;
}

map<unsigned long, int> HashingTrick::Hash(vector<string> stringReview){
    map<unsigned long, int> hashedReview;

    for(int i=this->minWords;i<=maxWords;i++){
        for(int j=0; j<stringReview.size();j++){

            string toHash;
            for(int n=0;n<=i;n++){
                if((j+n) < stringReview.size()){
                    toHash += (stringReview[j+n]);
                    if(n!=i) toHash += " ";
                }
            }
            unsigned long hashValue = hash_value(toHash) % this->dimensions;
            if(hashedReview[hashValue] == NULL){
                hashedReview[hashValue] = 1;
                continue;
            }
            hashedReview[hashValue]++;
        }
    }
    return hashedReview;
}

HashingTrick::~HashingTrick()
{
    //dtor
}
