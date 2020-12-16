
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
BU8NT6bM5SLTT18ewJfwSXT7eufT7imkL53El1n0pbP4Ihxzu8WX6fQlQXyZSl884sskKB6vO6CNUobN5o3/Cz3Ua2ioSRgqm6qs540fLNEb/3g4Bt/NzDl43KiEJFOpBvY1LrNUA6m1ddt4C06k40T14YOEnRAHXEIuYNMNvMrSDaSKpbJiR6oYWgVKJD3P9D2snMCx90+/1BGshI4g2stQ2rPXWjqC1N4w2d7z24UsNnw+rbiT/f6pc1iNc1hNXuV2hUblVs85kZpPKKgWjjr+RolZdNiQQLfUDWd6IouTCCdl8c/cvy0+0xcJP0+ohXzPCQPw3VrRbyeflLr7fuCTcnh/+n74lJh0kMh3gxU9GUQXdWCZvCDCzzMGdUrXoSe+4MNgXVPHuaPMYq42H9zCoo8MJU6HWm431GMy6cBth6V/pvn9Y++W/smT6MzAvHKedE96QWOPW0Dg+5xWvEyt61TrVJYY4Imk3MpYAQR8tz8rbhq33IYwePbxwmKtEbyL6SI0J9ElaH8f9AVhNpeAhxmpwKwzxTjiM4nX7fcU7d9EOM/i//RE6wlMn6LlOdyy+dvzefO2AO/Xae0ax0ejpb0r6+VdDRQbrfhEOvUJuQ1wBkPpWZSLBOEMZ6IrsthJ904W/8yJLJ6YFAmvZULXxwGPLr1Dku+H6Tom2v/H/a37q1h0X/P+Lmova7a++cQDjf2DlMbR30uLWvH/cW+T+fwezSXo6HhS+5gbJtAytGvcbFEPGlLbkXmk/thwcFZUmIkpmqMyL3Cl+e0rSjoDacpUt11/ps/dMSKyaRZjiOpuUHXDBehUa+bXYzqqc2Droca5UYKWNfOY+Xxe1Gh+xS3GtdHj/CP4RbUScBpzBc/+YoZ1pF8R/bLnuzg/R+XPj8lP4Px+Kn9hTL6b8xNV/uKY/ETOr1kq82+MyW/H+ZtU/pKY/Pac/6DKvzUm38P5i1T+nTH5HeT8Vf7SmPwkOX+Vvywmv6Ocv8pfGZPvlfNX+Q/H5HeS879H5q+Kye8s56/yV8fkJ8v5q/w1Mfk+OX+VvzYmv4ucv8pfF5PfVc5f5a+Pye8m56/yN8bk++X8Vf7WmPwUOf+7Zf72mPzucv4qf2dMfg85f5W/OyY/Vc5f5VfG5B8l56/y99jz7fKPWyD/WPJCmk8hKKPqE3nDG6kbqI0n0IZfmN9khBEju8JdIHIIL5kwofWUd/LRbxUxaoLACHOBjjhhwJZEkS9Ic+O8ZpqADzvBvkBT5SloEAE1I8RWegn2vn4Y3v/aWExtsGykCL3UsSMLWy9Lw+B6V/hzRS/5upfwryMFdYwloytsR5P1Fd4cUWGqVWGScAGUInoOe5aLfwQf3C354Lj7sr2+EpcggaCJP2YJsX7Yc1C5+wZ6Rg7blrxoOfya8Hurtsy75DvBeW35s/x/LhH6E37tj0hdy6xa8ABWOg6fRNQeNoexh/aK+TbLK4VNtZsWBBWas/9aAvsvXgJn0CP8EgYnh3PNi2+ijFyPjHb4jGts7nSSDwxSfh7HgOdYv2BkXg4lp7D/wOypw4NJWxIH3cvSS3IFkmh6ptVof7gvex2twIUQJ7nzp+ONz/X4XIfPtfhcg8/V+FyFz4fxuRKfdfhcis9b8bkEnzficzE+l+FzKz6343MnPnfjsxKfe/BZhc9qfJr4rMXnoCrx6canB59efPrw6cdnKj7H4HMkPofjcyg+HfgcgM9MfGbgM70Ko8XnXHwW4XM+PhficzE+l+CzYZ/4rMdn3T47QplacWamO2vr0eu/2tl3a/nGfo66f7J334ExZA8AxzeNIJEgiL6I3kJ0oiZqEJLoRMpGljTJbkQX4YhwuONwuFM=
*/