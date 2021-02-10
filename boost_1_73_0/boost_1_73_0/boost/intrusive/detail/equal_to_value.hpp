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

#ifndef BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This functor compares a stored value
//and the one passed as an argument
template<class ConstReference>
class equal_to_value
{
   ConstReference t_;

   public:
   equal_to_value(ConstReference t)
      :  t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(ConstReference t)const
   {  return t_ == t;   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

/* equal_to_value.hpp
Fip0dVfP3dl88U7VdW5FaH4JPpw/uoeLLJPg9N1W+4MtTs7UFLBQN3YLC3Umoq7VXTS/HT05dJru0uIdy/BuotWh1fy66NSFNn6gk0/X//8/3r4JEBB841svsBOdrnbnf95ciAm2gBKgBCgBSoASalKCnv+RmIQ2kyzWjAamN7kvp7zlzRP79Xq8W/e2NvVetn5LQeALHjenzya3Cw9l5xIZ0PIdqihILUeG+UO3LdNLVOz+8eY0UHDzMKgGqoFqoFqdqRaXwS+faus5WSHfB1ABVAAVQAVQqRVU9tBVisrhQESvPpjqfb0a3oyu310PetTUoBaoBWrVLMAnGBMx6XeABqABaAAavKDhzS+OUyuAbJ5N//N7uHvhxmSrLHT23FVCABCQBCQBSXhWdY4HyvWswBgwBowBY+CI8eZNmiMWXKiUI4Y1q/g9pKoXfOzrjnZrxDJPcU7dbHFq8fH918GwzxNZ7zVHH/uw6T2Q8V9O99z0VPugOe7yQKcdcVImkHnjJ4lmGalEz9y+rz4s/uhu3SKddsx5nOB2A7jlg9ukgkQreW1KJZBUeqksadtBsAqsAqvAqvysqq4nxmVJbDEmQToFSbc/oUqgECgECuWjsFr4K3nhqz4wk7wOF7+XOtAGtAFtQJsAtFXX
*/