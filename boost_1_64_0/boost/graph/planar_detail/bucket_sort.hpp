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
Y2+TdTLcsf8bSUYJdO4zPKCaNVHmo5F6jvdJ2eZK+tvZRmsxrbeMb3iGo5oRbPubZzDrcj9udSPLL0p+uAvy99N96iyX71iv+0b8Ue1bHn2ByDbQRKY1VL9jY5ekm5g7+MZQM0j3+bBQ8kNUOdNIk3mOMisbY4xvqQW99SvxeW/1rhn1XScl3ZS9rgJ5Ln3DjJqQZrhst7/LuBeoND30y/zE6Xd4VJZt4x7ZjtsWbnfyMjvd15x8/pfdbf179DO7WdbzQcZax+gl00y+Xv/s9+p9Dddk2fWwtiX9Tk3rXUa3pEwnpkf32TeRB+j1chgt0x8q5TuRLiPTV1vGGWmobUr1aSb9neNGWVad6Ue+Fb0Mtad/efoUUPvhvsLlaLbiWf7DxqjC/cDqa0P3W/SzTFcXl2nPSk9VE3+v2sZuSpkX7M8w/teJ2Ta7kU69t4TI9/vWfM5uK7Jdue6TqSMy+dPqA6aEzFtDl/02a+TI8VIt6eWRJOOJ0ftihqzvv41y1B87jQR97Jkq5eKNMKOEquvd8uQ72zG+ivKdVQNUvar7a5f3X5Ky5j9txFD1HHjRficys9j9ZJyDSJWUcdYNsI5pwxo1MKw+cc7JchvqsmwZsVq2UaoeuC1lltpTDDs9Iwz0Ky75zu3ZX3+3vGfPsI7LDWV5jDRKGV3c6ji2KX1MLSVlznJUbq+Oec7t4qrZi9xj1DuNzZWU78b73+SauTxfGxrIrQiq/8N3rD4Spcxlyqx0lAmZMdtZ5j3KWH2uZrv1P9VI6qcQt3GUCub3Ufmex//j+d6/WFWmk7OM3yyDF/nxPr/lvt7np8ebwTCrHMMEz4rU/Td6lMmzytTyVWYnZVbL9M0e6yzzvirzC+lmpNeo/rLX4kvEOod3EeuJDWrYBcTL/L0YF6jY6NIv9yb+3kxscQxDequkGSa80G0E5aT8K/y9nchXw7+qx2O50eXv1+R7dUjeDvKOoQoZn/StbRh36GMjFAqvu7KcpH/tYbLOjSpdu9draqi8PlZeE2deByuvsTOvrpXXyJlXzspr6MwrYeU1cOb9nqTz6jvzvrHy6jnzjlt5dZ15H1t5Cc68fTqvrp6P3Vaeno9tVp6ej6etPD3NE3vqPD3Nz6q8rGy6zcugjyTyqEPd+qc6o/uiUG1z8i6QXhau8iapdyGSR7uTPN3u1P1bxQW491t0U3TkSfvOow803Y7S/UWyb6u+s9X7GHWeri+lP5OfCufbGFOmMG3K/LFvqnRlj/SR3jrt1sfkIPU8/C2inHIIZfL6OfvO5Xg9Ypz0eqL7MNRtON3viSofr/sw3C3pF+nJupruwzDgQTk2WH1R6raAPn9hPFJG98O7S9JfGJlGkD62mi7H1iQ9TCXdF+Jrkv7KmEx7J1i3FbP1Mf8D+fygW30+xaU+3y6ff21kUUK994t/w5lOq4+sbVLmW+O/7F0JeFTVFX4vk4SQTCALDCFsYd+RTTZBIouyKWEpUBCzkEAiIRmSsAliggqIKLhTl4pWcQPFSitWahHRWksroLXUqtWidamtFNHSarX//HPeeUvmQej2td/XfFz+Ofeeu7y7nHvufrl9R269u/WmzbR1dr6ZRnqQ0HZ+9IesS4H7dWn23Zi3iVzYBRP5/T2RSUDYn/6uvUj9Rvis33jFUuqdVZfs8pM7WOQ+HS0Prc/Ib9hb+Q1ereNhxz0tZ35vxpnejxH7HpV///0tse8/8btPxu/+Gf/7W77F+1g+O9Qr8ccT9g65f3Cnia9unfyl370ufveo+N1D4nf/id+9On73xvjdT+J334vf/TBnfn9L7Hta/O7P8bsX6MzvmYl9D4/fPTmnvqdF7kmknlUAvA0=
*/