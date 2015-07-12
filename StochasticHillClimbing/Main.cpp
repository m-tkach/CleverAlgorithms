/*
 * Filename: Main.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <iostream>
#include <vector>

#include "StochasticHillClimbing.h"


namespace
{

inline void printResult(const CleverAlgorithms::StochasticHillClimbing::Candidate& result)
{
    std::cout << "Best cost: " << result.cost << "\n";
    std::cout << "Values: ";
    for (size_t i = 0; i < result.values.size(); ++i)
    {
        std::cout << result.values[i];
    }
    std::cout << "\n";
}

} /* anonymous namespace */


int main()
{
    const int kBitsCount = 64;
    const int kIterLimit = 192;
    CleverAlgorithms::StochasticHillClimbing::Candidate result = CleverAlgorithms::StochasticHillClimbing::search(kIterLimit, kBitsCount);
    printResult(result);
    return 0;
}
