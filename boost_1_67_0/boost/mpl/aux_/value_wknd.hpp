
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
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
*/