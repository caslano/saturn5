// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace util
{

namespace detail
{

struct default_integral
{
#ifdef BOOST_HAS_LONG_LONG
    typedef boost::long_long_type type;
#else
    typedef int type;
#endif
};

/*!
\details Selects the most appropriate:
    - if calculation type is specified (not void), that one is used
    - else if type is non-fundamental (user defined e.g. ttmath), that one
    - else if type is floating point, the specified default FP is used
    - else it is integral and the specified default integral is used
 */
template
<
    typename Type,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType,
    typename DefaultIntegralCalculationType
>
struct calculation_type
{
    BOOST_STATIC_ASSERT((
        boost::is_fundamental
            <
                DefaultFloatingPointCalculationType
            >::type::value
        ));
    BOOST_STATIC_ASSERT((
        boost::is_fundamental
            <
                DefaultIntegralCalculationType
            >::type::value
        ));


    typedef typename boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename boost::mpl::if_
                <
                    boost::is_floating_point<Type>,
                    typename select_most_precise
                        <
                            DefaultFloatingPointCalculationType,
                            Type
                        >::type,
                    typename select_most_precise
                        <
                            DefaultIntegralCalculationType,
                            Type
                        >::type
                >::type,
            CalculationType
        >::type type;
};

} // namespace detail


namespace calculation_type
{

namespace geometric
{

template
<
    typename Geometry,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct unary
{
    typedef typename detail::calculation_type
        <
            typename geometry::coordinate_type<Geometry>::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};

template
<
    typename Geometry1,
    typename Geometry2,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct binary
{
    typedef typename detail::calculation_type
        <
            typename select_coordinate_type<Geometry1, Geometry2>::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};


/*!
\brief calculation type (ternary, for three geometry types)
 */
template
<
    typename Geometry1,
    typename Geometry2,
    typename Geometry3,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct ternary
{
    typedef typename detail::calculation_type
        <
            typename select_most_precise
                <
                    typename coordinate_type<Geometry1>::type,
                    typename select_coordinate_type
                        <
                            Geometry2,
                            Geometry3
                        >::type
                >::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};

}} // namespace calculation_type::geometric

} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP

/* calculation_type.hpp
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
*/