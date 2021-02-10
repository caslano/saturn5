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
6QNluX73aFSg4lEI/JwNSyZ7Vmq7ROQJltdwQcz8NegU6Jk7kCXAOGK2vuLIUczuZB9KEOUTBCPliZaXtal3pivCus1OHUOK/Rh72R5uFQMgvYfjhB/yud0SACjCBjs+ZWdO9rcGnIRO7C4paZxJhDiOwxlYIHs3T6L/GDu/kgQohi4FToam72nq9IzHcQpt4wGA7QqPpLvuTVAsefvUksoZ2qRjtLEwOOUR27DtG9f0S40an+Zk0NcwS3Wmwvh6FT0Rrp/SVzDYdqXbAu/LWeeU9QOX4mWxhjTg+5j6T5SBdFGFXCT120wc31rtm7GW6jEEsbjTMUWNO9vjakMceY2ORJyWeiBxvPy0FQCeUdFiKqFsCnAy5w5nEX5dmkb2XD27mw/zddORVJ0Iwu+SznQ94UmcBVAv7nz103A0QJP2EMgRPP6LrGaNMxPvl1CLhjtBnbhAE6IcjUO11J1cM5PmTdOe1pManbECO+7DD8dWWJcl4d1394siaZjHWT4m5uS+YT4tPm6awzsPLyLA/6l90jk397EKCKks09NE1OEQIZFRf7DeMdy1yU0khaY+YNIQ0Q0Kp3KbDLEzCL5j6LFaxu5xmBgz05tEzDLQIVFenZALg8KrZyzFu9F7NCmGPctwSvMSW5WPUjCz
*/