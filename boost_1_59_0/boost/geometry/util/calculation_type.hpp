// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP


#include <boost/static_assert.hpp>

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
    typedef long long type;
};

/*!
\details Selects the most appropriate:
    - if calculation type is specified (not void), that one is used
    - else if type is non-fundamental (user defined e.g. Boost.Multiprecision), that one
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
        std::is_fundamental
            <
                DefaultFloatingPointCalculationType
            >::value
        ));
    BOOST_STATIC_ASSERT((
        std::is_fundamental
            <
                DefaultIntegralCalculationType
            >::value
        ));


    typedef std::conditional_t
        <
            std::is_void<CalculationType>::value,
            std::conditional_t
                <
                    std::is_floating_point<Type>::value,
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
                >,
            CalculationType
        > type;
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