#include "UnlabeledReview.h"

using namespace std;

UnlabeledReview::UnlabeledReview()
{
    //ctor
}

bool UnlabeledReview::ReadCompleteLine(stringstream* strstream){
    getline(*strstream, this->id, '\t');
    getline(*strstream, this->review, '\n');
    return true;
}

UnlabeledReview::~UnlabeledReview()
{
    //dtor
}
