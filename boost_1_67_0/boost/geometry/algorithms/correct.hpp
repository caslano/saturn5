// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP


#include <algorithm>
#include <cstddef>
#include <functional>

#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/correct_closure.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/util/order_as_direction.hpp>

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace correct
{

template <typename Geometry>
struct correct_nop
{
    template <typename Strategy>
    static inline void apply(Geometry& , Strategy const& )
    {}
};


template <typename Box, std::size_t Dimension, std::size_t DimensionCount>
struct correct_box_loop
{
    typedef typename coordinate_type<Box>::type coordinate_type;

    static inline void apply(Box& box)
    {
        if (get<min_corner, Dimension>(box) > get<max_corner, Dimension>(box))
        {
            // Swap the coordinates
            coordinate_type max_value = get<min_corner, Dimension>(box);
            coordinate_type min_value = get<max_corner, Dimension>(box);
            set<min_corner, Dimension>(box, min_value);
            set<max_corner, Dimension>(box, max_value);
        }

        correct_box_loop
            <
                Box, Dimension + 1, DimensionCount
            >::apply(box);
    }
};



template <typename Box, std::size_t DimensionCount>
struct correct_box_loop<Box, DimensionCount, DimensionCount>
{
    static inline void apply(Box& )
    {}

};


// Correct a box: make min/max correct
template <typename Box>
struct correct_box
{
    template <typename Strategy>
    static inline void apply(Box& box, Strategy const& )
    {
        // Currently only for Cartesian coordinates
        // (or spherical without crossing dateline)
        // Future version: adapt using strategies
        correct_box_loop
            <
                Box, 0, dimension<Box>::type::value
            >::apply(box);
    }
};


// Close a ring, if not closed
template <typename Ring, template <typename> class Predicate>
struct correct_ring
{
    typedef typename point_type<Ring>::type point_type;
    typedef typename coordinate_type<Ring>::type coordinate_type;

    typedef detail::area::ring_area
            <
                order_as_direction<geometry::point_order<Ring>::value>::value,
                geometry::closure<Ring>::value
            > ring_area_type;


    template <typename Strategy>
    static inline void apply(Ring& r, Strategy const& strategy)
    {
        // Correct closure if necessary
        detail::correct_closure::close_or_open_ring<Ring>::apply(r);

        // Check area
        typedef typename area_result<Ring, Strategy>::type area_result_type;
        Predicate<area_result_type> predicate;
        area_result_type const zero = 0;
        if (predicate(ring_area_type::apply(r, strategy), zero))
        {
            std::reverse(boost::begin(r), boost::end(r));
        }
    }
};

// Correct a polygon: normalizes all rings, sets outer ring clockwise, sets all
// inner rings counter clockwise (or vice versa depending on orientation)
template <typename Polygon>
struct correct_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;
    
    template <typename Strategy>
    static inline void apply(Polygon& poly, Strategy const& strategy)
    {
        correct_ring
            <
                ring_type,
                std::less
            >::apply(exterior_ring(poly), strategy);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            correct_ring
                <
                    ring_type,
                    std::greater
                >::apply(*it, strategy);
        }
    }
};


}} // namespace detail::correct
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct correct: not_implemented<Tag>
{};

template <typename Point>
struct correct<Point, point_tag>
    : detail::correct::correct_nop<Point>
{};

template <typename LineString>
struct correct<LineString, linestring_tag>
    : detail::correct::correct_nop<LineString>
{};

template <typename Segment>
struct correct<Segment, segment_tag>
    : detail::correct::correct_nop<Segment>
{};


template <typename Box>
struct correct<Box, box_tag>
    : detail::correct::correct_box<Box>
{};

template <typename Ring>
struct correct<Ring, ring_tag>
    : detail::correct::correct_ring
        <
            Ring,
            std::less
        >
{};

template <typename Polygon>
struct correct<Polygon, polygon_tag>
    : detail::correct::correct_polygon<Polygon>
{};


template <typename MultiPoint>
struct correct<MultiPoint, multi_point_tag>
    : detail::correct::correct_nop<MultiPoint>
{};


template <typename MultiLineString>
struct correct<MultiLineString, multi_linestring_tag>
    : detail::correct::correct_nop<MultiLineString>
{};


template <typename Geometry>
struct correct<Geometry, multi_polygon_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::correct::correct_polygon
                <
                    typename boost::range_value<Geometry>::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct correct
{
    template <typename Strategy>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        dispatch::correct<Geometry>::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct correct<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            correct<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry, Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief Corrects a geometry
\details Corrects a geometry: all rings which are wrongly oriented with respect
    to their expected orientation are reversed. To all rings which do not have a
    closing point and are typed as they should have one, the first point is
    appended. Also boxes can be corrected.
\ingroup correct
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be corrected if necessary

\qbk{[include reference/algorithms/correct.qbk]}
*/
template <typename Geometry>
inline void correct(Geometry& geometry)
{
    typedef typename point_type<Geometry>::type point_type;

    typedef typename strategy::area::services::default_strategy
        <
            typename cs_tag<point_type>::type
        >::type strategy_type;

    resolve_variant::correct<Geometry>::apply(geometry, strategy_type());
}

/*!
\brief Corrects a geometry
\details Corrects a geometry: all rings which are wrongly oriented with respect
    to their expected orientation are reversed. To all rings which do not have a
    closing point and are typed as they should have one, the first point is
    appended. Also boxes can be corrected.
\ingroup correct
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Area}
\param geometry \param_geometry which will be corrected if necessary
\param strategy \param_strategy{area}

\qbk{distinguish,with strategy}

\qbk{[include reference/algorithms/correct.qbk]}
*/
template <typename Geometry, typename Strategy>
inline void correct(Geometry& geometry, Strategy const& strategy)
{
    resolve_variant::correct<Geometry>::apply(geometry, strategy);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP

/* correct.hpp
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
*/