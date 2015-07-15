/*
 * Filename: Main.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <iostream>

#include "VariableNeighborhoodSearch.h"


namespace
{

inline void printResult(const std::vector<std::pair<float, float>>& cities,
                        const CleverAlgorithms::VariableNeighborhoodSearch::Candidate& result)
{
    assert(cities.size() == result.permutation.size());

    std::cout << "Best cost: " << result.cost << "\n";
    std::cout << "\nValues:\n";
    for (size_t i = 0; i < result.permutation.size(); ++i)
    {
        int j = result.permutation[i];
        std::cout << "(" << cities[j].first << " " << cities[j].second << ") ";
        if (i % 5 == 4)
        {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

} /* anonymous namespace */


int main()
{
    std::vector<std::pair<float, float>> berlin52 = { std::make_pair(565.0f, 575.0f), std::make_pair(25.0f, 185.0f),
        std::make_pair(345.0f, 750.0f), std::make_pair(945.0f, 685.0f), std::make_pair(845.0f, 655.0f), std::make_pair(880.0f, 660.0f),
        std::make_pair(25.0f, 230.0f), std::make_pair(525.0f, 1000.0f), std::make_pair(580.0f, 1175.0f), std::make_pair(650.0f, 1130.0f),
        std::make_pair(1605.0f, 620.0f), std::make_pair(1220.0f, 580.0f), std::make_pair(1465.0f, 200.0f), std::make_pair(1530.0f, 5.0f),
        std::make_pair(845.0f, 680.0f), std::make_pair(725.0f, 370.0f), std::make_pair(145.0f, 665.0f), std::make_pair(415.0f, 635.0f),
        std::make_pair(510.0f, 875.0f), std::make_pair(560.0f, 365.0f), std::make_pair(300.0f, 465.0f), std::make_pair(520.0f, 585.0f),
        std::make_pair(480.0f, 415.0f), std::make_pair(835.0f, 625.0f), std::make_pair(975.0f, 580.0f), std::make_pair(1215.0f, 245.0f),
        std::make_pair(1320.0f, 315.0f), std::make_pair(1250.0f, 400.0f), std::make_pair(660.0f, 180.0f), std::make_pair(410.0f, 250.0f),
        std::make_pair(420.0f, 555.0f), std::make_pair(575.0f, 665.0f), std::make_pair(1150.0f, 1160.0f), std::make_pair(700.0f, 580.0f),
        std::make_pair(685.0f, 595.0f), std::make_pair(685.0f, 610.0f), std::make_pair(770.0f, 610.0f), std::make_pair(795.0f, 645.0f),
        std::make_pair(720.0f, 635.0f), std::make_pair(760.0f, 650.0f), std::make_pair(475.0f, 960.0f), std::make_pair(95.0f, 260.0f),
        std::make_pair(875.0f, 920.0f), std::make_pair(700.0f, 500.0f), std::make_pair(555.0f, 815.0f), std::make_pair(830.0f, 485.0f),
        std::make_pair(1170.0f, 65.0f), std::make_pair(830.0f, 610.0f), std::make_pair(605.0f, 625.0f), std::make_pair(595.0f, 360.0f),
        std::make_pair(1340.0f, 725.0f), std::make_pair(1740.0f, 245.0f) };
    const int kNoImproveLimit = 250;
    const int kLocalSearchNoImproveLimit = 370;
    std::vector<int> neighborhoods(30);
    std::iota(neighborhoods.begin(), neighborhoods.end(), 1);

    CleverAlgorithms::VariableNeighborhoodSearch::Candidate result = CleverAlgorithms::VariableNeighborhoodSearch::search(berlin52,
                                                                                                                          neighborhoods,
                                                                                                                          kNoImproveLimit,
                                                                                                                          kLocalSearchNoImproveLimit);
    printResult(berlin52, result);
    return 0;
}
