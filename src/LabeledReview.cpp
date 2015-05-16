#include "LabeledReview.h"

using namespace std;

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
