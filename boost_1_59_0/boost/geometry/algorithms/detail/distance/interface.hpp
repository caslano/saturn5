// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_INTERFACE_HPP

#include <boost/concept_check.hpp>

#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

// TODO: move these to algorithms
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/distance_result.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/services.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2, typename Strategy,
    typename Tag1, typename Tag2, typename StrategyTag
>
struct distance
<
    Geometry1, Geometry2, Strategy,
    Tag1, Tag2, StrategyTag,
    true
>
    : distance<Geometry2, Geometry1, Strategy, Tag2, Tag1, StrategyTag, false>
{
    static inline auto apply(Geometry1 const& g1, Geometry2 const& g2,
                             Strategy const& strategy)
    {
        return distance
            <
                Geometry2, Geometry1, Strategy,
                Tag2, Tag1, StrategyTag,
                false
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct distance
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::distance
            <
                Geometry1, Geometry2, Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct is_strategy_converter_specialized
{
    typedef strategies::distance::services::strategy_converter<Strategy> converter;
    static const bool value = ! std::is_same
        <
            decltype(converter::get(std::declval<Strategy>())),
            strategies::detail::not_implemented
        >::value;
};

template <typename Strategy>
struct distance<Strategy, false>
{
    template
    <
        typename Geometry1, typename Geometry2, typename S,
        std::enable_if_t<is_strategy_converter_specialized<S>::value, int> = 0
    >
    static inline auto apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             S const& strategy)
    {
        typedef strategies::distance::services::strategy_converter<Strategy> converter;
        typedef decltype(converter::get(strategy)) strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, strategy_type
            >::apply(geometry1, geometry2, converter::get(strategy));
    }

    template
    <
        typename Geometry1, typename Geometry2, typename S,
        std::enable_if_t<! is_strategy_converter_specialized<S>::value, int> = 0
    >
    static inline auto apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             S const& strategy)
    {
        typedef strategies::distance::services::custom_strategy_converter
            <
                Geometry1, Geometry2, Strategy
            > converter;
        typedef decltype(converter::get(strategy)) strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, strategy_type
            >::apply(geometry1, geometry2, converter::get(strategy));
    }
};

template <>
struct distance<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategies::distance::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, strategy_type
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic
{


template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type
>
struct distance
{
    template <typename Strategy>
    static inline auto apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return resolve_strategy::distance
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};


template <typename DynamicGeometry1, typename Geometry2, typename Tag2>
struct distance<DynamicGeometry1, Geometry2, dynamic_geometry_tag, Tag2>
{
    template <typename Strategy>
    static inline auto apply(DynamicGeometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using result_t = typename geometry::distance_result<DynamicGeometry1, Geometry2, Strategy>::type;
        result_t result = 0;
        traits::visit<DynamicGeometry1>::apply([&](auto const& g1)
        {
            result = resolve_strategy::distance
                        <
                            Strategy
                        >::apply(g1, geometry2, strategy);
        }, geometry1);
        return result;
    }
};


template <typename Geometry1, typename DynamicGeometry2, typename Tag1>
struct distance<Geometry1, DynamicGeometry2, Tag1, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline auto apply(Geometry1 const& geometry1,
                             DynamicGeometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using result_t = typename geometry::distance_result<Geometry1, DynamicGeometry2, Strategy>::type;
        result_t result = 0;
        traits::visit<DynamicGeometry2>::apply([&](auto const& g2)
        {
            result = resolve_strategy::distance
                        <
                            Strategy
                        >::apply(geometry1, g2, strategy);
        }, geometry2);
        return result;
    }
};


template <typename DynamicGeometry1, typename DynamicGeometry2>
struct distance<DynamicGeometry1, DynamicGeometry2, dynamic_geometry_tag, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline auto apply(DynamicGeometry1 const& geometry1,
                             DynamicGeometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using result_t = typename geometry::distance_result<DynamicGeometry1, DynamicGeometry2, Strategy>::type;
        result_t result = 0;
        traits::visit<DynamicGeometry1, DynamicGeometry2>::apply([&](auto const& g1, auto const& g2)
        {
            result = resolve_strategy::distance
                        <
                            Strategy
                        >::apply(g1, g2, strategy);
        }, geometry1, geometry2);
        return result;
    }
};

} // namespace resolve_dynamic


/*!
\brief Calculate the distance between two geometries \brief_strategy
\ingroup distance
\details
\details The free function distance calculates the distance between two geometries \brief_strategy. \details_strategy_reasons

\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Distance}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{distance}
\return \return_calc{distance}
\note The strategy can be a point-point strategy. In case of distance point-line/point-polygon
    it may also be a point-segment strategy.

\qbk{distinguish,with strategy}

\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_distance_pythagoras Pythagoras (cartesian)]
\* [link geometry.reference.strategies.strategy_distance_haversine Haversine (spherical)]
\* [link geometry.reference.strategies.strategy_distance_cross_track Cross track (spherical\, point-to-segment)]
\* [link geometry.reference.strategies.strategy_distance_projected_point Projected point (cartesian\, point-to-segment)]
\* more (currently extensions): Vincenty\, Andoyer (geographic)
}
 */

/*
Note, in case of a Compilation Error:
if you get:
 - "Failed to specialize function template ..."
 - "error: no matching function for call to ..."
for distance, it is probably so that there is no specialization
for return_type<...> for your strategy.
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline auto distance(Geometry1 const& geometry1,
                     Geometry2 const& geometry2,
                     Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    detail::throw_on_empty_input(geometry1);
    detail::throw_on_empty_input(geometry2);

    return resolve_dynamic::distance
               <
                   Geometry1,
                   Geometry2
               >::apply(geometry1, geometry2, strategy);
}


/*!
\brief Calculate the distance between two geometries.
\ingroup distance
\details The free function distance calculates the distance between two geometries. \details_default_strategy

\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_calc{distance}

\qbk{[include reference/algorithms/distance.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline auto distance(Geometry1 const& geometry1,
                     Geometry2 const& geometry2)
{
    return geometry::distance(geometry1, geometry2, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_INTERFACE_HPP

/* interface.hpp
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
*/