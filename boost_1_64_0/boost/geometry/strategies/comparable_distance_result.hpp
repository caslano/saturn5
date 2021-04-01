// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP

#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/util/compress_variant.hpp>
#include <boost/geometry/util/transform_variant.hpp>
#include <boost/geometry/util/combine_if.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_result
    : strategy::distance::services::return_type
        <
            typename strategy::distance::services::comparable_type
                <
                    Strategy
                >::type,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, default_strategy>
    : comparable_distance_result
        <
            Geometry1,
            Geometry2,
            typename detail::distance::default_strategy
                <
                    Geometry1, Geometry2
                >::type
        >
{};

} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_result
    : resolve_strategy::comparable_distance_result
        <
            Geometry1,
            Geometry2,
            Strategy
        >
{};


template
<
    typename Geometry1,
    BOOST_VARIANT_ENUM_PARAMS(typename T),
    typename Strategy
>
struct comparable_distance_result
    <
        Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if<
        typename boost::mpl::vector1<Geometry1>,
        typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
        boost::mpl::always<boost::mpl::true_>
    >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::comparable_distance_result<
                boost::mpl::first<boost::mpl::_>,
                boost::mpl::second<boost::mpl::_>,
                Strategy
            >,
            boost::mpl::back_inserter<boost::mpl::vector0<> >
        >::type
    >::type type;
};


// Distance arguments are commutative
template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T),
    typename Geometry2,
    typename Strategy
>
struct comparable_distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2,
        Strategy
    > : public comparable_distance_result
        <
            Geometry2, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
        >
{};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct comparable_distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if
        <
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            boost::mpl::always<boost::mpl::true_>
        >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::comparable_distance_result<
                boost::mpl::first<boost::mpl::_>,
                boost::mpl::second<boost::mpl::_>,
                Strategy
            >,
            boost::mpl::back_inserter<boost::mpl::vector0<> >
        >::type
    >::type type;
};

} // namespace resolve_variant





/*!
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
*/
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Strategy = void
>
struct comparable_distance_result
    : resolve_variant::comparable_distance_result
        <
            Geometry1, Geometry2, Strategy
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, void>
    : comparable_distance_result<Geometry1, Geometry2, default_strategy>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP

/* comparable_distance_result.hpp
CIDlnvlh3fOmJHY8H/mb1g1LujKEVYUXgDkvrm5g6tTFU2gWG083nsNUHX/s0vD/JWS4gzPtRFwkcPkb1Ahkbp0c7Ni9hJuTdOqThBCSjVeyTVzxd0bGZ1jx3DCJYJbg8eb0F9/VNCmFd6kZGMnIY0s+46S6hjwJgXOmwd0M0tFcfONPW3WNHWbvTsjXkLDMtksE4KYtu2PYz769672vCdOaRdZIVZozKTPsjiQlHqw7hwHTqwQgM5xTxGGssdJhkzT1NW9svQHidUurjJJRprLeTZ5AhfSFqLNGJHD0XbF0mUeLw/y7imawY0whHuVmYR8ttqFlINIeqSe7sIA7IHkaUZAYfYxz6MU2LLswbRcX8xxVb8ftLo0vRptWEygJIvIgitcKhi0VpODzjLg13aJE1Pepf0Pscm9sFC1oUpVshZvBtjl7IuQf1Ddz7eMJIqOW2mJCxKiMqV9tiZF7C4K4q7o+3/xRZFyrRNBvIQhVZDnOrWZM1VaZ450MsJOmvpCbfrLLgW9OhycCCGj3C7NQ4rC47G7LL/45cGeBX+fnnLGVFMd9g6UUmw==
*/