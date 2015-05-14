/*
 * Filename: RandomSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "RandomSearch.h"


namespace CleverAlgorithms
{

namespace
{

inline float objectiveFunction(const std::vector<float>& values)
{
    float res = 0.0f;
    for (size_t i = 0; i < values.size(); ++i)
    {
        res += values[i] * values[i];
    }
    return res;
}


inline std::vector<float> randomVector(const std::vector<std::pair<float, float>>& searchSpace)
{
    std::vector<float> res;
    for (size_t i = 0; i < searchSpace.size(); ++i)
    {
        float left = searchSpace[i].first;
        float right = searchSpace[i].second;
        float v = left + (right - left) * ((float)rand() / RAND_MAX);
        res.push_back(v);
    }
    return res;
}

} /* anonymous namespace */


RandomSearch::Candidate RandomSearch::search(const std::vector<std::pair<float, float>>& searchSpace, const int kIterLimit)
{
    srand((unsigned)time(0));
    RandomSearch::Candidate best;
    for (int i = 0; i < kIterLimit; ++i)
    {
        RandomSearch::Candidate candidate;
        candidate.values = randomVector(searchSpace);
        candidate.cost = objectiveFunction(candidate.values);
        if (!i || candidate.cost < best.cost)
        {
            best.cost = candidate.cost;
            best.values.swap(candidate.values);
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
