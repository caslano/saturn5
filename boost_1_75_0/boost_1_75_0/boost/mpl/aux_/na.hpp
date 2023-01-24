
#ifndef BOOST_MPL_AUX_NA_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_fwd.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

template< typename T >
struct is_na
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_na<na>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_na
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_na<na>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename T, typename U > struct if_na
{
    typedef T type;
};

template< typename U > struct if_na<na,U>
{
    typedef U type;
};
#else
template< typename T > struct if_na_impl
{
    template< typename U > struct apply
    {
        typedef T type;
    };
};

template<> struct if_na_impl<na>
{
    template< typename U > struct apply
    {
        typedef U type;
    };
};

template< typename T, typename U > struct if_na
    : if_na_impl<T>::template apply<U>
{
};
#endif

}}

#endif // BOOST_MPL_AUX_NA_HPP_INCLUDED

/* na.hpp
V3ZUpkNeQHYbuLAjgC/uRzVkIsFr/iJsxNntam0rZDsqdHOTAE5C2SRNpMJMsU+zU8pJQf7aZT0QkP3LHnRxMrdCQuHS/10H7Day70kl6sZ2olcbPPsJ1MWT3eLwdsUsTs+DmefgrayS70U8eazF1XkEuDdSSPrxBuxH9TIiCboq+pPzTrqJ/0jmeChf1zARRwmExybkwVelB5g0lb7/Bxf4B9OVZw7CqN0fR+XrZ7TaY7AEMYNn2EVxMC2T/fbd25CjtMT7M8OBUS8hzD4vfY+OXlQ6SMhjsM4iz6+dnDwms3D2OD9tMyZH4w3H1/JTmP8jdYzM8UY6GV6M3FbLk5o9nb3Kn4jv0cFjlvMUXGHsNWR4K8NEJI1W1YJbvRL89pkEiPBtcm+z5QaHeMREDBV+TL9DonvBp964vqx4ot0M0UImnIKblk+yWCTw/TQDPWHTMHN6BdPa0ad3mFhHzGxN/nNTT4Qa6p3p18H2HrhDGagSCu9pdjBUzRtYam0Nrp+MEzwRmniFiGMBhO5H94YBSNc+Ywa9mHlePbewGOm6Gxsbqz4UFRVplkpzcZVqLLtYN+4zLRb3dd+8fdG/t9dNBhBfWYHhHLc0VrZ7duENVBkDgs8HKateYf88pXdqO70Ow0a9O6akouCjr83/x8jT+Vh1pmhovOpp1I/v6qJunMTmoU74slVUbtS/qonywWIlvel20U3dXnsh
*/