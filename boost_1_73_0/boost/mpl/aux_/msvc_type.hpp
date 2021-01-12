
#ifndef BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_type_impl
{
    template< typename T > struct result_
    {
        typedef typename T::type type;
    };
};

template<> struct msvc_type_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_type
    : msvc_type_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_type 
{
    typedef typename T::type type;
};

template<> struct msvc_type<int>
{
    typedef int type;
};

#endif

}}}

#endif // BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

/* msvc_type.hpp
6vM+NuPTPJbPhP3zPPtxEedwCRdzKd/k6rCeN1kmuq5mba5jM77DtnyXnbiex/N9ducHPI8bmMwPOZwfcRw/4TXcxNnczIf597Be11bhN3DZv4mrwr7C3HDe2Ga+yvyONbiddfk9m3AHj+QuduRuHs+feTL3ciALl1RvsCgnshiv4368mfvzNpbkYzyAz7IUV7E017MMv2ZZ7uKBLBtdh7MyD+JxrMBurMj+PJhJrMKLeQgv
*/