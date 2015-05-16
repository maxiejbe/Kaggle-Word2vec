#ifndef UNLABELEDREVIEW_H
#define UNLABELEDREVIEW_H

#include <sstream>
#include "Review.h"

class UnlabeledReview: public Review
{
    public:
        UnlabeledReview();
        virtual ~UnlabeledReview();

        virtual bool ReadCompleteLine(std::stringstream* strstream);
    protected:
    private:
};

#endif // UNLABELEDREVIEW_H
