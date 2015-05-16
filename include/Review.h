#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Review
{
    public:
        Review();
        virtual ~Review();

        std::string GetId();
        void SetId(std::string value);
        std::string GetReview();
        void SetReview(std::string value);

        bool FromFileLine(std::ifstream* str);

    protected:
        std::string id;
        std::string review;

        virtual bool ReadCompleteLine(std::stringstream* strstream) = 0;

    private:
};

#endif // REVIEW_H
