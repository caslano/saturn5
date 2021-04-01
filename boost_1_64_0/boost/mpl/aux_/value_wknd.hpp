
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
zEn7VitaKRe8YLQLhtQ+RREsYlDLsIvK77m0CjLa2WhUH4ukoxg0HudqWAHCnc8COw6gf8aVI/hR3uexVQoIB2fE87E8TwNz0ljoWEFtaOQlavY2qD9U/k7B/7OYL3t4ySJmMhi40vU42Vc7mp5NKcO31PgOENMeRVf0igEMARAZNe2p6qSxTw1ra/Qv2NQgURU5o5D+8OOkeLXIs0KqtibR4tLDO3PkWn4TBvP6bMYhRuNSyGqK+yR2G1CSmwDcyJiTxP8CTxh8K1+F5BcefmiKpZEzAD7E7XkVuu4kTF81tzPFI3VSdhAG4Uvrg6w8ttOIabcl6fl8IrFEH/3tI8y6hfIlSyBTcoHyZ3tNDvbGHFWxIL4DrcRN6MslqbIyaHKue6WJgPsg9wMs7TxiqfkvUFKH5rOoIPT3TbGfuTvuXedMkjDevlMh6rVju89+RtGpl0uHsziGlwXUCgqnAG8vKVqkaUwOjAI5cyjLLlv8tR+YXuFfE7bTy+FzEuzW959lClsg4krS2eOBY/XI6M1MU1oWXYApDaYvUGbB1Mle9xINL9qoZBX4ZQ==
*/