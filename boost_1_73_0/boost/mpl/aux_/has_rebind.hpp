
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
#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
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

#   if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
template< typename T >
struct has_rebind
{
    static has_rebind_tag<T>* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(has_rebind_tag<int>() | get()) == sizeof(yes_tag)
        );
};
#   else // __BORLANDC__
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
#   endif // __BORLANDC__

#endif

}}}

#endif // BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

/* has_rebind.hpp
P+f5WQbKNgf1QeyltPN+lnF9oNmGBjdbXfDMRF2I26vf9hMN8Zi9L68LGfU/yytpUkdlO2jHHdJ0dcHlBXXkrsO2tP2wRt4c9iG1Lsh4zFfGe/G9fhzby4ty/Y7xD0pdr6Tdq2h12CK/5clNTnm1vmQwjmxf+/wPMv8A0o5/rtWJNK2u+YWbRqh1swPj7iV4E//+c11bsFbfpGxPO9Qr47IJtjbdzzOuS3vr8g9DiHJsEfso
*/