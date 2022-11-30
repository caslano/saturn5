// Boost.Geometry Index
//
// n-dimensional bounds
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/covered_by/interface.hpp>
#include <boost/geometry/algorithms/detail/envelope/interface.hpp>
#include <boost/geometry/algorithms/detail/expand/interface.hpp>

#include <boost/geometry/index/detail/bounded_view.hpp>

namespace boost { namespace geometry { namespace index { namespace detail
{

namespace dispatch
{

template <typename Geometry,
          typename Bounds,
          typename TagGeometry = typename geometry::tag<Geometry>::type,
          typename TagBounds = typename geometry::tag<Bounds>::type>
struct bounds
{
    template <typename Strategy>
    static inline void apply(Geometry const& g, Bounds & b, Strategy const& )
    {
        geometry::convert(g, b);
    }
};

template <typename Geometry, typename Bounds>
struct bounds<Geometry, Bounds, segment_tag, box_tag>
{
    template <typename Strategy>
    static inline void apply(Geometry const& g, Bounds & b, Strategy const& s)
    {
        index::detail::bounded_view<Geometry, Bounds, Strategy> v(g, s);
        geometry::convert(v, b);
    }
};


} // namespace dispatch


template <typename Geometry, typename Bounds, typename Strategy>
inline void bounds(Geometry const& g, Bounds & b, Strategy const& s)
{
    concepts::check_concepts_and_equal_dimensions<Geometry const, Bounds>();
    dispatch::bounds<Geometry, Bounds>::apply(g, b, s);
}


namespace dispatch
{

template <typename Bounds,
          typename Geometry,
          typename TagBounds = typename geometry::tag<Bounds>::type,
          typename TagGeometry = typename geometry::tag<Geometry>::type>
struct expand
{
    // STATIC ASSERT
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, point_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& s)
    {
        geometry::expand(b, g, s);
    }
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, box_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& s)
    {
        geometry::expand(b, g, s);
    }
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, segment_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& s)
    {
        geometry::expand(b, geometry::return_envelope<Bounds>(g, s), s);
        // requires additional strategy
        //geometry::expand(b, g, s);
    }
};


} // namespace dispatch


template <typename Bounds, typename Geometry, typename Strategy>
inline void expand(Bounds & b, Geometry const& g, Strategy const& s)
{
    dispatch::expand<Bounds, Geometry>::apply(b, g, s);
}

template <typename Bounds, typename Geometry>
inline void expand(Bounds & b, Geometry const& g, default_strategy const& )
{
    dispatch::expand<Bounds, Geometry>::apply(b, g);
}


namespace dispatch
{


template <typename Geometry,
          typename Bounds,
          typename TagGeometry = typename geometry::tag<Geometry>::type,
          typename TagBounds = typename geometry::tag<Bounds>::type>
struct covered_by_bounds
{};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, point_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        return geometry::covered_by(g, b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const& s)
    {
        return geometry::covered_by(g, b, s);
    }
};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, box_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        return geometry::covered_by(g, b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const& s)
    {
        return geometry::covered_by(g, b, s);
    }
};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, segment_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        typedef typename point_type<Geometry>::type point_type;
        typedef geometry::model::box<point_type> bounds_type;
        typedef index::detail::bounded_view<Geometry, bounds_type, default_strategy> view_type;

        return geometry::covered_by(view_type(g, default_strategy()), b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const& strategy)
    {
        typedef typename point_type<Geometry>::type point_type;
        typedef geometry::model::box<point_type> bounds_type;
        typedef index::detail::bounded_view<Geometry, bounds_type, Strategy> view_type;

        return geometry::covered_by(view_type(g, strategy), b, strategy);
    }
};


} // namespace dispatch


template <typename Geometry, typename Bounds, typename Strategy>
inline bool covered_by_bounds(Geometry const& g, Bounds & b, Strategy const& s)
{
    return dispatch::covered_by_bounds<Geometry, Bounds>::apply(g, b, s);
}

template <typename Geometry, typename Bounds>
inline bool covered_by_bounds(Geometry const& g, Bounds & b, default_strategy const& )
{
    return dispatch::covered_by_bounds<Geometry, Bounds>::apply(g, b);
}


}}}} // namespace boost::geometry::index::detail


#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP

/* bounds.hpp
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
*/