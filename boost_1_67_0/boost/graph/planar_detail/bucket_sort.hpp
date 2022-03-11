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