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
WzFmM84SLVOfSoFGohBPPLS5IBa7iaxUGFDs/gZKqb2PbaAJw+FZMAqDcojyCdCb4T1KF0Xg7RS4EYB6dbltSrAZhfgeYhK+mNMYNoqDAHLKIRLQNBEi1QvnHVEgdBrVyOgGAaEjZA2iMjYSV7gziEyFKb2LcTjV545hu4oF0riEaZoQeYO8BNwqak+mjwSyuzuivUR6hh2SqaMS/uK6IupmyKQCmQS3V90D6++C9ffBg3dCFaGOxHo1PmYkSTqhS5RtofSlpKBADDSV4SmW3UeUkaw++L+EZCXkcxwPrD7ZtS1jzsPbjPPKveFx76Kr97rdw+5haINVzlY8ocZ0DWfB8LwAm4MqpMrtz6U61Nt0rmOVLMIq+Y5VMh6r5DxWnK+ihMyWhltfxASYX9UhYqqgxOOEbMw0hRE3cPwaOfcysU1LNqk62FGuyyWnElt1dXfmAVumsp8A8mVPwC2j6lSLzzjRQD7qZLTgkbXGxFLS1L8he69eAY0QXAl8q8TMp+h3gcnNG4jWfIpHmoCUo4U8LyIKAWHqVXtmkWdWvZlJCiSclUbS9fibkzhDPJCvdhHpJsa9pDt2wXzZ9zgPSjUIFP8sAiqXL+Xkpdy/rMuHQEn30uXelGlRSzJnFCvzOAuWytDnumUye0ms
*/