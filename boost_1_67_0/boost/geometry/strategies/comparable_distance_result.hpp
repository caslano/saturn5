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
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
*/