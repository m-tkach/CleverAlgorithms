/*
 * Filename: VariableNeighborhoodSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <set>

#include "VariableNeighborhoodSearch.h"


namespace CleverAlgorithms
{

namespace
{

inline float euc2d(const std::pair<float, float>& a, const std::pair<float, float>& b)
{
    float dx = a.first - b.first;
    float dy = a.second - b.second;
    return std::sqrt(dx * dx + dy * dy);
}


inline float cost(const std::vector<std::pair<float, float>>& cities, const std::vector<int>& permutation)
{
    assert(cities.size() == permutation.size());

    float distance = 0.0f;
    for (size_t i = 0; i < permutation.size(); ++i)
    {
        int j = i + 1 == permutation.size() ? 0 : i + 1;
        int c1 = permutation[i],
            c2 = permutation[j];
        distance += euc2d(cities[c1], cities[c2]);
    }
    return distance;
}


inline std::vector<int> randomPermutation(const std::vector<std::pair<float, float>>& cities)
{
    std::vector<int> res(cities.size());
    std::iota(res.begin(), res.end(), 0);
    for (size_t i = 0; i < res.size(); ++i)
    {
        size_t r = rand() % (res.size() - i) + i;
        std::swap(res[i], res[r]);
    }
    return res;
}


inline void stochasticTwoOpt(std::vector<int>& permutation)
{
    assert(permutation.size() >= 4);

    size_t c1 = rand() % permutation.size(),
           c2 = rand() % permutation.size();
    std::set<size_t> exclude;
    exclude.insert(c1);
    exclude.insert(c1 ? c1 - 1 : permutation.size() - 1);
    exclude.insert(c1 + 1 < permutation.size() ? c1 + 1 : 0);
    while (exclude.count(c2))
    {
        c2 = rand() % permutation.size();
    }
    if (c1 > c2)
    {
        std::swap(c1, c2);
    }
    std::reverse(permutation.begin() + c1, permutation.begin() + c2);
}


inline void localSearch(VariableNeighborhoodSearch::Candidate& best,
                        const std::vector<std::pair<float, float>>& cities,
                        const int kNoImproveLimit,
                        const int kNeighborhood)
{
    int count = 0;
    while (count < kNoImproveLimit)
    {
        VariableNeighborhoodSearch::Candidate candidate;
        candidate.permutation = best.permutation;
        for (int i = 0; i < kNeighborhood; ++i)
        {
            stochasticTwoOpt(candidate.permutation);
        }
        candidate.cost = cost(cities, candidate.permutation);
        if (candidate.cost < best.cost)
        {
            best.permutation.swap(candidate.permutation);
            best.cost = candidate.cost;
            count = 0;
        }
        else
        {
            ++count;
        }
    }
}

} /* anonymous namespace */


VariableNeighborhoodSearch::Candidate VariableNeighborhoodSearch::search(const std::vector<std::pair<float, float>>& cities,
                                                                         const std::vector<int> neighborhoods,
                                                                         const int kNoImproveLimit,
                                                                         const int kLsNoImproveLimit)
{
    srand(static_cast<unsigned>(time(nullptr)));

    VariableNeighborhoodSearch::Candidate best;
    best.permutation = randomPermutation(cities);
    best.cost = cost(cities, best.permutation);
    int count = 0;
    while (count < kNoImproveLimit)
    {
        for (size_t i = 0; i < neighborhoods.size(); ++i)
        {
            int neigh = neighborhoods[i];
            VariableNeighborhoodSearch::Candidate candidate;
            candidate.permutation = best.permutation;
            for (int iter = 0; iter < neigh; ++iter)
            {
                stochasticTwoOpt(candidate.permutation);
            }
            candidate.cost = cost(cities, candidate.permutation);
            localSearch(candidate, cities, kLsNoImproveLimit, neigh);
            if (candidate.cost < best.cost)
            {
                best.permutation.swap(candidate.permutation);
                best.cost = candidate.cost;
                count = 0;
                break;
            }
            else
            {
                ++count;
            }
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
