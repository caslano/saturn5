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
3mJ1HPvrHGUf3VobzmdKo1X670Fotnth+d6suzC5j0akRvPsaKfY0JE261hbYeZy//XKNGJthVkLextVcBVzXrFLf77V/7ZMsft7Gl1hXsO8hEUMCH7DPIPJmJXptPQhc0mxU2VGHGG+KPOzmF+Isb4IcxR2Mbjahny7BzMVtvTW77e5tsq43yP/0vslmIuwGpeb69+thZ3oJMxkli/fu/nC7IQVaviU6xcB8xBW3W4A41ID
*/