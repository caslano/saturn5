
#ifndef BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_eti_base_impl
{
    template< typename T > struct result_
        : T
    {
        typedef T type;
    };
};

template<> struct msvc_eti_base_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
        typedef result_ first;
        typedef result_ second;
        typedef result_ tag;
        enum { value = 0 };
    };
};

template< typename T > struct msvc_eti_base
    : msvc_eti_base_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // !BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_eti_base
    : T
{
#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304))
    msvc_eti_base();
#endif
    typedef T type;
};

#endif 

template<> struct msvc_eti_base<int>
{
    typedef msvc_eti_base type;
    typedef msvc_eti_base first;
    typedef msvc_eti_base second;
    typedef msvc_eti_base tag;
    enum { value = 0 };
};

}}}

#endif // BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

/* msvc_eti_base.hpp
NQ071rF90GtJXFEAoEzFFCurlzTmCtrzDNGHefxzUhTEGpGMkBqI48GDT/G5iSmC3WUfwNcj8AqYsaRD0Cl8UwoJLlw0Ht+Tp+KMYL/r13ZxRV4Br5lIR28crs4c/2FWedSgmGuPJBQ6MtKaB7FWttGv+nTXRHi66TaLSrC184y3VPap97R6ABTLLjtToyqyTIn5x1qF2dqLvsQ5pJJKZM7ejNc/122Asx8/bZ/SOCV42vl3DI3dzLQ/Nn0uPml1yDR1ADJZX59CDZSW4T0gyNh8iDI0G5h7JHh+Y1EalHzP8kj4UKfAKHuMOw/lCfuBx8LbgOtCtePtudOfDKkp4qgVOm0B1m9YLhlmb7wxAPnxnuBbwS5dc1QxDozXS7XSKYJwd27yFZ1kLhz6WXxgKlpn+VLjXgC5Q8yuZigSav/59O+2uUSgV/OOdqLxTgH9FJWnY4FP0Q54LDOAgmSeKSJjdslp50PqD8Vt4Pu7oUz7uP2H8nVEqHAwNmO7px7a8nDx9ETpKLV2beucQ1oANeiynFf4Uy5Wr2gyExkJb6UxHddB7eyt3k4n0AMX3a+sDjMNYR4B7myO6QWHaYD2fZh21LDfXx2MKuz+vr6XLt6wCJWpQg770wvbJ9ONdgLOTBlSbFN39N1skjcIyt+GavGWWiqpd9Jng2Dn3IqddA/aynqhYws9hz0GiJmy08632rWrGRsJt+NETKvG
*/