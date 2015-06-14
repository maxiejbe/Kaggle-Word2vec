#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/lexical_cast.hpp"
#include <map>
#include "HashingTrick.h"

class Review
{
    public:
        Review();
        virtual ~Review();

        std::string GetId();
        void SetId(std::string value);
        std::string GetReview();
        void SetReview(std::string value);

        std::vector<std::string> ToVector(std::map<std::string, int>* excludeWords);

        bool FromFileLine(std::ifstream* str);

    protected:
        std::string id;
        std::string review;

        virtual bool ReadCompleteLine(std::stringstream* strstream) = 0;

    private:
};

#endif // REVIEW_H
