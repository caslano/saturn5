
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