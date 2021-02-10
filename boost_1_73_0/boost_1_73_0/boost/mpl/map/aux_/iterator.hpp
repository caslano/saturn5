
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
lQxE09VnCcsr7YEeYwPQNriuwUbOEZC6RPeB1EY9BLYK9+G61l2RKFxtFuRLiTK0Dsmi6K/gu4jwG4E9VoXQ0M52CcLIBUa7ojPReod/W+20mW86/QiPbYBnBE9mxcuikzweBaHsYiFNEckzzg8G42k+nGQHHetk/JDzi0+QphvmtKXS0M1LB7IONNJ7SJfw3mlq97UCwRe5ZMMMnS7pVskgkGXoeMnDjhIq6eER0cCer2zYY+Jpk0sE1EWwytY9RuP4bs2u4+0IJWxgfcjgv6S3V2udXsugrclehrm4na2LwWz9+9fwc8RXlTodXSbsBwlP+3NSkYFqXc0PZjcP0+H4PmF9pbCh8CE/3JLTRBlUkfk7YpP2a/2ECQ2P4Dstgr8K5Luf8R9QSwMECgAAAAgALWdKUoJ5SPTPAQAA5AIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MjBVVAUAAbZIJGBVUl1v4jAQfLeU/7BqVfXhhBzo9XTiTNSUhhKVEq4Eruh0D8ZZSq5JjGxDRX99HfPVvsTx7uzs7I6ZQW0E1xgQllcLaY9X3L5JlemAxI/hiIzD8cB9IJykfRgk9/GQMHpCMborJOfkHMaoNqgaOs+QMIWrYmsB2gVFmQXkE8dT
*/