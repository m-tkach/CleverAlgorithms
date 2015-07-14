/*
 * Filename: GuidedLocalSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef GUIDEDLOCALSEARCH_H_51465370_2A5C_11E5_9C1D_C038963D1C06
#define GUIDEDLOCALSEARCH_H_51465370_2A5C_11E5_9C1D_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class GuidedLocalSearch
{
public:

    struct Candidate
    {
        std::vector<int> permutation;
        float ordinaryCost;
        float augmentedCost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& cities,
                            const int kIterLimit,
                            const int kNoImproveLimit,
                            const float kLambda);
};

} /* namespace CleverAlgorithms */

#endif /* GUIDEDLOCALSEARCH_H_51465370_2A5C_11E5_9C1D_C038963D1C06 */
