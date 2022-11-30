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
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
*/