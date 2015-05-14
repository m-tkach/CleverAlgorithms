/*
 * Filename: RandomSearch.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef RANDOMSEARCH_H_39D1B58C_F8D3_11E4_9ED5_C038963D1C06
#define RANDOMSEARCH_H_39D1B58C_F8D3_11E4_9ED5_C038963D1C06

namespace CleverAlgorithms
{

class RandomSearch
{
public:

    struct Candidate
    {
        std::vector<float> values;
        float cost;
    };

    static Candidate search(const std::vector<std::pair<float, float>>& searchSpace, const int kIterLimit);
};

} /* namespace CleverAlgorithms */

#endif /* RANDOMSEARCH_H_39D1B58C_F8D3_11E4_9ED5_C038963D1C06 */
