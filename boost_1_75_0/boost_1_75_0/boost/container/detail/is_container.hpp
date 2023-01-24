//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//empty
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME empty
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//size
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME size
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_container
{
   static const bool value =
      boost::container::is_container_detail::
         has_member_function_callable_with_size <const Container>::value &&
      boost::container::is_container_detail::
         has_member_function_callable_with_empty<const Container>::value;
};

template <>
struct is_container<void>
{
   static const bool value = false;
};


}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP

/* is_container.hpp
gaj6F0H0eskMZCw3Ez1cOwvd2DcLPZBbjowPLkUP9yxBrnJz0cvVvyM3+V+Qz95fkIPcUvRiwwLkuH0pCty7CN09NgNZHPsDPT21CD0/MhuFnZ6DAo8sR/EbF6LPm39DSTpLkfm6NUh/jyx6vHMzsjq4D7nh1cpnqyxy37MB+ePIOLgX3VDZhO4cW4Nuasoho2O7kc3JPeiG7g7kdGoVClFbgwI0NqOAowrIUOM0enzuFLqpp4ustC6j4JPKKOjycZSusA5FnVyNcpW3oJjL61DKiUMo//ge9EZrO6o8sw+90z6JYnQuocqrR9GP18XQNKNRaLbVBDTB9Wc0xmcCErs9Ey01moEWPJ6BJoROR/PsZyIZp1/RXN/f0XSnZWi+nQyaFiKJ/gheinZem4c2PZ2Ntj5ehHY//AMdvSaD9jj/gcbG/opmvpFAS+z2IMmQI0jdTBadv7sOnTI/hNQeb0drnRXRpee7kaalFtrioYrO+Z5Es2JWI8kEDbQ3cjeSizuNTpQcRgaPpFCosSQKd1mK4IkYavEYjrIeLEL1N6egDOdFqCVhBrpvIovumtJQwJ2tyN90FzJ8thHpvzyI7P13oSfXtZGH2XHkb3YSGXueQb4MdZRosBmlmq5Er222oIz7G1G88S6UcF8BZT1URAVOa1Gx90qU7LYd5TgqoHi/A+hz4AYU81QVxRldRenXtVCdmSbKdVNGHxjH
*/