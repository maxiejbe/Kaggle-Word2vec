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

        boost::tuple<std::map<unsigned long, int>, std::string> ToReviewHashTuple(std::map<std::string, int>* excludeWords,
                                                              HashingTrick* hashingTrick);

    protected:
    private:
};

#endif // UNLABELEDREVIEW_H
