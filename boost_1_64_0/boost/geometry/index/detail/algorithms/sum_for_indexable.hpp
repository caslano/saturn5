// Boost.Geometry Index
//
// Sum values calculated for indexable's dimensions, used e.g. in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct sum_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (sum_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct sum_for_indexable
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i) +
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i);
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct sum_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

/* sum_for_indexable.hpp
AQf5Dlt9Q05Znvk05PYbJDB1b3gfwD8JO3UNPHicY/JmRNNM+MIXJbHFY/oYVUzGI2LjL//zwYLn3RwRmPmtdivh6/kFgzD5XkiPeXJdgouGX16axcTwWSYoWsfWR5wa1Jonr7pY72O1xIemJTcDLi+dhCVPOhDVLvB3qlsBdWdHst8Ik5IoGUCkcKFdJMdobWPNSPXjtxxnUKHA2nWG+Ju/n4TjJKIyoCnWsepFa8ySp9OLzUGuiL7RXC1WnKCTQqzDRIXQeRvDFswJb1SgC67J3jL1yhFBYGM85nwITYoJ4IP88AeRIwgv6+eJJFRce+1wQcj4hLLoImhQVhKE/C6EHHpHouSZS8xeDYXE4mr33w3RhRp/S6hIYQlDOAC5Ai1NgWPtiOEEcpsiyogR/3WYJl7byvSIaO9qBKp1Blslbtg8vR/ZJQ2ontXmJ4JOe1nuOHm2Ujo2baQfRPhQblNvnWIpZhaQJcYVmzxE/Xzt996ghWDRWAJydY8vLq1L7FUilbt2cqXYUmBElerON2W+cMMhitaES1W27Ax+9vqmN6K0jttzvUAdsw==
*/