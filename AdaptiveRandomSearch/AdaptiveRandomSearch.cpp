/*
 * Filename: AdaptiveRandomSearch.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "AdaptiveRandomSearch.h"


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


inline float random(float left, float right)
{
    assert(left <= right);
    return left + (right - left) * (static_cast<float>(rand()) / RAND_MAX);
}


inline std::vector<float> randomVector(const std::vector<std::pair<float, float>>& bounds)
{
    std::vector<float> res(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i)
    {
        res[i] = random(bounds[i].first, bounds[i].second);
    }
    return res;
}


inline float largeStepSize(const int kIter, const float kStepSize, const float kSmallFactor, const float kLargeFactor, const int kIterMult)
{
    assert(kIterMult != 0);

    if (kIter > 0 && kIter % kIterMult == 0)
    {
        return kStepSize * kLargeFactor;
    }
    return kStepSize * kSmallFactor;
}


inline std::vector<float> takeStep(const std::vector<std::pair<float, float>>& bounds,
                                   const AdaptiveRandomSearch::Candidate& current,
                                   const float kStepSize)
{
    std::vector<float> position(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i)
    {
        float left = std::max(bounds[i].first, current.values[i] - kStepSize);
        float right = std::min(bounds[i].second, current.values[i] + kStepSize);
        position[i] = random(left, right);
    }
    return position;
}


inline std::pair<AdaptiveRandomSearch::Candidate, AdaptiveRandomSearch::Candidate> takeSteps(const std::vector<std::pair<float, float>>& bounds,
                                                                                             const AdaptiveRandomSearch::Candidate& current,
                                                                                             const float kStepSize,
                                                                                             const float kBigStepSize)
{
    AdaptiveRandomSearch::Candidate ordinaryStep, bigStep;
    ordinaryStep.values = takeStep(bounds, current, kStepSize);
    ordinaryStep.cost = objectiveFunction(ordinaryStep.values);
    bigStep.values = takeStep(bounds, current, kBigStepSize);
    bigStep.cost = objectiveFunction(bigStep.values);
    return {ordinaryStep, bigStep};
}

} // anonymous namespace


AdaptiveRandomSearch::Candidate AdaptiveRandomSearch::search(const std::vector<std::pair<float, float>>& bounds,
                                                             const int kIterLimit, const float kInitFactor,
                                                             const float kSmallFactor, const float kLargeFactor,
                                                             const int kIterMult, const int kNoImproveLimit)
{
    assert(!bounds.empty());

    srand(static_cast<unsigned>(time(nullptr)));

    AdaptiveRandomSearch::Candidate best;
    best.values = randomVector(bounds);
    best.cost = objectiveFunction(best.values);
    int count = 0;
    float stepSize = (bounds.front().second - bounds.front().first) * kInitFactor;
    for (int iter = 0; iter < kIterLimit; ++iter)
    {
        float bigStepSize = largeStepSize(iter, stepSize, kSmallFactor, kLargeFactor, kIterMult);
        std::pair<AdaptiveRandomSearch::Candidate, AdaptiveRandomSearch::Candidate> steps = takeSteps(bounds, best, stepSize, bigStepSize);
        AdaptiveRandomSearch::Candidate& ordinaryStep = steps.first;
        AdaptiveRandomSearch::Candidate& bigStep = steps.second;
        if (ordinaryStep.cost <= best.cost || bigStep.cost <= best.cost)
        {
            if (bigStep.cost <= ordinaryStep.cost)
            {
                stepSize = bigStepSize;
                best = bigStep;
            }
            else
            {
                best = ordinaryStep;
            }
            count = 0;
        }
        else
        {
            ++count;
            if (count >= kNoImproveLimit)
            {
                count = 0;
                stepSize /= kSmallFactor;
            }
        }
    }
    return best;
}

} /* namespace CleverAlgorithms */
