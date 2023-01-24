
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
Iih/szaXAN6LrE6iETGc2m7VBXyCjpxzAUcJTiqfl5KbT9N87AQISDfocnUnds9+7lPcufN345v0rXvVaW0vLMf/ofe5uzHptxBRAv5NK1ecdp+Z8BaZ5cumCyclHCLKY6ejj+3ALwcsyiK6yNc+eyW4fwqPEep+kJmniyo48/zCNifqTRglEPn+0L1Wrd8FxMYuTSor+2wusTwx4fN2WUy4nVNVT7+Q/7ZK6Cc906LanaaPSodN+URtWXuzntab2QHSaTaAmVduYmO37rW2m+4Id2wocZwOG/s3tZHtVlPjvO+NS9tQzqfF16AVPOvN8mr/OXGK9+TaGNDTDQxxmvL7Z63YEFRI6HkHnSf+N2nKVpSK7gKfi0K9++eRokPsFOynLAkJhWfEuSJsHawDQduSRZ+ijaNI/hwew2nkb18L+D08FlCO+vEV5+/hsYgCWvo9Mmmc3iGjGTtiUTTOV/fJL5ekuNUQvFOxOC6Xqa+jaatgifeubThrATb7FfrM8bQ7N2sBBJe+nr8dwr5nDWI46Vm/SsrsZr2xib12RejtrIQr5mF6jtXwdayjuKLPDcqgb7aV5P88V6/ceL6ji++N960boEvzLcBCYNksbZ1LdJ9HYHk8C6N8Y6Tm9/CYrorl0p/DY+yVfw2PRbR1run/Hh7jP0c5x/8lbflbpz+Fx4wh3WtGkOHfw2PrMPrb/uPHY8WFzGqgAXgQ
*/