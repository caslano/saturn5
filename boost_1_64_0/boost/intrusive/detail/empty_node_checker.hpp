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

#ifndef BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP
#define BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct empty_node_checker
{
   typedef ValueTraits                             value_traits;
   typedef typename value_traits::node_traits      node_traits;
   typedef typename node_traits::const_node_ptr    const_node_ptr;

   struct return_type {};

   void operator () (const const_node_ptr&, const return_type&, const return_type&, return_type&) {}
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

/* empty_node_checker.hpp
cJLM0eP6qNKDoIUTY3Vew83SrjKpM6xi+bNcB9aQew70DnVVrOkmv6VrCz4ibEIe4HlUKgSUtqS+KGm1Z/bb6glYNmnBGaXueLUsl1Yb9Cjy9EbMinNhTIYHijL3rVb0Wx49yBHMi/mAuV9XRQ+u4Ke9LW1/kvfbwHGR6GDOm89uxI/gJT0jWPwdS4FnfP/d1P23t421TpXAHe8bGEy+EpccAUtHqUQbq75Iw3YkMzAYXoRxBkyeGdnHeduHXgx0csqGbFVsXy4tPu+LL+34XAZzJhvAZm/FF0C2+pZaPC/dJOi4W6unobZTOaq0gYMAv+WQQJNv8uAcYCFA3hYFAdFvH0xohklxIb4h+Cf6fa43NM2aw9w1w2tA9b0LuVkbyv6AqYzWIyy0TjtcbhRo+uvU48yDxbrc17zCF2TslMapaDBBdKLxK+e4xkRaqu1WGy3W8xXt0ASFtauGPvDwV+PN8MoIC/nAc6r5ZZdlTXQBOtisVrQWtGaOCvnAGoJoU40xjIxdRQgCjAeGO06AuLsOIZKNotgMtBviEIHU2OSGoov6lGJ2OMdcWw==
*/