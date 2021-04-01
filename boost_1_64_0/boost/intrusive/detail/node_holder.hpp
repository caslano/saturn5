/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

template<class Node, class Tag, unsigned int>
struct node_holder
   :  public Node
{};

}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

/* node_holder.hpp
7O5Z3jaF8vNfWS8muFPSwxBS6WNw1lw9degz3eL8t13E2RftorX9s+cJ785IOn9VYSVaWUH8x8k4qnzTCW74QxWB8rm6mxj3DvDf4phJKbqtk5U91SyA2s26pp+ox/GULWSvbPa1GVHceYhfdI5I66M86YSgJGJTCku5+WKHLHFxp9pXn5lKAClHypb3uTYpIqDiPRI50hrANNeAg7Y3rAWzz5Z6NPdPdzSihY31AVWEiyFlHz29dWsTjezHRy5ID1WdxqWG9XHw2+JSXBa+WYRmuUkENoy1TTiHZYHVwxxNRdrqDR/JHcjtcj4o9irV2vFEpW3ZcVv3MIRDoUI0WZXxRuk6qEqArvEDjSHMNC7wpUgbWTkWlg6hl2OjTARzxtUTVAOXIkn6TX3VP0M72Dfht3kVmjZMrTJISnGgi9h5lET9URca9KvVSp5u71Q0CP18YyE9wzZo4U5enxqrEAFFJ9GJdG9jqQpYPCe9pZJrtY7x9631UXO1OVx2feCP+QW1fUr5pAKDO/yQ1I5UElbWAezkLI07D7tUAtNIBqvsS+MPe0MeWP37VQ==
*/