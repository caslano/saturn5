// Boost.Geometry Index
//
// Sum values calculated for indexable's dimensions, used e.g. in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

#include <boost/geometry/core/static_assert.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct sum_for_indexable_dimension
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable type.",
        Geometry, Indexable, IndexableTag, AlgoTag);
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
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
*/