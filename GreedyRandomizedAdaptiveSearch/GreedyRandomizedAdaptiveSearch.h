/*
 * Filename: GreedyRandomizedAdaptiveSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef GREEDYRANDOMIZEDADAPTIVESEARCH_H_3A2344A8_2FDE_11E5_A4B9_C038963D1C06
#define GREEDYRANDOMIZEDADAPTIVESEARCH_H_3A2344A8_2FDE_11E5_A4B9_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class GreedyRandomizedAdaptiveSearch
{
public:

    struct Candidate
    {
        std::vector<int> permutation;
        float cost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& cities,
                            const int kIterLimit,
                            const int kNoImproveLimit,
                            const float kAlpha);
};

} /* namespace CleverAlgorithms */

#endif /* GREEDYRANDOMIZEDADAPTIVESEARCH_H_3A2344A8_2FDE_11E5_A4B9_C038963D1C06 */
