
#ifndef BOOST_MPL_MAP_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/ptr_to_ref.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/pair.hpp>
#   include <boost/mpl/void.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#endif

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Map, typename Key >
struct m_at
{
    typedef aux::type_wrapper<Key> key_;
    typedef __typeof__( BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY(
          Map
        , BOOST_MPL_AUX_STATIC_CAST(key_*, 0)
        ) ) type;
};

template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
        : aux::wrapped_type< typename m_at<
              Map
            , Key
            >::type >
    {
    };
};

// agurt 31/jan/04: two-step implementation for the sake of GCC 3.x
template< typename Map, long order > 
struct item_by_order_impl
{
    typedef __typeof__( BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER(
          Map 
        , BOOST_MPL_AUX_STATIC_CAST(long_<order>*, 0)
        ) ) type;
};

template< typename Map, long order >
struct item_by_order
    : aux::wrapped_type<
          typename item_by_order_impl<Map,order>::type
        >
{
};

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Map, long n > struct m_at
{
    typedef void_ type;
};

#   else

template< long n > struct m_at_impl
{
    template< typename Map > struct result_
    {
        typedef void_ type;
    };
};

template< typename Map, long n > struct m_at
{
    typedef typename m_at_impl<n>::result_<Map>::type type;
};

#   endif


template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
    {
        typedef typename m_at< Map, (x_order_impl<Map,Key>::value - 2) >::type item_;       
        typedef typename eval_if<
              is_void_<item_>
            , void_
            , second<item_>
            >::type type;
    };
};

template< typename Map, long order > struct is_item_masked
{
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
              Map
            , BOOST_MPL_AUX_STATIC_CAST(long_<order>*, 0)
            ) ) == sizeof(aux::yes_tag)
        );
};

template< typename Map, long order > struct item_by_order
{    
    typedef typename eval_if_c< 
          is_item_masked<Map,order>::value
        , void_
        , m_at<Map,(order - 2)>
        >::type type;
};

#endif

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
j3K2sgPyh/2Z0WWgBHHwi47kAuByMqiI5DrZWor8WlimzEEKnPwIaqd9+MZ2BeZvmnny0MphZTRhw1i3zvIwhDi7bZ+E+zwmnbWeodh4kKexoXqtaf76pToUFD+hs+QxNn94eMw+j0o61oXg/9yJ8P7TpXCrt4xkw/i/39H+f0fCeXj+aRGd618X0TVJbvTUnQ095JfjDDWf25wxxWQzxEB3c26kfjJ8qmbITHBhtT/Zpm5rYAxV1aKlZo5UqaleGZIPo1pAVdV4KYj+KbZLbJpOTJPXFKdWahIT49mM1SzkIboPbyXfztPLxtjZxg12Th2N0Ht5db587361NpLKz+PB/5gIrjqEr7dedQCri22D+SqjhstKB79iPhdx5N757T5qeLdaWwvhdvclIJNORMBGc0fEnStf0Ea69qUG4a9HniWx9NG2aHqkN1EtX+jXWLYQb3sYPexvThMqVLLF9BKR6JGHy78DtRGXktdzVdTsDRKUOzmfX56FHh08Ny7zWCewB6NFfEFmMV3+bQ6995tWF01ya48+Zj6PxcF6r4jsbZrGg9xlIIAOQOXhxMRXzdkIVL36keiPv4eiQVlLYj4LjHANX3wIwgQ+vQk6k5wrg5xeRNGtOfQBeXkpPwbpCFyPnrc7LWQ5UD9AX43xfz2kbaV0s/R68L3luCzSuFFJsmm4gbxYI18l9RR2ZVyh9LTd0XnfcnTU+25G
*/