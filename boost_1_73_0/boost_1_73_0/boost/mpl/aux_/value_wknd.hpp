
#ifndef BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    || defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

#   include <boost/mpl/int.hpp>

namespace boost { namespace mpl { namespace aux {
template< typename C_ > struct value_wknd
    : C_
{
};

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct value_wknd<int>
    : int_<1>
{
    using int_<1>::value;
};
#endif
}}}


#if !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
#   define BOOST_MPL_AUX_VALUE_WKND(C) \
    ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::aux::value_wknd< C > \
/**/
#    define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) BOOST_MPL_AUX_VALUE_WKND(C)
#else
#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) \
    ::boost::mpl::aux::value_wknd< C > \
/**/
#endif

#else // BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) C

#endif

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_STATIC_CAST(T, C::value) \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_VALUE_WKND(C)::value \
/**/
#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > struct value_type_wknd
{
    typedef typename T::value_type type;
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<> struct value_type_wknd<int>
{
    typedef int type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

/* value_wknd.hpp
Ml2WellqKWyhFeN8WRcWuW4si/1tjtjv0rIX7AXMsF5gzU2RIotrrMoVbUiFFaC0zFF+OvVWaLzuZD/cD+EwOIDJFZiludWNksjOhcUIkgZfQ3ACY72AgyAMIDyKjk6iIID3HxI20MqisnyE6s7mEZw8IcmqomiLD9avSlEoNlrzj2DfPwiO3gZBEDJWY1rUKF0ljt2aZPgsywM6eHL1U9wOn+X2DmQuaoP2tDFcGFkUjNEhHaXQKbtWsJV2UBYuSSetbD9oi2kF77Pc2ooCNp9xhsI2NVJ/ilSxrqmxv0UpkDgt+mw0mJ+NRqeo5jez/ZvkD37soEHy53T4DehydxFxRco5lfqswroE/uEyPB5H0UioO2eF03K9eD2YnA9nwwQ4wsu0QPDGiKkBAW1KcNYq0YMig91S7m7Cdtdhu3t7e6AoqrEZP/b23r0kEtuzIVbinlxN6irqJLUYauSNQVgWNgdyMOTaWHC7QJMq8JW/Ifa7aFpJfX8vVNppGPn+4/+P/z1+3jfY+gX4A+xcTGbJ5TTacRmmk2uqaAnezj+quZ/L7njz71+qAzbW6hBT/I3zVC9VqUXaIk1dzjHLHOUFtojs/DG35I8WoA5VWhmk5KlDPOAjqv2JKC3X/W+d8RHrIltBO2Yis1Sp
*/