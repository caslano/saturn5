
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
+zkMUF6gbFZ5glYkcVLM9i0retZsWhYcfZsUrGQqFyWkQoLKEJLppMg5UwiB44DEr1MKUPXIushjPpUFJAKr8jcFCSrkipwYJQCj/ALLRT4TVlU6E8gruJSiHAErJLJkBhSJoliQ5pLsAselENVElBXCS1aZDJhiOraesXq1t4x7mRcF5GWlaCLg5EKQpJmtxMvVPH9NdUUqymmFhZWUi4IKy4QelIK8ZP2lAWEC11WEiRRxgeN5puRCoZKNTJ9ZVrM5ryK8rYHM6wQZxV3jZHeOflkP7RdpgK7jGEJtd8+tZ/+ImKz77liGuh58yLkUlUhV8/h4YId7zo71RpQKS9UczibYA4XflJ2pcfE78IzJClU/r0Sz0wm7TXdlfILlSGU98No71tnZWfOAotD3dYV6i9BEUzHuN7QO64+NXShFybHfcBs71o41zIhT+qMa1vXRRoRvRFWJ7CWyOcjrKAdCytmVqjwg0u53IfU2kDKISXBLCjewzsFqIQyMUG5VgsxHmbpBCd6/KgFeeq8enRr87dTgralhEymNgNzLEVVYIi0IJVJ3U79pmEDr0gPqwvd08m/zkhXFbJcyNyhu1rO34pjylXdQfFuz+1tQ7D8+ioPtKPbXKL6O9KaGf2BBf1/Th1s3vb8SxFsx
*/