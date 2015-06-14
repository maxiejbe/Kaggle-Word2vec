#include "UnlabeledReview.h"

using namespace std;
using namespace boost;

UnlabeledReview::UnlabeledReview()
{
    //ctor
}

bool UnlabeledReview::ReadCompleteLine(stringstream* strstream){
    getline(*strstream, this->id, '\t');
    getline(*strstream, this->review, '\n');
    return true;
}

tuple<map<unsigned long, int>, string> UnlabeledReview::ToReviewHashTuple(map<string, int>* excludeWords, HashingTrick* hashingTrick){
    map<unsigned long, int> hashedReview = hashingTrick->Hash(this->ToVector(excludeWords));
    return make_tuple(hashedReview, this->id);
}


UnlabeledReview::~UnlabeledReview()
{
    //dtor
}
