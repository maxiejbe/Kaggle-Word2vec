#ifndef LABELEDREVIEW_H
#define LABELEDREVIEW_H

#include <sstream>
#include "Review.h"

class LabeledReview: public Review
{
    public:
        std::string GetSentiment();
        void SetSentiment(std::string value);
        LabeledReview();
        virtual ~LabeledReview();

        boost::tuple<std::map<unsigned long, int>, int> ToReviewHashTuple(std::map<std::string, int>* excludeWords,
                                                              HashingTrick* hashingTrick);

    protected:
        virtual bool ReadCompleteLine(std::stringstream* strstream);

    private:
        std::string sentiment;
};

#endif // LABELEDREVIEW_H
