//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP
#define BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class VoidPointer>
struct node_slist
{
   //This hook will be used to chain the individual nodes
    typedef typename bi::make_slist_base_hook
      <bi::void_pointer<VoidPointer>, bi::link_mode<bi::normal_link> >::type slist_hook_t;

   //A node object will hold node_t when it's not allocated
   typedef slist_hook_t node_t;

   typedef typename bi::make_slist
      <node_t, bi::linear<true>, bi::cache_last<true>, bi::base_hook<slist_hook_t> >::type node_slist_t;
};

template<class T>
struct is_stateless_segment_manager
{
   static const bool value = false;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

/* pool_common.hpp
9kF/x6LP3+r2y6tLd9vwfQaZ12VE4thtJKTDnI38esN6Ftlg8Q513RP9z+pW873l4c9iaYvxKO+97K/u/0FzjBysXVVnF0nEmPDw0DpKXmFb3JVv+IMAQK0p192rc+2S6/Day21wDlH+r0Cjoprq53K1nZvFLfxNzUx/JwgZPQIovggFwyg7xUHxFGUcqhZGYGexgh4q9dKJloTT4lkZO5ZS62Xh9BpGtOsh5r/GTuqXdcPmHV6iJ9WlomwdElgScG7c7L+PFiY9nE6+J6o+z9viZCr6gSrFmIrVMibBO9KZh/wg5I2fuuBfMlas1Ilk7LeJNmwcVZ/1Yz8u/X2pPlLElB5cQX7s0uCbB9nxGcHM5E268kRbWzvNKS2Sprw+tpkWue070sWkzSQfBLwvd3OcopCyDbZP1iDXgmLWwAyweW6W9IAreNY1MKPDCJSDI1JqU6fPrZKzlZqliORzLcFB3TMzOF1mA8DotBnl8Q5vEQpJiPJ+skLwRzuGyTiM+GMYnWJb2PkjM0BZoIP+N67gkE083m1MjY+1Ly+XQgX4dz0TYHAEkVLzfQ==
*/