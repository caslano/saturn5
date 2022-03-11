// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP

#include <cmath>
#include <iterator>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/transform.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace transform
{

struct transform_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline bool apply(Point1 const& p1, Point2& p2,
                Strategy const& strategy)
    {
        return strategy.apply(p1, p2);
    }
};


struct transform_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2& b2,
                Strategy const& strategy)
    {
        typedef typename point_type<Box1>::type point_type1;
        typedef typename point_type<Box2>::type point_type2;

        point_type1 lower_left, upper_right;
        geometry::detail::assign::assign_box_2d_corner<min_corner, min_corner>(
                    b1, lower_left);
        geometry::detail::assign::assign_box_2d_corner<max_corner, max_corner>(
                    b1, upper_right);

        point_type2 p1, p2;
        if (strategy.apply(lower_left, p1) && strategy.apply(upper_right, p2))
        {
            // Create a valid box and therefore swap if necessary
            typedef typename coordinate_type<point_type2>::type coordinate_type;
            coordinate_type x1 = geometry::get<0>(p1)
                    , y1  = geometry::get<1>(p1)
                    , x2  = geometry::get<0>(p2)
                    , y2  = geometry::get<1>(p2);

            if (x1 > x2) { std::swap(x1, x2); }
            if (y1 > y2) { std::swap(y1, y2); }

            geometry::set<min_corner, 0>(b2, x1);
            geometry::set<min_corner, 1>(b2, y1);
            geometry::set<max_corner, 0>(b2, x2);
            geometry::set<max_corner, 1>(b2, y2);

            return true;
        }
        return false;
    }
};

struct transform_box_or_segment
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& source, Geometry2& target,
                Strategy const& strategy)
    {
        typedef typename point_type<Geometry1>::type point_type1;
        typedef typename point_type<Geometry2>::type point_type2;

        point_type1 source_point[2];
        geometry::detail::assign_point_from_index<0>(source, source_point[0]);
        geometry::detail::assign_point_from_index<1>(source, source_point[1]);

        point_type2 target_point[2];
        if (strategy.apply(source_point[0], target_point[0])
            && strategy.apply(source_point[1], target_point[1]))
        {
            geometry::detail::assign_point_to_index<0>(target_point[0], target);
            geometry::detail::assign_point_to_index<1>(target_point[1], target);
            return true;
        }
        return false;
    }
};


template
<
    typename PointOut,
    typename OutputIterator,
    typename Range,
    typename Strategy
>
inline bool transform_range_out(Range const& range,
    OutputIterator out, Strategy const& strategy)
{
    PointOut point_out;
    for(typename boost::range_iterator<Range const>::type
        it = boost::begin(range);
        it != boost::end(range);
        ++it)
    {
        if (! transform_point::apply(*it, point_out, strategy))
        {
            return false;
        }
        *out++ = point_out;
    }
    return true;
}


struct transform_polygon
{
    template <typename Polygon1, typename Polygon2, typename Strategy>
    static inline bool apply(Polygon1 const& poly1, Polygon2& poly2,
                Strategy const& strategy)
    {
        typedef typename point_type<Polygon2>::type point2_type;

        geometry::clear(poly2);

        if (!transform_range_out<point2_type>(geometry::exterior_ring(poly1),
                    range::back_inserter(geometry::exterior_ring(poly2)), strategy))
        {
            return false;
        }

        // Note: here a resizeable container is assumed.
        traits::resize
            <
                typename boost::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(geometry::interior_rings(poly2),
                     geometry::num_interior_rings(poly1));

        typename geometry::interior_return_type<Polygon1 const>::type
            rings1 = geometry::interior_rings(poly1);
        typename geometry::interior_return_type<Polygon2>::type
            rings2 = geometry::interior_rings(poly2);

        typename detail::interior_iterator<Polygon1 const>::type
            it1 = boost::begin(rings1);
        typename detail::interior_iterator<Polygon2>::type
            it2 = boost::begin(rings2);
        for ( ; it1 != boost::end(rings1); ++it1, ++it2)
        {
            if ( ! transform_range_out<point2_type>(*it1,
                                                    range::back_inserter(*it2),
                                                    strategy) )
            {
                return false;
            }
        }

        return true;
    }
};


template <typename Point1, typename Point2>
struct select_strategy
{
    typedef typename strategy::transform::services::default_strategy
        <
            typename cs_tag<Point1>::type,
            typename cs_tag<Point2>::type,
            typename coordinate_system<Point1>::type,
            typename coordinate_system<Point2>::type,
            dimension<Point1>::type::value,
            dimension<Point2>::type::value,
            typename point_type<Point1>::type,
            typename point_type<Point2>::type
        >::type type;
};

struct transform_range
{
    template <typename Range1, typename Range2, typename Strategy>
    static inline bool apply(Range1 const& range1,
            Range2& range2, Strategy const& strategy)
    {
        typedef typename point_type<Range2>::type point_type;

        // Should NOT be done here!
        // geometry::clear(range2);
        return transform_range_out<point_type>(range1,
                range::back_inserter(range2), strategy);
    }
};


/*!
    \brief Is able to transform any multi-geometry, calling the single-version as policy
*/
template <typename Policy>
struct transform_multi
{
    template <typename Multi1, typename Multi2, typename S>
    static inline bool apply(Multi1 const& multi1, Multi2& multi2, S const& strategy)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            if (! Policy::apply(*it1, *it2, strategy))
            {
                return false;
            }
        }

        return true;
    }
};


}} // namespace detail::transform
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag_cast<typename tag<Geometry1>::type, multi_tag>::type,
    typename Tag2 = typename tag_cast<typename tag<Geometry2>::type, multi_tag>::type
>
struct transform {};

template <typename Point1, typename Point2>
struct transform<Point1, Point2, point_tag, point_tag>
    : detail::transform::transform_point
{
};


template <typename Linestring1, typename Linestring2>
struct transform
    <
        Linestring1, Linestring2,
        linestring_tag, linestring_tag
    >
    : detail::transform::transform_range
{
};

template <typename Range1, typename Range2>
struct transform<Range1, Range2, ring_tag, ring_tag>
    : detail::transform::transform_range
{
};

template <typename Polygon1, typename Polygon2>
struct transform<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : detail::transform::transform_polygon
{
};

template <typename Box1, typename Box2>
struct transform<Box1, Box2, box_tag, box_tag>
    : detail::transform::transform_box
{
};

template <typename Segment1, typename Segment2>
struct transform<Segment1, Segment2, segment_tag, segment_tag>
    : detail::transform::transform_box_or_segment
{
};

template <typename Multi1, typename Multi2>
struct transform
    <
        Multi1, Multi2,
        multi_tag, multi_tag
    >
    : detail::transform::transform_multi
        <
            dispatch::transform
                <
                    typename boost::range_value<Multi1>::type,
                    typename boost::range_value<Multi2>::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct transform
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2>();

        return dispatch::transform<Geometry1, Geometry2>::apply(
            geometry1,
            geometry2,
            strategy
        );
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             default_strategy)
    {
        return apply(
            geometry1,
            geometry2,
            typename detail::transform::select_strategy<Geometry1, Geometry2>::type()
        );
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct transform
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             Strategy const& strategy)
    {
        return resolve_strategy::transform::apply(
            geometry1,
            geometry2,
            strategy
        );
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct transform<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        inline bool operator()(Geometry1 const& geometry1) const
        {
            return transform<Geometry1, Geometry2>::apply(
                geometry1,
                m_geometry2,
                m_strategy
            );
        }
    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

} // namespace resolve_variant


/*!
\brief Transforms from one geometry to another geometry  \brief_strategy
\ingroup transform
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy strategy
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy The strategy to be used for transformation
\return True if the transformation could be done

\qbk{distinguish,with strategy}

\qbk{[include reference/algorithms/transform_with_strategy.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2,
            Strategy const& strategy)
{
    return resolve_variant::transform<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, strategy);
}


/*!
\brief Transforms from one geometry to another geometry using a strategy
\ingroup transform
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return True if the transformation could be done

\qbk{[include reference/algorithms/transform.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2)
{
    return geometry::transform(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP

/* transform.hpp
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
*/