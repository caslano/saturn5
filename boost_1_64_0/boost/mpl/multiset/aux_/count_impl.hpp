
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
RKJHNwDp5uEcZYLDQb13BULn/dYz7Uz3PxG6whIq7S8F3T3AYkdtZtkgh8Swihr5E4R2FNfTGtHupl5O8btws/cYfMSByuTgASVWUR/k2Y/Bdz7vkeL+2TPoWuZmzg6M6WfZfpr+lZwiTPHkAJtP36iTwxflv1QlxjzBAX6tSqDg4uB+B7fnuib2uTy5AqZktwPoiXPwV7q9YGzvnGbqeSOptliqjk0rYaImMbggXZA5GplTSayNpfn2GdaZfmEXYzMnqwWskRQo2hEZdllLwjc1oFU177pQV77ORHU+yz5XHkthMmhqWfq9AvefaHUW4BWy/H4R68Ohcs9EuCoSxjH2KGO+G1sjGwOfTkUDubVvQXPtc88MNNigs5cr626/QV+LCLX2T9JkU7P0i/F3TChPGS+h8ib0KZ4fQf1V3FboH0TfSeSvm+ZdzHyFnOFAFEqT9RAulJoCUWuF8lKM/qHyCxv7gqPjNvAETBHKBQEu90cJXe0Q4tm802U6UgEftT0zN8f/7w819SkL3Ubjza32apOcLBp0hTtkkOSfe9XcvGN48xo53s6Shw==
*/