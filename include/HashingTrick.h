#ifndef HASHINGTRICK_H
#define HASHINGTRICK_H

#include <vector>
#include <string>
#include "boost/mpl/modulus.hpp"
#include <boost/functional/hash.hpp>
#include "boost/limits.hpp"
#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

class HashingTrick
{
    public:
        HashingTrick(int dimensions);
        std::vector<int> Hash(std::vector<std::string> stringVector);
        virtual ~HashingTrick();
    protected:
    private:
        int dimensions;
};

#endif // HASHINGTRICK_H
