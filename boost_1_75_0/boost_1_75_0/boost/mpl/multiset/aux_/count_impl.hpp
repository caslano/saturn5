
#ifndef BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include <boost/mpl/if.hpp>
#   include <boost/type_traits/is_reference.hpp>
#endif

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {
template< typename S, typename U >
struct multiset_count_impl
    : int_< sizeof(S::key_count(BOOST_MPL_AUX_STATIC_CAST(U*,0))) - 1 >
{
};

template< typename S, typename U >
struct multiset_count_ref_impl
{
    typedef U (* u_)();
    typedef int_< sizeof(S::ref_key_count(BOOST_MPL_AUX_STATIC_CAST(u_,0))) - 1 > type_;
    BOOST_STATIC_CONSTANT(int, value = type_::value);
    typedef type_ type;
};
}

template<>
struct count_impl< aux::multiset_tag >
{
    template< typename Set, typename Key > struct apply
        : if_< 
              is_reference<Key>
            , aux::multiset_count_ref_impl<Set,Key>
            , aux::multiset_count_impl<Set,Key>
            >::type
    {
    };
};

#else

template<>
struct count_impl< aux::multiset_tag >
{
    template< typename Set, typename Key > struct apply
    {
        enum { msvc71_wknd_ = sizeof(Set::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*,0))) - 1 };
        typedef int_< msvc71_wknd_ > type;
        BOOST_STATIC_CONSTANT(int, value = msvc71_wknd_);
    };
};

#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

}}

#endif // BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED

/* count_impl.hpp
X5p6lG0SOvK+SrbIRg5XONNb3pXIDxk5+hx87hmzsI7lFCzbFiFC/RIcXtYtwVQk2nauQo9qI8saNLuz2PvI75q9BH0cbDD5gqJspaT4EUsh4/hUuaWixIKR8zfG1qZHYnR27GZE2SBODlouRnYihci7Mide4a+z3r9hIJlN4z0BEfKqpOzPIFluKFea7DsIJ4vim5nK7jrGES5FMAdGoYnzZbw9y6tTqE31pOM0cV08XpgUXZFkO+8hUynheXSR6aISnW/VPFFW40YVzXCSe4k41/XHFn5gEO/0sc5sHvyaurMuvelsKdJiOjW24m1JhdOOxkdH+y19ThiEKxuI16FZP7oILFUJL1fuO1VcUjllsrFs6Nf0T2pO+WsMXevaCliit22PAmjiNc0GNb9lGQm4FDFs29locSu0AHDvMVjuh8fsCfw+i2vmFwpK/mL8VH/3M++UWyp8dBwFdL28P3JXgcJYfPldKSojgrF5rOHhdMQhiDEHCySxTrlgQdbI3B9bfuFTaNOlehS8N8v0nHX302xCvOdcJ3ijLWJbdeRWg3p3ia5nwTU/Y/ZtJwEKGSKeUHlKgCdkgvDqz9TonV0/yt/90JgxcjAE9QFxknU9Bri/A8TdWTQxSzJS1bjBbZABmarKl6trc6tVcE+m2c/zn/L2jRebOw87pkVlWtOfONN1R0/xqFh8PYVsYvxi9Xu/GiRQ3u/ajL5o
*/