/*
 * Filename: Main.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <iostream>
#include <vector>
#include <utility>

#include "RandomSearch.h"


namespace
{

inline void printResult(const CleverAlgorithms::RandomSearch::Candidate& result)
{
    std::cout << "Best cost: " << result.cost << "\n";
    std::cout << "Values:";
    for (size_t i = 0; i < result.values.size(); ++i)
    {
        std::cout << " " << result.values[i];
    }
    std::cout << "\n";
}

} /* anonymous namespace */


int main()
{
    const int kProblemSize = 2;
    std::vector<std::pair<float, float>> searchSpace(kProblemSize, std::make_pair(-5.0f, 5.0f));
    const int kMaxIter = 1000;

    CleverAlgorithms::RandomSearch::Candidate best = CleverAlgorithms::RandomSearch::search(searchSpace, kMaxIter);
    printResult(best);
}
