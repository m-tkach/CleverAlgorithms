/*
 * Filename: IteratedLocalSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <set>

#include "IteratedLocalSearch.h"


namespace CleverAlgorithms
{

namespace
{

inline std::vector<int> randomPermutation(const std::vector<std::pair<float, float>>& cities)
{
    std::vector<int> res(cities.size());
    std::iota(res.begin(), res.end(), 0);
    for (size_t i = 0; i < res.size(); ++i)
    {
        int r = rand() % (res.size() - i) + i;
        std::swap(res[i], res[r]);
    }
    return res;
}


inline float euc2d(const std::pair<float, float>& a, const std::pair<float, float>& b)
{
    float dx = a.first - b.first;
    float dy = a.second - b.second;
    return std::sqrt(dx * dx + dy * dy);
}


inline float cost(const std::vector<std::pair<float, float>>& cities, const std::vector<int>& permutation)
{
    assert(cities.size() == permutation.size());

    float res = 0.0f;
    for (size_t i = 0; i < permutation.size(); ++i)
    {
        size_t j = i + 1;
        if (j == permutation.size()) j = 0;

        res += euc2d(cities[permutation[i]], cities[permutation[j]]);
    }
    return res;
}


inline std::vector<int> stochasticTwoOpt(const std::vector<int>& permutation)
{
    assert(permutation.size() >= 4);

    std::set<size_t> exclude;
    size_t c1 = 0, c2 = 0;
    c1 = rand() % permutation.size();
    exclude.insert(c1);
    exclude.insert((c1 ? c1 : permutation.size()) - 1);
    exclude.insert((c1 + 1 == permutation.size()) ? 0 : c1 + 1);

    do
    {
        c2 = rand() % permutation.size();
    }
    while (exclude.count(c2));

    if (c1 > c2)
    {
        std::swap(c1, c2);
    }

    std::vector<int> res(permutation);
    std::reverse(res.begin() + c1, res.begin() + c2);
    return res;
}


inline void localSearch(IteratedLocalSearch::Candidate& current,
                        const std::vector<std::pair<float, float>>& cities,
                        const int kNoImproveLimit)
{
    int count = 0;
    while (count < kNoImproveLimit)
    {
        IteratedLocalSearch::Candidate candidate;
        candidate.permutation = stochasticTwoOpt(current.permutation);
        candidate.cost = cost(cities, candidate.permutation);
        if (candidate.cost < current.cost)
        {
            count = 0;
            current.permutation.swap(candidate.permutation);
            current.cost = candidate.cost;
        }
        else
        {
            ++count;
        }
    }
}


inline std::vector<int> doubleBridgeMove(const std::vector<int>& permutation)
{
    assert(permutation.size() >= 4);

    const size_t kRandMod = permutation.size() / 4;
    size_t pos0 = 0;
    size_t pos1 = 1 + rand() % kRandMod;
    size_t pos2 = pos1 + 1 + rand() % kRandMod;
    size_t pos3 = pos2 + 1 + rand() % kRandMod;
    size_t pos4 = permutation.size();

    std::vector<int> res;
    res.reserve(permutation.size());
    for (size_t i = pos0; i < pos1; ++i) res.push_back(permutation[i]);
    for (size_t i = pos3; i < pos4; ++i) res.push_back(permutation[i]);
    for (size_t i = pos2; i < pos3; ++i) res.push_back(permutation[i]);
    for (size_t i = pos1; i < pos2; ++i) res.push_back(permutation[i]);
    return res;
}


inline IteratedLocalSearch::Candidate perturbation(const std::vector<std::pair<float, float>>& cities,
                                                   const IteratedLocalSearch::Candidate& best)
{
    IteratedLocalSearch::Candidate candidate;
    candidate.permutation = doubleBridgeMove(best.permutation);
    candidate.cost = cost(cities, candidate.permutation);
    return candidate;
}

} /* anonymous namespace */


IteratedLocalSearch::Candidate IteratedLocalSearch::search(const std::vector<std::pair<float, float>>& cities,
                                                           const int kIterLimit,
                                                           const int kNoImproveLimit)
{
    srand(static_cast<unsigned>(time(nullptr)));

    IteratedLocalSearch::Candidate best;
    best.permutation = randomPermutation(cities);
    best.cost = cost(cities, best.permutation);
    localSearch(best, cities, kNoImproveLimit);
    for (int iter = 0; iter < kIterLimit; ++iter)
    {
        IteratedLocalSearch::Candidate candidate = perturbation(cities, best);
        localSearch(candidate, cities, kNoImproveLimit);
        if (candidate.cost < best.cost)
        {
            best.permutation.swap(candidate.permutation);
            best.cost = candidate.cost;
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
