
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
Z7fby5GnEVCG9PFcThxszi2YXNVFSgwsLBFSLARpxxQyrUrgEhqwGo2qdULgmCPmyHYEG7SXhXAyW7RJsyCTFsPMy62t6MBuGWfIbU0eZ55L5VDHmB3eQOyyOxQZCpXwAv64vWnyPwVuLZaVhd+k2EDFbU4aC25JPFgFdVWhJies9RInqiy5THdkfKl6qrZVbU/pScikqFOkyvd65S6eixIxdnT/NGeFWjFXWAe7Xx7kdl5nRKCV9+o0rLUgkZKwZkpj0xqwE6JraYiEM2tq6f9nDJIUf9iUBRA40wgP+gMfUCYqFXI19Wub9S78D2S2D703PXOmdFiaqe9KQNms1+u9b9R9pVfMd6ydDgcdXirq9xtBpkk/VWtZKJ46ee4ImVIgkYmEO6LNDsQ5NzlYauKpb3Iejsb+LDlPB2cpLnEySHg4GU7CcHCGfBIG6fl4MgwyPrkYDwdJdrY8Hw6zkAfjZLIcXQzHI+TLizBmzmkbkf0rZLxrTAMl3yT7waKUA78TVeui0+Qo+FBpzKjDZUI7k4E/69gcfbl7XFzfR0eu4e/vHhbM5RozOt5F38dqSDGHysFjHb2Y7dC65/ZtTGNrm8tl5lFHFnD0+HA5v35ghVg6uIzGDjeCKPerAhxoF7R52E03/BM/OX/h
*/