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
pH6RsDKxwE5Mqzugz78I12j9fwdyCu44Z6B//ZMEG693A0XHU+7cH4+94BC0Qb+Rv+Sv/fszIdDg8L5MReNzznNijKF05p8uBEbnJVZacTkOlORXz/HL49e9c9amTMQoT2iDgk+Tm2xTNSN3awzp6yfJ7/5CBYXhIdHAlSQFuE/xArK+5Fpa1g3h+sQsRvQiuAvWWpl9rcz8jOvBdbEM1HOYDJzE82iUCgdujGhNrQR0JGFekbfxgoG6piBlR+duqlAgvALs6VNsKcrEAV4J2EDpbXyYGkGwaqMKCGg7jHcdQaq1Ixs2VnYfue3Ogdh95UnOXPqAHfjSzR/5c/+XfqawhTqdWoDeM6TmZMZWI7YCG3TiCbBTPmuuPRXWnBVj9Vxn2Hc8LKxe8nNiAylhA2QU9Ot/L4Nnhv7xoLGTagCINE/kNfz6H0Y6I2V/orsvpnah77sfSbhcxGVJLth/YY8wC43sobvh+wR27++jvaNkQyGPPKcF4v6mhA2O+BvQcbCOONp7PEBoFdheg7JUsylvFuM8k8Yuo0AGDVljXQzKOdm/F1oltkKGdg==
*/