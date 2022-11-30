
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
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
*/