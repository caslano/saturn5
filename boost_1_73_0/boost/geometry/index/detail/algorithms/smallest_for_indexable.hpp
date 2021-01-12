// Boost.Geometry Index
//
// Get smallest value calculated for indexable's dimensions, used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct smallest_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (smallest_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct smallest_for_indexable
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        result_type r1 = smallest_for_indexable<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        result_type r2 = smallest_for_indexable_dimension<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        return r1 < r2 ? r1 : r2;
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct smallest_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        return
            smallest_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i, data);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

/* smallest_for_indexable.hpp
yTBLYS2L/tOP7z+Va/ZNi6zEvhxmKmzyxNOTea4ocYnstpxru1CZ+6KrA5YxB5VrzjN7sZq9PsxEWNkDFuxf1ivjcvqtecrcVT7vq027usxdZVz87XbMpT3K533pP4/rd0CxghXPs4YcUa45/oregx1TxrkfN+aZk6XYrMXBfG9zVrGVKWd5LxcVy8r8U3/PrqzDrnlvh+fbLcWq3RrMd82P1Ln/fV3/XXdl3Nk7fdibvlXm
*/