#include "Review.h"
#include "StringCleaner.h"

using namespace std;

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

bool Review::FromFileLine(ifstream* str){
    string line;
    if (getline(*str,line))
    {
        stringstream iss(line);
        if (this->ReadCompleteLine(&iss))
        {
            //StringCleaner::CompleteClean(&this->review);
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
