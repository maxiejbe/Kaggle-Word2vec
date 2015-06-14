#include "LabeledReview.h"

using namespace std;
using namespace boost;

LabeledReview::LabeledReview()
{
    //ctor
}

bool LabeledReview::ReadCompleteLine(stringstream* strstream){
    getline(*strstream, this->id, '\t');
    getline(*strstream, this->sentiment, '\t');
    getline(*strstream, this->review, '\n');
    return true;
}

tuple<map<unsigned long, int>, int> LabeledReview::ToReviewHashTuple(map<string, int>* excludeWords, HashingTrick* hashingTrick){
    map<unsigned long, int> hashedReview = hashingTrick->Hash(this->ToVector(excludeWords));
    return make_tuple(hashedReview, lexical_cast<int>(this->sentiment));
}

string LabeledReview::GetSentiment(){
    return this->sentiment;
}

void LabeledReview::SetSentiment(string value){
    this->sentiment = value;
}

LabeledReview::~LabeledReview()
{
    //dtor
}
