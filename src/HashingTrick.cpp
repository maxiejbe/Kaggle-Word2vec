#include "HashingTrick.h"

using namespace std;
using namespace boost;

HashingTrick::HashingTrick(unsigned long dimensions)
{
    this->dimensions = dimensions;
}

vector<int> HashingTrick::Hash(vector<string> stringReview){
//    int arr[this->dimensions];
//    //initialize
//    for(unsigned long i=0; i<(this->dimensions); ++i){
//        arr[i] = 0;
//    }
//    vector<int> hashedReview (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    vector<int> hashedReview(this->dimensions);

    for(unsigned long i=0; i<(this->dimensions); ++i){
        hashedReview[i] = 0;
    }

    //hash!
    for (vector<string>::iterator it = stringReview.begin(); it != stringReview.end(); ++it){
        hashedReview[hash_value(*it) % this->dimensions] = 1;
    }
    return hashedReview;
}

HashingTrick::~HashingTrick()
{
    //dtor
}
