/*
 * Filename: StochasticHillClimbing.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <cassert>
#include <cstdlib>
#include <ctime>

#include "StochasticHillClimbing.h"


namespace CleverAlgorithms
{

namespace
{

inline int onemax(const std::vector<bool>& values)
{
    int res = 0;
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (values[i])
        {
            ++res;
        }
    }
    return res;
}


inline std::vector<bool> randomBits(const int kBitsCount)
{
    std::vector<bool> res(kBitsCount);
    for (int i = 0; i < kBitsCount; ++i)
    {
        res[i] = rand() > (RAND_MAX / 2);
    }
    return res;
}


inline std::vector<bool> randomNeighbor(const std::vector<bool>& current)
{
    assert(!current.empty());

    std::vector<bool> mutant(current);
    size_t pos = rand() % current.size();
    mutant[pos] = !mutant[pos];
    return mutant;
}

} /* anonymous namespace */


StochasticHillClimbing::Candidate StochasticHillClimbing::search(const int kIterLimit, const int kBitsCount)
{
    srand(static_cast<unsigned>(time(nullptr)));

    StochasticHillClimbing::Candidate best;
    best.values = randomBits(kBitsCount);
    best.cost = onemax(best.values);
    for (int iter = 0; iter < kIterLimit; ++iter)
    {
        StochasticHillClimbing::Candidate neighbor;
        neighbor.values = randomNeighbor(best.values);
        neighbor.cost = onemax(neighbor.values);
        if (neighbor.cost > best.cost)
        {
            best.values.swap(neighbor.values);
            best.cost = neighbor.cost;
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
