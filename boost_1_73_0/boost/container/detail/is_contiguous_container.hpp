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
zle3lFor5XGZR56A4XAJjIZPwvpwGewMn4b3wuV6jSg5zlffbVfOT9/K9+9JmAhPwTrwe9gQ/g02gmfgSrFXiX1W7HNi8x2q7GE+zBcnuApykudiUWs0AGWiaWgJ2lhTPZ+tn2deh28nOoLOo4hTLqMJMp+zXt7betZ6Fwcsq/ibZ67V89bb5Xnr7LUug9ee/EvPXLeX5655trrsuerf8Fz1lEzXP/1s9QD6ORsVo3VoOzqM
*/