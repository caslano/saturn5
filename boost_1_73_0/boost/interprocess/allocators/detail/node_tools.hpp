//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP
#define BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {


template<class VoidPointer>
struct node_slist
{
   //This hook will be used to chain the individual nodes
    typedef typename bi::make_slist_base_hook
      <bi::void_pointer<VoidPointer>, bi::link_mode<bi::normal_link> >::type slist_hook_t;

   //A node object will hold node_t when it's not allocated
   struct node_t
      :  public slist_hook_t
   {};

   typedef typename bi::make_slist
      <node_t, bi::linear<true>, bi::base_hook<slist_hook_t> >::type node_slist_t;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP

/* node_tools.hpp
UICapjfpE5HiKr/Se0Q+bNc7YV3vh029H7TrnbDTaRxkpzFbtPX1K5JK8Vq3FDtH21I8jCxJTkiucy+FX3SybL3Cm+V9UveVV3hPLndJ5Huu8J5c7pHI667wlssBWy6EtVwOGLk02HIh7MilgXK5VuTy61HeHcR+GzVhjXq/Qb3PRk3Y6SD2sYMYL6g3jDqnFtr7fPOZTmlhkWjh9FFJ6yrirqvSK43gdbVEnLfSycRemwnC
*/