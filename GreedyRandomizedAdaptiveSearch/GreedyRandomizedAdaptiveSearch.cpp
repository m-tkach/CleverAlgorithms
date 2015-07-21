/*
 * Filename: GreedyRandomizedAdaptiveSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <set>

#include "GreedyRandomizedAdaptiveSearch.h"


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


inline float cost(const std::vector<std::pair<float, float>>& cities,
                  const std::vector<int>& permutation)
{
    assert(permutation.size() == cities.size());

    float distance = 0.0f;
    for (size_t i = 0; i < cities.size(); ++i)
    {
        int c1 = permutation[i];
        int c2 = i + 1 < permutation.size() ? permutation[i + 1] : permutation[0];
        distance += euc2d(cities[c1], cities[c2]);
    }
    return distance;
}


inline std::vector<int> stochasticTwoOpt(const std::vector<int>& permutation)
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

    std::vector<int> res(permutation);
    std::reverse(res.begin() + c1, res.begin() + c2);
    return res;
}


inline void localSearch(GreedyRandomizedAdaptiveSearch::Candidate& current,
                        const std::vector<std::pair<float, float>>& cities,
                        const int kNoImproveLimit)
{
    int count = 0;
    while (count < kNoImproveLimit)
    {
        GreedyRandomizedAdaptiveSearch::Candidate candidate;
        candidate.permutation = stochasticTwoOpt(current.permutation);
        candidate.cost = cost(cities, candidate.permutation);
        if (candidate.cost < current.cost)
        {
            current.permutation.swap(candidate.permutation);
            current.cost = candidate.cost;
            count = 0;
        }
        else
        {
            ++count;
        }
    }
}


inline GreedyRandomizedAdaptiveSearch::Candidate constructRandomizedGreedySolution(const std::vector<std::pair<float, float>>& cities,
                                                                                   const float kAlpha)
{
    assert(!cities.empty());

    GreedyRandomizedAdaptiveSearch::Candidate candidate;
    candidate.permutation.push_back(rand() % cities.size());
    std::vector<char> used(cities.size(), 0);
    used[candidate.permutation.back()] = 1;
    while (candidate.permutation.size() < cities.size())
    {
        std::vector<std::pair<float, size_t>> costs;
        for (size_t i = 0; i < cities.size(); ++i)
        {
            if (!used[i])
            {
                float c = euc2d(cities[candidate.permutation.back()], cities[i]);
                costs.push_back({c, i});
            }
        }

        assert(!costs.empty());

        float minCost = costs.front().first,
              maxCost = costs.front().first;
        for (size_t i = 1; i < costs.size(); ++i)
        {
            if (costs[i].first < minCost)
            {
                minCost = costs[i].first;
            }
            if (costs[i].first > maxCost)
            {
                maxCost = costs[i].first;
            }
        }

        std::vector<size_t> rcl;
        for (size_t i = 0; i < costs.size(); ++i)
        {
            float c = costs[i].first;
            size_t j = costs[i].second;
            if (c <= minCost + kAlpha * (maxCost - minCost))
            {
                rcl.push_back(j);
            }
        }

        assert(!rcl.empty());

        size_t city = rcl[rand() % rcl.size()];
        candidate.permutation.push_back(static_cast<int>(city));
        used[city] = 1;
    }
    candidate.cost = cost(cities, candidate.permutation);
    return candidate;
}

} /* anonymous namespace */


GreedyRandomizedAdaptiveSearch::Candidate GreedyRandomizedAdaptiveSearch::search(const std::vector<std::pair<float, float>>& cities,
                                                                                 const int kIterLimit,
                                                                                 const int kNoImproveLimit,
                                                                                 const float kAlpha)
{
    srand(static_cast<unsigned>(time(nullptr)));

    GreedyRandomizedAdaptiveSearch::Candidate best;
    for (int iter = 0; iter < kIterLimit; ++iter)
    {
        GreedyRandomizedAdaptiveSearch::Candidate candidate = constructRandomizedGreedySolution(cities, kAlpha);
        localSearch(candidate, cities, kNoImproveLimit);
        if (!iter || candidate.cost < best.cost)
        {
            best.permutation.swap(candidate.permutation);
            best.cost = candidate.cost;
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
