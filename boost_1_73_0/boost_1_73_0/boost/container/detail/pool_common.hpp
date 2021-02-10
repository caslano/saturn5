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
Sq0r9W48zpqa407GuczUODtI4ZR6+79drZDNltyCrDRoCY2iNph4G7YyZ4W5o0T4smo2nKnSvqeFgCIfyxoU5bwvh6mMqm4LFOJeLdtEQoXsmTY3JYUyaPtSbh8Foqx9oaKpBcKhLBiXSxTehkbktG7jWyEOKL3KreTPtOyeew5SICsYuDH48QA2RDFlw5WfzMJlAlfuYuEGyQrCz+AGq77ehR98Qm8wRK2B3lQ1VciiBratOKP5I/BfOumWk8xgulzML8MoSaezZXCRzr3gSzJLIy9w58kqjf2/PDiBwRsI5M4Y/c0ABpxtjBPgrXNy6kzwhfmXbhuuWaqoNk3HL/pLIUQ8g8C99KwX4KyPICsb8Q9wKq51iW1AKUqJli5QjopVlDPBxHVbNF4FYRT7sfUbExlvcgpnhkbn0fKj1QFmEhd+ojds1+BViQbi6KPnudnApbgGxb7T0fsW/5MXTxd+lPhhYAUSnSUys2UMERl9QBb2OIE13cpdN8Zvnd9fOxPHsiKCbSZd3T02H5/XxblBWBeRidzcaqoc8Atc6ethiUwKQTsotB5uraZC81urqmWGxjGIpJMRg4dJTYQqaH1EBUqBi+8OayMk9W9DlT6A96W6datvASc4pmY60NTrwn9eqOHJCOnbJkP/
*/