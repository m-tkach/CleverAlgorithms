/*
 * Filename: IteratedLocalSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef ITERATEDLOCALSEARCH_H_777FF7BE_298D_11E5_9758_C038963D1C06
#define ITERATEDLOCALSEARCH_H_777FF7BE_298D_11E5_9758_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class IteratedLocalSearch
{
public:

    struct Candidate
    {
        std::vector<int> permutation;
        float cost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& cities, const int kIterLimit, const int kNoImproveLimit);
};

} /* namespace CleverAlgorithms */

#endif /* ITERATEDLOCALSEARCH_H_777FF7BE_298D_11E5_9758_C038963D1C06 */
