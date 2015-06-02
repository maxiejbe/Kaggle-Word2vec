#ifndef HASHINGTRICK_H
#define HASHINGTRICK_H

#include <vector>
#include <string>


class HashingTrick
{
    public:
        HashingTrick(int dimensions);
        std::vector<int> Hash(std::vector<std::string> stringVector);
        virtual ~HashingTrick();
    protected:
    private:
};

#endif // HASHINGTRICK_H
