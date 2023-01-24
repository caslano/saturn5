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
ojphhvyng8yXySRN+6rFppQtquzG8vyqrC1VKD895bMK7cfQfjEacencorVM3MA8Hy8XRfdt1TQxCWuV+5TyHJrnjf5+AbRX85TRhdFYzTZsLdVn+5k7FZP4doXTVHSM7HymN4g1enZGt78KNyi7nMorp3ZrZpsTObv9gs7QzjJzfNpnA3cwO7+kTmM+H1rcul2SRy/Nnt2/XmguprF+lKAd6pFKvrOaTzL9PA+b89u+AR8fU/zXzfiWrCn8pff/kIgj03u9h8nTLPpEPdLjaOY+yllrXXTmmvJG21lldawrji/r0Nlb5p5LLan0nu0rc8/U/vzS+/bbMvfN3UOOuGrmBii91x+UudeUqyBnZCsovZd/U+ZeqlV+PY+Ze9LLvdZvM9NDLpDrofR++y7f6o+7V8Wnf8TllPCvtOBn3LPis/zS551oySRB6pmKN8CYm82MsjPqmSqywvFvyzz/4fyjbqaM0rGg3BIs1Hs7l8fC4C9jnwR1Pff0dOIGjJ1VUBxMEseBDRYIhGAhOAQP7rZY0KAhuLvroou7QwgEh4WwuAeHICGLu7t8uC2Ly2IndVV3D1dXN1PzMD2/mu6ep/73yyDxbMX/8Mn1UZB0vCVCZlW4+X/IO8SKF62QO7djhaDaFRaNaJZ2CTGlFs6cVHRwfHNqWosv0vSUS31l8vzhNWfzOAXbnMWOQVzjVhKbj9bviuNrKfkfO2V9
*/