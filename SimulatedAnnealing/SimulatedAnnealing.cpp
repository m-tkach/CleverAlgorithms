/*
 * Filename: SimulatedAnnealing.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <ctime>
#include <set>

#include "SimulatedAnnealing.h"


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


inline SimulatedAnnealing::Candidate createNeighbor(const SimulatedAnnealing::Candidate& current, const std::vector<std::pair<float, float>>& cities)
{
    SimulatedAnnealing::Candidate candidate;
    candidate.permutation = current.permutation;
    stochasticTwoOpt(candidate.permutation);
    candidate.cost = cost(cities, candidate.permutation);
    return candidate;
}


inline bool shouldAccept(const SimulatedAnnealing::Candidate& candidate, const SimulatedAnnealing::Candidate& current, const float kTemperature)
{
    if (candidate.cost < current.cost)
    {
        return true;
    }
    const float randomValue = static_cast<float>(rand()) / RAND_MAX;
    return std::exp((current.cost - candidate.cost) / kTemperature) > randomValue;
}

} /* anonymous namespace */


SimulatedAnnealing::Candidate SimulatedAnnealing::search(const std::vector<std::pair<float, float>>& cities,
                                                         const int kIterLimit,
                                                         const float kMaxTemperature,
                                                         const float kTemperatureChange)
{
    srand(static_cast<unsigned>(time(nullptr)));

    SimulatedAnnealing::Candidate current;
    current.permutation = randomPermutation(cities);
    current.cost = cost(cities, current.permutation);

    SimulatedAnnealing::Candidate best = current;
    float temperature = kMaxTemperature;
    for (int iter = 0; iter <= kIterLimit; ++iter)
    {
        SimulatedAnnealing::Candidate candidate = createNeighbor(current, cities);
        temperature *= kTemperatureChange;
        if (shouldAccept(candidate, current, temperature))
        {
            current = candidate;
        }
        if (candidate.cost < best.cost)
        {
            best.permutation.swap(candidate.permutation);
            best.cost = candidate.cost;
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
