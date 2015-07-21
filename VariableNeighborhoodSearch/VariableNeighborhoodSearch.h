/*
 * Filename: VariableNeighborhoodSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef VARIABLENEIGHBORHOODSEARCH_H_02AE2378_2B29_11E5_849E_C038963D1C06
#define VARIABLENEIGHBORHOODSEARCH_H_02AE2378_2B29_11E5_849E_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class VariableNeighborhoodSearch
{
public:

    struct Candidate
    {
        std::vector<int> permutation;
        float cost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& cities,
                            const std::vector<int>& neighborhoods,
                            const int kNoImproveLimit,
                            const int kLsNoImproveLimit);
};

} /* namespace CleverAlgorithms */

#endif /* VARIABLENEIGHBORHOODSEARCH_H_02AE2378_2B29_11E5_849E_C038963D1C06 */
