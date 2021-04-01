
#ifndef BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED

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
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/next.hpp>
#   include <boost/type_traits/is_same.hpp>
#endif


namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

template< typename T, typename Base >
struct ms_item
{
    typedef aux::multiset_tag tag;

    template< typename U > struct prior_count
    {
        enum { msvc70_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(U*,0))) };
        typedef int_< msvc70_wknd_ > count_;
        typedef typename eval_if< is_same<T,U>, next<count_>, count_ >::type c_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
        typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value>::type type;
#else
        typedef char (&type)[BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value];
#endif
    };

    template< typename U > struct prior_ref_count
    {
        typedef U (* u_)();
        enum { msvc70_wknd_ = sizeof(Base::ref_key_count(BOOST_MPL_AUX_STATIC_CAST(u_,0))) }; 
        typedef int_< msvc70_wknd_ > count_;
        typedef typename eval_if< is_same<T,U>, next<count_>, count_ >::type c_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
        typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value>::type type;
#else
        typedef char (&type)[BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value];
#endif
    };

    template< typename U >
    static typename prior_count<U>::type key_count(U*);

    template< typename U >
    static typename prior_ref_count<U>::type ref_key_count(U (*)());
};

#else // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {
template< typename U, typename Base >
struct prior_key_count
{
    enum { msvc71_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<U>*,0))) }; 
    typedef int_< msvc71_wknd_ > count_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag< BOOST_MPL_AUX_VALUE_WKND(count_)::value >::type type;
#else
    typedef char (&type)[count_::value];
#endif
};
}

template< typename T, typename Base >
struct ms_item
{
    typedef aux::multiset_tag tag;

    enum { msvc71_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*,0))) + 1 };
    typedef int_< msvc71_wknd_ > count_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    static 
    typename aux::weighted_tag< BOOST_MPL_AUX_VALUE_WKND(count_)::value >::type
        key_count(aux::type_wrapper<T>*);
#else
    static char (& key_count(aux::type_wrapper<T>*) )[count_::value];
#endif

    template< typename U >
    static typename aux::prior_key_count<U,Base>::type key_count(aux::type_wrapper<U>*);
};

#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

}}

#endif // BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED

/* item.hpp
hbnYo08DXtkoLxwCgIyuZJ3iuaMxJ/QJ/lsag/xCWkOlPCg0ZuNrko5lNRbnAD+DX1t9lz4tawup6WnmCru3bIKF8mH8DvY3ygaOXyIc8VSBZYFFSSmKC/mVAbsqNf1rty8HMsfGhdMFILeXxgcB+pfEydwK+83Hes7adqZeIdDeLn1p77sWbTAzBCyzH2DJ42g1EUIC9CX8eUvejCgs3Fm2saJU6pXFTbPWJRCUssNCzwKW6q++4MmGEMh8g9voPFgGT61ybmi3xZnCu6d/bh9zyxglNnrsiJtwPXznWYCa97tJP5UQ3niAGezJDBcxk69Wl50xbIhSya4X9aX08UhkMu97c9v3Q+2HkehWQ+K1FFlyq34oCO7oM/3Y7UpxKc17EMh2OyifWRacNYQdovIr7Hw1Wk6ZCP78xwh2qf802gjwTgEoYL7Y8L3BbOa7OY+XxlzA8C6jQDyEcfpSXrYIxv4CL7/po1b4iVp+H7/TxI+NF8CaCP+j+261JCgz2MZWianY1ExWC/OtDgHzk3bLqvOjQ/18q9k1pYLbrsXbw9jDKbcJCoiykA==
*/