// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_AREA_HPP
#define BOOST_GEOMETRY_ALGORITHMS_AREA_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/calculate_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>

#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/area_result.hpp>
#include <boost/geometry/strategies/default_area_result.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/strategies/concepts/area_concept.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/order_as_direction.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace area
{

struct box_area
{
    template <typename Box, typename Strategy>
    static inline typename coordinate_type<Box>::type
    apply(Box const& box, Strategy const&)
    {
        // Currently only works for 2D Cartesian boxes
        assert_dimension<Box, 2>();

        return (get<max_corner, 0>(box) - get<min_corner, 0>(box))
             * (get<max_corner, 1>(box) - get<min_corner, 1>(box));
    }
};


template
<
    iterate_direction Direction,
    closure_selector Closure
>
struct ring_area
{
    template <typename Ring, typename Strategy>
    static inline typename area_result<Ring, Strategy>::type
    apply(Ring const& ring, Strategy const& strategy)
    {
        BOOST_CONCEPT_ASSERT( (geometry::concepts::AreaStrategy<Ring, Strategy>) );
        assert_dimension<Ring, 2>();

        // Ignore warning (because using static method sometimes) on strategy
        boost::ignore_unused(strategy);

        // An open ring has at least three points,
        // A closed ring has at least four points,
        // if not, there is no (zero) area
        if (boost::size(ring)
                < core_detail::closure::minimum_ring_size<Closure>::value)
        {
            return typename area_result<Ring, Strategy>::type();
        }

        typedef typename reversible_view<Ring const, Direction>::type rview_type;
        typedef typename closeable_view
            <
                rview_type const, Closure
            >::type view_type;
        typedef typename boost::range_iterator<view_type const>::type iterator_type;

        rview_type rview(ring);
        view_type view(rview);
        typename Strategy::template state<Ring> state;
        iterator_type it = boost::begin(view);
        iterator_type end = boost::end(view);

        for (iterator_type previous = it++;
            it != end;
            ++previous, ++it)
        {
            strategy.apply(*previous, *it, state);
        }

        return strategy.result(state);
    }
};


}} // namespace detail::area


#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct area : detail::calculate_null
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply
            <
                typename area_result<Geometry, Strategy>::type
            >(geometry, strategy);
    }
};


template <typename Geometry>
struct area<Geometry, box_tag> : detail::area::box_area
{};


template <typename Ring>
struct area<Ring, ring_tag>
    : detail::area::ring_area
        <
            order_as_direction<geometry::point_order<Ring>::value>::value,
            geometry::closure<Ring>::value
        >
{};


template <typename Polygon>
struct area<Polygon, polygon_tag> : detail::calculate_polygon_sum
{
    template <typename Strategy>
    static inline typename area_result<Polygon, Strategy>::type
        apply(Polygon const& polygon, Strategy const& strategy)
    {
        return calculate_polygon_sum::apply<
            typename area_result<Polygon, Strategy>::type,
            detail::area::ring_area
                <
                    order_as_direction<geometry::point_order<Polygon>::value>::value,
                    geometry::closure<Polygon>::value
                >
            >(polygon, strategy);
    }
};


template <typename MultiGeometry>
struct area<MultiGeometry, multi_polygon_tag> : detail::multi_sum
{
    template <typename Strategy>
    static inline typename area_result<MultiGeometry, Strategy>::type
    apply(MultiGeometry const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   typename area_result<MultiGeometry, Strategy>::type,
                   area<typename boost::range_value<MultiGeometry>::type>
               >(multi, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template <typename Strategy>
struct area
{
    template <typename Geometry>
    static inline typename area_result<Geometry, Strategy>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return dispatch::area<Geometry>::apply(geometry, strategy);
    }
};

template <>
struct area<default_strategy>
{
    template <typename Geometry>
    static inline typename area_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy)
    {
        typedef typename strategy::area::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

        return dispatch::area<Geometry>::apply(geometry, strategy_type());
    }
};


} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry>
struct area
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        return resolve_strategy::area<Strategy>::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct area<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> variant_type;

    template <typename Strategy>
    struct visitor
        : boost::static_visitor<typename area_result<variant_type, Strategy>::type>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry>
        typename area_result<variant_type, Strategy>::type
        operator()(Geometry const& geometry) const
        {
            return area<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename area_result<variant_type, Strategy>::type
    apply(variant_type const& geometry,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{area}
\ingroup area
\details \details_calc{area}. \details_default_strategy

The area algorithm calculates the surface area of all geometries having a surface, namely
box, polygon, ring, multipolygon. The units are the square of the units used for the points
defining the surface. If subject geometry is defined in meters, then area is calculated
in square meters.

The area calculation can be done in all three common coordinate systems, Cartesian, Spherical
and Geographic as well.

\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{area}

\qbk{[include reference/algorithms/area.qbk]}
\qbk{[heading Examples]}
\qbk{[area] [area_output]}
*/
template <typename Geometry>
inline typename area_result<Geometry>::type
area(Geometry const& geometry)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_variant::area<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief \brief_calc{area} \brief_strategy
\ingroup area
\details \details_calc{area} \brief_strategy. \details_strategy_reasons
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Area}
\param geometry \param_geometry
\param strategy \param_strategy{area}
\return \return_calc{area}

\qbk{distinguish,with strategy}

\qbk{
[include reference/algorithms/area.qbk]

[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_area_cartesian Cartesian]
\* [link geometry.reference.strategies.strategy_area_spherical Spherical]
\* [link geometry.reference.strategies.strategy_area_geographic Geographic]

[heading Example]
[area_with_strategy]
[area_with_strategy_output]
}
 */
template <typename Geometry, typename Strategy>
inline typename area_result<Geometry, Strategy>::type
area(Geometry const& geometry, Strategy const& strategy)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_variant::area<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_AREA_HPP

/* area.hpp
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
*/