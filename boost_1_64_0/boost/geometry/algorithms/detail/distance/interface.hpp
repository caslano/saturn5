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
9QivNIH9wfo0Fl2zk7bP775naV/YHkgtz2Wd6a2G/+b0gW3FwFqmb4DrnWnS2fxkXsmwjeqAV5HJrF/KXleko6HNMCVTwBY1MzsHbAuTh53wKj+dVYoPG/M7DvvBOzXfUb+M+k6twfmc2ekOGm1MZTkoZS1J+TwzvNf1arexl4XiDAdWp+NridWWI/JelNd30Xv284Oi6a4dcBjG1gNg2aeKWTdYaq1t9orNFjVUPuDnNOETLTz5mj7y76UluEdt5gmn0XYHzGr2noBGnIkLcfQ5Z6w91+HHOvBgGJ0OY8fc1+8l4Yn++RgO7yyp/jZ5XkUua4lbYzX9mTimHETDfw+jU8MvOFJoNV20SC3A5ZnT9R7d1ANuf33X6/Tbo7eeEVArRavzUOnYPONx7mbegBh9HcsaEuPaq/CzpXzloivNG+XV4s9leGyHeEPmjW7qp/9jHHGZv7OPRpvjubf6PJZ8uGANDXfSGvgAE+Htyr7O69T1J9PosMI8+jT2cIjmSerfVfxZOjQ7rRZrDa6Rn4uu2f5z/rNauE7LPIvN16DxsrWFhZ3VdwP7qGzmL6QGYcNjPP+ULsy3hWccqnf4Csa1wAH6ZFFbeNcbZunV3vZ+Sc4ixCkTbR7wnpSDeVznXJeP/Rw2dcvrnua21DzsvOlgmJzElZ8Trc28N3G6Gf0Br2K+9f/DX44Mc90PzbMw5TNeeRwYMBv3LJbz4CiYtZ0fMMteW1hHO72Es5tOwQdmjWrfBfxsL89QXY04hfNpgQ92iwm9M7MFTNF316rYl1777Bu+k9m0EeyZ9o911qD38tK5+is5fD4uRjf4bdtWui49sL4TbdrYM3xzaLfdtDmd/ssGmGp+nHHf2fo49aAOhxYwHw9xfsV7PM/PW5kefuHExDT89LI0e2GacxaNcIre19s19Mixj+DfYvOiOblKdT1bnKcVac7lZY/Mr67iy2ciXOhrp2jI0IAZn84ckJwupSv7Z8XrP6nBZeaHXXpfrSZsasZPKg81YQoOiZdC3+u/V+9oBGvezktI2kC9HbcnM8Hfkebcnepb/gc5n9mXEzfAhbpiW1sd51JTh27qY2fLH8d46Ft51RXM/Z3lyKxZZ7IZoJRebo/re9NIzphuy++l2kF8He9NChNgcrIxcKZXCC6Af7C0/Eg8r0fK38KlMKvcXP0gftui5Vgv9Taz/C0vpbryEh7TG3f5r/Lza35zA49uMW686T0P6Ykq8r5C/e37WCm+sBf66uZRa6CN5012lgmfliwye77So09h3XVnZ0dxdozPxyv0lkCZjJ59joJLzrzmRgdLptl3nXWpmzuwJ2i2ZwBds0Qj+WivVoNpwtrqP4rP3pDvIxfT6ZYCX8IFnJEEH6wvLI90fK9Y7gFXKrrHbxPhwi1xy6MO6qmDSvT273zUIfQybj9i/tp6xZyLxxOuMD9V5AlZS+4W9s5TuDAOnhfG2WoxJx67sFJc/rFmPnDebvQ5zD01hL4eJ6/isbSuZ0idNeynd7ens/+eYlWErkvF/4Gz+V1njP5dvt6cEuMD6/3wCPt23R8K045qpZVcxx4AV5t43RdB+MWsFqr/5wY890fjTqDlPPt6BudHLKf3WsGcvnyBHfJMPxwJ6FnaN9j74swNoZdh/UAxgcUlrtp/UVpiq/3F5SUNoMnv02+rnNXAwftwqHt3WiwWfGoOD0fAqpVmUrWey4xTtaKaltcnIThJvP9JxpcTl6NPzT4LnPOKeXb4m7mivdLGn8LxN3nlDq92Vm+Xx8LrWPoXTo3oLT91vTdKT2eHSdloHjU4pK/+WyV/G+meTri+FS/Nuqv9TWdv482NgvF/eh2d/SidtZixplU=
*/