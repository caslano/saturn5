// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

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

#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/distance_result.hpp>

#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


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
    typedef typename strategy::distance::services::return_type
                     <
                         Strategy,
                         typename point_type<Geometry2>::type,
                         typename point_type<Geometry1>::type
                     >::type return_type;

    static inline return_type apply(
        Geometry1 const& g1,
        Geometry2 const& g2,
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

template <typename Strategy>
struct distance
{
    template <typename Geometry1, typename Geometry2>
    static inline typename distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return dispatch::distance
            <
                Geometry1, Geometry2, Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};

template <>
struct distance<default_strategy>
{
    template <typename Geometry1, typename Geometry2>
    static inline
    typename distance_result<Geometry1, Geometry2, default_strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          default_strategy)
    {
        typedef typename detail::distance::default_strategy
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


namespace resolve_variant
{


template <typename Geometry1, typename Geometry2>
struct distance
{
    template <typename Strategy>
    static inline typename distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return resolve_strategy::distance
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct distance<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename distance_result
                <
                    variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
                    Geometry2,
                    Strategy
                >::type
        >
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2,
                Strategy const& strategy)
            : m_geometry2(geometry2),
              m_strategy(strategy)
        {}

        template <typename Geometry1>
        typename distance_result<Geometry1, Geometry2, Strategy>::type
        operator()(Geometry1 const& geometry1) const
        {
            return distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                    <
                        Strategy
                    >(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename distance_result
        <
            variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Geometry2,
            Strategy
        >::type
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct distance<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename distance_result
                <
                    Geometry1,
                    variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
                    Strategy
                >::type
        >
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1,
                Strategy const& strategy)
            : m_geometry1(geometry1),
              m_strategy(strategy)
        {}

        template <typename Geometry2>
        typename distance_result<Geometry1, Geometry2, Strategy>::type
        operator()(Geometry2 const& geometry2) const
        {
            return distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                <
                    Strategy
                >(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename distance_result
        <
            Geometry1,
            variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Strategy
        >::type
    apply(
        Geometry1 const& geometry1,
        const variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry2,
        Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};


template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct distance
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename distance_result
                <
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>,
                    Strategy
                >::type
        >
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        typename distance_result<Geometry1, Geometry2, Strategy>::type
        operator()(Geometry1 const& geometry1, Geometry2 const& geometry2) const
        {
            return distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                <
                    Strategy
                >(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename distance_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>,
            Strategy
        >::type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


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
inline typename distance_result<Geometry1, Geometry2, Strategy>::type
distance(Geometry1 const& geometry1,
         Geometry2 const& geometry2,
         Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    detail::throw_on_empty_input(geometry1);
    detail::throw_on_empty_input(geometry2);

    return resolve_variant::distance
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
inline typename default_distance_result<Geometry1, Geometry2>::type
distance(Geometry1 const& geometry1,
         Geometry2 const& geometry2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return geometry::distance(geometry1, geometry2, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_INTERFACE_HPP

/* interface.hpp
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
*/