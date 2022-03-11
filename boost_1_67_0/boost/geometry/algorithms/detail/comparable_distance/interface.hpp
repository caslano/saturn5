// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2019.
// Modifications copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/comparable_distance_result.hpp>
#include <boost/geometry/strategies/default_comparable_distance_result.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/interface.hpp>


namespace boost { namespace geometry
{


namespace resolve_strategy
{

template <typename Strategy>
struct comparable_distance
{
    template <typename Geometry1, typename Geometry2>
    static inline
    typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        typedef typename strategy::distance::services::comparable_type
            <
                Strategy
            >::type comparable_strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, comparable_strategy_type
            >::apply(geometry1,
                     geometry2,
                     strategy::distance::services::get_comparable
                         <
                             Strategy
                         >::apply(strategy));
    }
};

template <>
struct comparable_distance<default_strategy>
{
    template <typename Geometry1, typename Geometry2>
    static inline typename comparable_distance_result
        <
            Geometry1, Geometry2, default_strategy
        >::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          default_strategy)
    {
        typedef typename strategy::distance::services::comparable_type
            <
                typename detail::distance::default_strategy
                    <
                        Geometry1, Geometry2
                    >::type
            >::type comparable_strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, comparable_strategy_type
            >::apply(geometry1, geometry2, comparable_strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant
{


template <typename Geometry1, typename Geometry2>
struct comparable_distance
{
    template <typename Strategy>
    static inline
    typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return resolve_strategy::comparable_distance
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct comparable_distance
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
                <
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
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
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry1 const& geometry1) const
        {
            return comparable_distance
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
    static inline typename comparable_distance_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Geometry2,
            Strategy
        >::type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct comparable_distance
    <
        Geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
                <
                    Geometry1,
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
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
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry2 const& geometry2) const
        {
            return comparable_distance
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
    static inline typename comparable_distance_result
        <
            Geometry1,
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Strategy
        >::type
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
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
struct comparable_distance
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
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
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry1 const& geometry1, Geometry2 const& geometry2) const
        {
            return comparable_distance
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
    static inline typename comparable_distance_result
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
\brief \brief_calc2{comparable distance measurement} \brief_strategy
\ingroup distance
\details The free function comparable_distance does not necessarily calculate the distance,
    but it calculates a distance measure such that two distances are comparable to each other.
    For example: for the Cartesian coordinate system, Pythagoras is used but the square root
    is not taken, which makes it faster and the results of two point pairs can still be
    compared to each other.
\tparam Geometry1 first geometry type
\tparam Geometry2 second geometry type
\tparam Strategy \tparam_strategy{Distance}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{distance}
\return \return_calc{comparable distance}

\qbk{distinguish,with strategy}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
comparable_distance(Geometry1 const& geometry1, Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return resolve_variant::comparable_distance
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}



/*!
\brief \brief_calc2{comparable distance measurement}
\ingroup distance
\details The free function comparable_distance does not necessarily calculate the distance,
    but it calculates a distance measure such that two distances are comparable to each other.
    For example: for the Cartesian coordinate system, Pythagoras is used but the square root
    is not taken, which makes it faster and the results of two point pairs can still be
    compared to each other.
\tparam Geometry1 first geometry type
\tparam Geometry2 second geometry type
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_calc{comparable distance}

\qbk{[include reference/algorithms/comparable_distance.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline typename default_comparable_distance_result<Geometry1, Geometry2>::type
comparable_distance(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return geometry::comparable_distance(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP

/* interface.hpp
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
*/