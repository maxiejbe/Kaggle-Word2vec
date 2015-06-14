#include "Review.h"
#include "StringCleaner.h"

using namespace std;
using namespace boost;

Review::Review()
{
    //ctor
}

string Review::GetId(){
    return this->id;
}

void Review::SetId(string value){
    this->id = value;
}

string Review::GetReview(){
    return this->review;
}

void Review::SetReview(string value){
    this->review = value;
}

vector<string> Review::ToVector(map<string, int>* excludeWords){
    //let me explain myself, I need to get a vector of words + sentiment as a tuple
    vector<string> reviewVector;
    boost::split(reviewVector,this->review,boost::is_any_of(" "));

    //Diff between reviewVector and excludeWords and generate the tuple
    vector<string> cleanedVector;
    for (vector<string>::iterator it = reviewVector.begin(); it != reviewVector.end(); ++it){
        if((*excludeWords)[*it] == 1) continue;
        cleanedVector.push_back(*it);
    }
    return cleanedVector;
}

bool Review::FromFileLine(ifstream* str){
    string line;
    if (getline(*str,line))
    {
        stringstream iss(line);
        if (this->ReadCompleteLine(&iss))
        {
            StringCleaner::CompleteClean(&this->review);
            return true;
        }
        str->setstate(std::ios::failbit);
    }
    return false;
}

Review::~Review()
{
    //dtor
}
