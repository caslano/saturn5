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
wsM/jDlfuF7IdbluLI2U657WF7LcqcuabP5Fxqo/ICv3OdWCO+a/L1zAEsuZ79I50WWDrxt1QvySk8uxdD3WxZsT4dTmJK4BcYYUNW4exNEU4c+UEMxFUpma/3jnZegT61EFwC7K0ODICo9ruQXeHXPQyleZjaCMLJvsrRp7YyOLIk5DGYx6Kx4gyZ2K4N52mYv5ERAIZP97VXT+Pg5/ev2jRZ7tXFYwpMo8ybJ39enCwMlk
*/