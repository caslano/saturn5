
#ifndef BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< 
      typename Map
    , long order
    , long max_order
    >
struct next_order
    : if_< 
          is_void_< typename item_by_order<Map,order>::type >
        , next_order<Map,(order+1),max_order>
        , long_<order>
        >::type
{
};

template< 
      typename Map
    , long max_order
    >
struct next_order<Map,max_order,max_order>
    : long_<max_order>
{
};


template< typename Map, long order, long max_order >
struct m_iter
{
    typedef forward_iterator_tag category;
    typedef typename item_by_order<Map,order>::type type;
};

template< typename Map, long max_order >
struct m_iter<Map,max_order,max_order>
{
    typedef forward_iterator_tag category;
};


template< typename Map, long order, long max_order > 
struct next< m_iter<Map,order,max_order> >
{
    typedef m_iter<
          Map
        , next_order<Map,order+1,max_order>::value
        , max_order
        > type;
};

template< typename Map, long max_order > 
struct next< m_iter<Map,max_order,max_order> >
{
};

#else

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order;

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order_impl
    : if_< 
          is_void_< typename item_by_order<Map,order>::type >
        , next_order<Map,(order+1),max_order>
        , long_<order>
        >::type
    {
    };

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order
    : if_c<
          (order != max_order)
        , next_order_impl<Map,order,max_order>
        , long_<order>
        >::type
{
};


template<
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter;

struct m_iter_empty_base {};

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter_base
{
    typedef typename item_by_order<Map,order>::type type;
    
    typedef m_iter<
          Map
        , next_order<Map,order+1,max_order>::value
        , max_order
        > next;
};

template<
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter
  : if_c<
          (order == max_order)
        , m_iter_empty_base
        , m_iter_base<Map,order,max_order>
        >::type
{
    typedef forward_iterator_tag category;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
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
*/