//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_contiguous_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_contiguous_container
{
   static const bool value =
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<Container>::value && 
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<const Container>::value;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

/* is_contiguous_container.hpp
wAWuP+LWiptgSltie+5Y4/jBLiEK4NBOmTb3/YcBCAiKZQ7phEghJ3wYmQ7F6G4Vq10+YvmE6E/9IDI/M1gbeFW3Q0N8W1IVaqdYHKuQ/vw+f90wey1VnFbTJ2gB3pcHLxRQrVKe5KhLM++SMC+M+VzbgwpAy3JOpMMIW41i2ECfh9kKfnzdTAlxndegn/bSrb7V2yYWYixxJtU2vTKdBCI5R3IG2AVlarO0/K2ymuCvhbIqC+SrtNYmSy3cZadMpTDAHZqFnT3RVQDDoZcKb6Wtk1u1FdX4ZV7rbbZLdm3XWLd+mZtvP+o9m7ZUs19tRYoLW4yP8O1ALNgFKVkeF7Y3nErGfjyCB4LGjRTvbF2/KbYmhURBj61ZKbcAxYH3zEuL1LCWSFe1JUDJT9RR2TD9s+0ias/dBn4eL5c2ZBDAOFDAevxjihkkLxLMP5ZxDmKcbMGJATcqzlP0wrhKMUomELqhrT1cXbkyhyuzKR8Ji3q1QGIsE7vM1gHosufCqxo5DskgLvXVuQOr0qIexZaiIN1fmYBGKz0A+GFQZhFd5hL1D1vWE9GpLw==
*/