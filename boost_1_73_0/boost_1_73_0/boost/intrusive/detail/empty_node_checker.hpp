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
EmrOMBuKqj7LdFhKWyT0O/nJju99p8KQz5LWJqpmoUOeLagtoi15aSCgHSJrltBLUTd9Vs5F4VYE5UTXm/qgK4dwwloivM9JXr14tklqhfB6BQ5zlvUmuUyT1Apx9QrvYZ6bvNPeeVVhZ+CSaZ/c6eaiCcXephkQddnFC33ir+B5/X2aEToIbM1+WrTm+cGyad7aZ/D3os0t17il7d46PSjmE9EmxPZemRg63I463mmvW9DpGT1rOqPfr675MnP1qf73olfdC+1xNCOEermhw8G5A9PQTfJhbo69w+ePM81cvK/xi2k80U+GPtbd5TneGm70uUFZ7yZLbTVjYI6N+YRQCajBLFsnTmiVXF9+/evmMUO//fVfB0lFUKMn1hA049ImM9saE8ex7LX9ne7n/vn7rx9/vel9+Tz6MjyntcWceeiNpugygjpGrq2b95eWRRW577r2nMoTPhaceTU3qeyBybsXc8PVrx9sz6oTOsI67a0TgusCmYfkBzG81eN1RZFfBdf9rtkm/bz4rrv439NOO3TQH0Jb46ZzRRxrbo/J9mhKkbOIij0qxtwm3aPHo9OjX2iT/M/MA4rDAKIGiRJikTUQ0bA+ofPwhJhjr4CfzsnNq5OWN5R/GhNt5v9N/43nttHaHuKb14ba
*/