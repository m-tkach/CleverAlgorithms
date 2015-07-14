/*
 * Filename: GuidedLocalSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <set>

#include "GuidedLocalSearch.h"


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


inline std::vector<int> stochasticTwoOpt(const std::vector<int>& permutation)
{
    assert(permutation.size() >= 4);

    std::set<size_t> exclude;
    size_t c1 = rand() % permutation.size(), c2 = 0;

    exclude.insert(c1);
    exclude.insert((c1 ? c1 : permutation.size()) - 1);
    exclude.insert((c1 + 1) % permutation.size());

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


inline std::pair<float, float> augmentedCost(const std::vector<std::pair<float, float>>& cities,
                                             const std::vector<int>& permutation,
                                             const std::vector<std::vector<float>>& penalties,
                                             const float kLambda)
{
    assert(cities.size() == permutation.size());
    assert(cities.size() == penalties.size());

    float distance = 0.0f;
    float augmented = 0.0f;
    for (size_t i = 0; i < permutation.size(); ++i)
    {
        int c1 = permutation[i];
        int c2 = (i + 1 < permutation.size()) ? permutation[i + 1] : permutation[0];
        if (c2 < c1)
        {
            std::swap(c1, c2);
        }
        float d = euc2d(cities[c1], cities[c2]);
        distance += d;
        augmented += d * (kLambda * penalties[c1][c2]);
    }
    return {distance, augmented};
}


inline void updateCost(GuidedLocalSearch::Candidate& current,
                       const std::vector<std::pair<float, float>>& cities,
                       const std::vector<std::vector<float>>& penalties,
                       const float kLambda)
{
    std::pair<float, float> costs = augmentedCost(cities, current.permutation, penalties, kLambda);
    current.ordinaryCost = costs.first;
    current.augmentedCost = costs.second;
}


inline void localSearch(GuidedLocalSearch::Candidate& current,
                        const std::vector<std::pair<float, float>>& cities,
                        const std::vector<std::vector<float>>& penalties,
                        const int kNoImproveLimit,
                        const float kLambda)
{
    updateCost(current, cities, penalties, kLambda);
    int count = 0;
    while (count < kNoImproveLimit)
    {
        GuidedLocalSearch::Candidate candidate;
        candidate.permutation = stochasticTwoOpt(current.permutation);
        updateCost(candidate, cities, penalties, kLambda);
        if (candidate.augmentedCost < current.augmentedCost)
        {
            current.permutation.swap(candidate.permutation);
            current.ordinaryCost = candidate.ordinaryCost;
            current.augmentedCost = candidate.augmentedCost;
            count = 0;
        }
        else
        {
            ++count;
        }
    }
}


inline std::vector<float> calcualateFeaturesUtilities(const std::vector<std::pair<float, float>>& cities,
                                                      const std::vector<int>& permutation,
                                                      const std::vector<std::vector<float>>& penalties)
{
    assert(cities.size() == permutation.size());
    assert(cities.size() == penalties.size());

    std::vector<float> utilities(cities.size(), 0.0f);
    for (size_t i = 0; i < permutation.size(); ++i)
    {
        int c1 = permutation[i];
        int c2 = (i + 1 < permutation.size()) ? permutation[i + 1] : 0;
        if (c2 < c1)
        {
            std::swap(c1, c2);
        }
        utilities[i] = euc2d(cities[c1], cities[c2]) / (1.0f + penalties[c1][c2]);
    }
    return utilities;
}


inline void updatePenalties(std::vector<std::vector<float>>& penalties,
                            const std::vector<std::pair<float, float>>& cities,
                            const std::vector<int>& permutation,
                            const std::vector<float>& utilities)
{
    float maxUtility = *std::max_element(utilities.begin(), utilities.end());
    for (size_t i = 0; i < permutation.size(); ++i)
    {
        int c1 = permutation[i];
        int c2 = (i + 1 < permutation.size()) ? permutation[i + 1] : 0;
        if (c2 < c1)
        {
            std::swap(c1, c2);
        }
        if (std::fabs(utilities[i] - maxUtility) <= std::numeric_limits<float>::epsilon())
        {
            penalties[c1][c2] += 1.0f;
        }
    }
}

} /* anonymous namespace */


GuidedLocalSearch::Candidate GuidedLocalSearch::search(const std::vector<std::pair<float, float>>& cities,
                                                       const int kIterLimit,
                                                       const int kNoImproveLimit,
                                                       const float kLambda)
{
    srand(static_cast<unsigned>(time(nullptr)));

    std::vector<std::vector<float>> penalties(cities.size(), std::vector<float>(cities.size(), 0.0f));
    GuidedLocalSearch::Candidate current, best;
    current.permutation = randomPermutation(cities);
    for (int iter = 0; iter < kIterLimit; ++iter)
    {
        localSearch(current, cities, penalties, kNoImproveLimit, kLambda);
        std::vector<float> utilities = calcualateFeaturesUtilities(cities, current.permutation, penalties);
        updatePenalties(penalties, cities, current.permutation, utilities);
        if (!iter || current.ordinaryCost < best.ordinaryCost)
        {
            best.permutation = current.permutation;
            best.ordinaryCost = current.ordinaryCost;
            best.augmentedCost = current.augmentedCost;
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
