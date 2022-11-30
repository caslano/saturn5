
#ifndef BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(BOOST_INTEL_CXX_VERSION)
#   include <boost/mpl/has_xxx.hpp>
#elif BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   include <boost/mpl/has_xxx.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/msvc_is_class.hpp>
#elif BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#   include <boost/type_traits/is_class.hpp>
#else
#   include <boost/mpl/aux_/type_wrapper.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#endif

namespace boost { namespace mpl { namespace aux {

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(BOOST_INTEL_CXX_VERSION)

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_rebind, rebind, false)

#elif BOOST_WORKAROUND(BOOST_MSVC, < 1300)

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_rebind_impl, rebind, false)

template< typename T >
struct has_rebind
    : if_< 
          msvc_is_class<T>
        , has_rebind_impl<T>
        , bool_<false>
        >::type
{
};

#else // the rest

template< typename T > struct has_rebind_tag {};
no_tag operator|(has_rebind_tag<int>, void const volatile*);

#   if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
template< typename T >
struct has_rebind
{
    static has_rebind_tag<T>* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(has_rebind_tag<int>() | get()) == sizeof(yes_tag)
        );
};
#   else // BOOST_BORLANDC
template< typename T >
struct has_rebind_impl
{
    static T* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(has_rebind_tag<int>() | get()) == sizeof(yes_tag)
        );
};

template< typename T >
struct has_rebind
    : if_< 
          is_class<T>
        , has_rebind_impl<T>
        , bool_<false>
        >::type
{
};
#   endif // BOOST_BORLANDC

#endif

}}}

#endif // BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

/* has_rebind.hpp
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
*/