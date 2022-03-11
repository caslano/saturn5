// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014, 2015.
// Modifications copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP

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
struct distance_result
    : strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >
{};

template <typename Geometry1, typename Geometry2>
struct distance_result<Geometry1, Geometry2, default_strategy>
    : distance_result
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
struct distance_result
    : resolve_strategy::distance_result
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
struct distance_result
    <
        Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if<
        typename boost::mpl::vector1<Geometry1>,
        typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
        // Here we want should remove most of the combinations that
        // are not valid, mostly to limit the size of the resulting MPL set.
        // But is_implementedn is not ready for prime time
        //
        // util::is_implemented2<boost::mpl::_1, boost::mpl::_2, dispatch::distance<boost::mpl::_1, boost::mpl::_2> >
        boost::mpl::always<boost::mpl::true_>
    >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::distance_result<
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
struct distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2,
        Strategy
    > : public distance_result
        <
            Geometry2, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
        >
{};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct distance_result
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
            // Here we want to try to remove most of the combinations
            // that are not valid, mostly to limit the size of the
            // resulting MPL vector.
            // But is_implemented is not ready for prime time
            //
            // util::is_implemented2<boost::mpl::_1, boost::mpl::_2, dispatch::distance<boost::mpl::_1, boost::mpl::_2> >
            boost::mpl::always<boost::mpl::true_>
        >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::distance_result<
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
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Strategy = void
>
struct distance_result
    : resolve_variant::distance_result<Geometry1, Geometry2, Strategy>
{};


template <typename Geometry1, typename Geometry2>
struct distance_result<Geometry1, Geometry2, void>
    : distance_result<Geometry1, Geometry2, default_strategy>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP

/* distance_result.hpp
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
*/