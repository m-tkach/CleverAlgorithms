/*
 * Filename: AdaptiveRandomSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef ADAPTIVERANDOMSEARCH_H_0A627B1E_280C_11E5_85AF_C038963D1C06
#define ADAPTIVERANDOMSEARCH_H_0A627B1E_280C_11E5_85AF_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class AdaptiveRandomSearch
{
public:

    struct Candidate
    {
        std::vector<float> values;
        float cost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& bounds,
                            const int kIterLimit,
                            const float kInitFactor,
                            const float kSmallFactor,
                            const float kLargeFactor,
                            const int kIterMult,
                            const int kNoImproveLimit);
};

} /* namespace CleverAlgorithms */

#endif /* ADAPTIVERANDOMSEARCH_H_0A627B1E_280C_11E5_85AF_C038963D1C06 */
