
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
6vjhGGmCBx/HjI9l82dSx+lVLkUCmq90L3tzEH+X6/CWdguu4n+w9Dy+E7VZH5T2AMc0RYiF9pJr3zMe00FGSJTVUm5uq0wFfU1Ln8OokOkk4lV+E4+aWjGasTl0yJWfVaH8GNOu9fjccsBxQ0axBwpwFKa6+zjNTiNqg/xqRqOHEltbNycaU6kZ0lTHXqJEJn4Ndfq1EjbzlBReQBwM1QtpU/3DnsAjZmiDCVImQMazpegWe9vdhiS2/Zum5IwzYhw/5GVeXtNhoZYBVOahsu48wyq+sQDexVeevG5os/Fl1mOWtxrn2sd27LTPlcAx6qV2WTRP0+kT5sXs3gIi9BI1fGU7h+qhaKg2Xho46V5MF1n1eJkJoSklXtcxNGgpx449t9GzxzwbPQbMmTZ9c8Cg2CRElXAdR+j/fSKQpeDuxKYJqZWpt+CjbcEbl1Aa00J1kraV3ESa5tHyP5W+67hy6jQYNu6BySSgMxh/P2HGAtyT9gsnLZiC+0BDmkRUQ5Pv/D8/nhRTgxC8cTqW9I9uN9AX+juDhIbJTSLrhj7ffqLUdmEpDijzLQ==
*/