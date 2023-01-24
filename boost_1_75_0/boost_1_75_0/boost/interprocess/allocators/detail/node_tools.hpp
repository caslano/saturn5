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
/8D0Am1JTzetL/u6JHm3crjybRvOOvvb/iBRtKMlVbs02iSX1Oj9muCBsQF5VxKXchsS+wE8yhurmQ9OpA4k6SLKg4mJZxSYWvjqVRg5UqVopejWJb3+0SYGff7oTNT0r8zy1vFfuw0aJ7PnVKuNBlGo0wzf3JsrdCcxtgGVVcTwjUQyAs8A3gRCQQ8BAo46yJmpm0CslOsuXEjpo3A5IG34y0aBWE3FMUnRuXm3zIlyiW5Zxw+ugnOjT582wKcUJ5v7RgXntvF4nsCbKNVHbjzPPHe5MkAOa3j7ErxE1Zs+LmFJKGhnbCpm5/ED55i4F8dr4PGP1Yym10Xnjg9GB4lnTP1fGyFKMqetVHUyhVc8hNtK+9zZT6H9UWyk4hDYkVk8a0I47ViqhE2I/MxVzoyR/0di751hwzl6ldghzZ8VUF1wGEm8nvIyg2NeVNDhRW3ZlyE++KumHKl5L8KvayKfHbkJv059AIgFmZQV3+1y/+U88mlbk/8OQHHYgn6hrPcxzPeN689dlr6DrTpHaQ4+s+xQ0fH3xG+O7x2QtDm0hmLPc2c6IkZsh+raJ3ca+w/nqURbtEC23gxRwe73Te8Xvq36BkuXW9cZyTEqo3XelI3Gzt/6thpxEHMu55BjUA9c953XEdoP9dB9BRLULOTq964m1yS5uxm/7woiJFwj5GDCAZ52zvFsmI69URR1CnjBUExjPacZ7WyO
*/