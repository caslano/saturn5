// Boost.Geometry Index
//
// n-dimensional bounds
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP

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
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& )
    {
        geometry::expand(b, g, typename Strategy::expand_point_strategy_type());
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
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& )
    {
        geometry::expand(b, g, typename Strategy::expand_box_strategy_type());
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
        index::detail::bounded_view<Geometry, Bounds, Strategy> v(g, s);
        geometry::expand(b, v, typename Strategy::expand_box_strategy_type());
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
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const&)
    {
        return geometry::covered_by(g, b, typename Strategy::covered_by_point_box_strategy_type());
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
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const&)
    {
        return geometry::covered_by(g, b, typename Strategy::covered_by_box_box_strategy_type());
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

        return geometry::covered_by(view_type(g, strategy), b,
                                    typename Strategy::covered_by_box_box_strategy_type());
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