
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