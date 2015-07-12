/*
 * Filename: Main.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <iomanip>
#include <iostream>
#include <vector>

#include "AdaptiveRandomSearch.h"


namespace
{

inline void printResult(const CleverAlgorithms::AdaptiveRandomSearch::Candidate& result)
{
    std::cout << "Best cost: " << std::fixed << std::setprecision(8) << result.cost << "\n";
    std::cout << "Values:";
    for (size_t i = 0; i < result.values.size(); ++i)
    {
        std::cout << " " << std::fixed << std::setprecision(8) << result.values[i];
    }
    std::cout << "\n";
}

} /* anonymous namespace */


int main()
{
    const int kProblemSize = 2;
    std::vector<std::pair<float, float>> bounds(kProblemSize, {-5.0f, 5.0f});

    const int kIterLimit = 1000;
    const float kInitFactor = 0.05f;
    const float kSmallFactor = 1.3f;
    const float kLargeFactor = 3.0f;
    const int kIterMult = 10;
    const int kNoImproveLimit = 30;

    CleverAlgorithms::AdaptiveRandomSearch::Candidate result = CleverAlgorithms::AdaptiveRandomSearch::search(bounds,
                                                                                                              kIterLimit,
                                                                                                              kInitFactor,
                                                                                                              kSmallFactor,
                                                                                                              kLargeFactor,
                                                                                                              kIterMult,
                                                                                                              kNoImproveLimit);
    printResult(result);
    return 0;
}
