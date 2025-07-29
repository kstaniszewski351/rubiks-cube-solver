#pragma once
#include <vector>
#include <ranges>

class MultiIndex
{
public:
    MultiIndex(std::vector<int> max_indexes);

    template<typename Iterator>
    int fromRaw(Iterator begin) const
    {
        int multi_index = 0;

        for(int max_index : max_indexes_)
        {
            multi_index *= max_index;
            multi_index += *begin;
            
            ++begin;
        }
        return multi_index;
    }

    template<typename Iterator>
    void toRaw(int multi_index, Iterator end) const
    {
        --end;

        for(int max_index : std::ranges::reverse_view(max_indexes_))
        {
            const int raw_index = multi_index % max_index;
            multi_index /= max_index;

            *end = raw_index;
            --end;
        }
    }

    int getMaxIndex() const;

private:
    const std::vector<int> max_indexes_;
    const int max_index_;
};