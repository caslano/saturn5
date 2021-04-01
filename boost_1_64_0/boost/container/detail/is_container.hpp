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
ymgLBd4elr1M8kir/RiLZvEQrb6DcFOz7NUkPvYFxF0BCkG5UdCtQjZHsu906HawfJFEshh/xQWNz5FWafux6Q/oSiJDknKUmYjfhaYNNVKywIWcZsegXlTT7bllUkv+uDc71ozYULdSG37g8E2HAvoOfzKsWD8IiE/cB3gkENHPIf7nYhozU1iv8irDyjUn2geMz9xxhyk69eaGbV96JEHyz+j+r+Kp8V2wyA0urLeOdMHbl6+Mth0wi5gz+zb5VUXsMdBXpl79dcmOQdqf9clwdDQEeLrzW4PxLUCKnuUDZTQliQVX8T+ZbHImLVD1QnAUR+TPlj+JwplDgxkVqEqtWia7BZfBRDkJpFBLApDxIf73PKShZM0l8iACsayE58QPp4WovMVKMDcKJL7OFJu4WeUrfE1K96BEW77xp8evenoouPO24Vo32jltCfmjE30vEYLCFPZRIneGVeZvnLeNXifdPJu3SbqRWdSjAPKLUsn6ep0Fg36VL817oDneqWv6kjsQoGBhIcBaU3u+z83EvR2tpKKYa3IuQP7YmI1Z3LsCuaAeJEUiAw==
*/