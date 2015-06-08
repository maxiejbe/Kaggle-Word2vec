#ifndef HASHINGTRICK_H
#define HASHINGTRICK_H

#include <vector>
#include <string>
#include "boost/mpl/modulus.hpp"
#include <boost/functional/hash.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/limits.hpp"
#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

class HashingTrick
{
    public:
        HashingTrick(unsigned long dimensions);
        std::map<unsigned long, int> Hash(std::vector<std::string> stringVector);
        virtual ~HashingTrick();
    protected:
    private:
        unsigned long dimensions;
};

#endif // HASHINGTRICK_H
