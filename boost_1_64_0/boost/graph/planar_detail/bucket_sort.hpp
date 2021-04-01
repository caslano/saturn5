//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __BUCKET_SORT_HPP__
#define __BUCKET_SORT_HPP__

#include <vector>
#include <algorithm>
#include <boost/property_map/property_map.hpp>

namespace boost
{

template < typename ItemToRankMap > struct rank_comparison
{
    rank_comparison(ItemToRankMap arg_itrm) : itrm(arg_itrm) {}

    template < typename Item > bool operator()(Item x, Item y) const
    {
        return get(itrm, x) < get(itrm, y);
    }

private:
    ItemToRankMap itrm;
};

template < typename TupleType, int N,
    typename PropertyMapWrapper = identity_property_map >
struct property_map_tuple_adaptor
: public put_get_helper< typename PropertyMapWrapper::value_type,
      property_map_tuple_adaptor< TupleType, N, PropertyMapWrapper > >
{
    typedef typename PropertyMapWrapper::reference reference;
    typedef typename PropertyMapWrapper::value_type value_type;
    typedef TupleType key_type;
    typedef readable_property_map_tag category;

    property_map_tuple_adaptor() {}

    property_map_tuple_adaptor(PropertyMapWrapper wrapper_map)
    : m_wrapper_map(wrapper_map)
    {
    }

    inline value_type operator[](const key_type& x) const
    {
        return get(m_wrapper_map, get< n >(x));
    }

    static const int n = N;
    PropertyMapWrapper m_wrapper_map;
};

// This function sorts a sequence of n items by their ranks in linear time,
// given that all ranks are in the range [0, range). This sort is stable.
template < typename ForwardIterator, typename ItemToRankMap, typename SizeType >
void bucket_sort(ForwardIterator begin, ForwardIterator end, ItemToRankMap rank,
    SizeType range = 0)
{
#ifdef BOOST_GRAPH_PREFER_STD_LIB
    std::stable_sort(begin, end, rank_comparison< ItemToRankMap >(rank));
#else
    typedef std::vector<
        typename boost::property_traits< ItemToRankMap >::key_type >
        vector_of_values_t;
    typedef std::vector< vector_of_values_t > vector_of_vectors_t;

    if (!range)
    {
        rank_comparison< ItemToRankMap > cmp(rank);
        ForwardIterator max_by_rank = std::max_element(begin, end, cmp);
        if (max_by_rank == end)
            return;
        range = get(rank, *max_by_rank) + 1;
    }

    vector_of_vectors_t temp_values(range);

    for (ForwardIterator itr = begin; itr != end; ++itr)
    {
        temp_values[get(rank, *itr)].push_back(*itr);
    }

    ForwardIterator orig_seq_itr = begin;
    typename vector_of_vectors_t::iterator itr_end = temp_values.end();
    for (typename vector_of_vectors_t::iterator itr = temp_values.begin();
         itr != itr_end; ++itr)
    {
        typename vector_of_values_t::iterator jtr_end = itr->end();
        for (typename vector_of_values_t::iterator jtr = itr->begin();
             jtr != jtr_end; ++jtr)
        {
            *orig_seq_itr = *jtr;
            ++orig_seq_itr;
        }
    }
#endif
}

template < typename ForwardIterator, typename ItemToRankMap >
void bucket_sort(ForwardIterator begin, ForwardIterator end, ItemToRankMap rank)
{
    bucket_sort(begin, end, rank, 0);
}

template < typename ForwardIterator >
void bucket_sort(ForwardIterator begin, ForwardIterator end)
{
    bucket_sort(begin, end, identity_property_map());
}

} // namespace boost

#endif //__BUCKET_SORT_HPP__

/* bucket_sort.hpp
zZ35TimLiZRXQyWu8dYGvcqfmGzZfr9KizONz7WyG4dCmg8lFId09BD6jCZ7FI5NtsRLP3vCo//yT2QgP8StbmXIhV3GKfEXglxYJ95bVVcuwFAmZgHHuSFJYIm0cAI3aRRwIkt6N6C188jOusEUhzKY9zz01EZU5TybyYAsf3kUV+aV+G3D7PJXLcXZLkzqOc+N3ZGwGUDAog9M7/MeQfepsNHDdSi5ztQPQ0a7uNNDarYuQPbMsYtsK6jmEKGIL4Ws6H0xL9q4LoERdR6Raa4xXEy+VMsFlvJ0UD2sQCYGHF0zrGhOZ3CVPG/xEeATsr7Hegu19kbjTA1ILAnqKDiswxGBexkfwhdHs+dc69QdzozEbvY6Y0d3ptQIB73sqsdg5sqRwxleAZUjkzuhHGr3pye4LHualmxtftPKBSp4h9QnarHW+tizpCK2H4oQzkDRLj6XQc7YYPGZiLhb6bSMA1I29ggJ8OJnojYyUgGyRJLS6MhMGD1Fxxx8zELjE6a2rn39ftqj0L3K6MFMEUCJmh1r9udKL2wd2aQBAM0fpqAB707O4r62Og==
*/