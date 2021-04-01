/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_TRANSPARENT_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_TRANSPARENT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/intrinsics.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Metafunction that checks if f(arg,arg2) executes without argument type
 * conversion. By default (i.e. when it cannot be determined) it evaluates to
 * true.
 */

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent:mpl::true_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#if !defined(BOOST_NO_SFINAE)&&!defined(BOOST_NO_SFINAE_EXPR)&& \
    !defined(BOOST_NO_CXX11_DECLTYPE)&& \
    (defined(BOOST_NO_CXX11_FINAL)||defined(BOOST_IS_FINAL))

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_final.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/declval.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost{

namespace multi_index{

namespace detail{

struct not_is_transparent_result_type{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_class_helper:F
{
  using F::operator();
  template<typename T,typename Q>
  not_is_transparent_result_type operator()(const T&,const Q&)const;
};

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent_class:mpl::true_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_class<
  F,Arg1,Arg2,
  typename enable_if<
    is_same<
      decltype(
        declval<const is_transparent_class_helper<F,Arg1,Arg2> >()(
          declval<const Arg1&>(),declval<const Arg2&>())
      ),
      not_is_transparent_result_type
    >
  >::type
>:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent<
  F,Arg1,Arg2,
  typename enable_if<
    mpl::and_<
      is_class<F>,
      mpl::not_<is_final<F> > /* is_transparent_class_helper derives from F */
    >
  >::type
>:is_transparent_class<F,Arg1,Arg2>{};

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent_function:mpl::true_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_function<
  F,Arg1,Arg2,
  typename enable_if<
    mpl::or_<
      mpl::not_<mpl::or_<
        is_same<typename function_traits<F>::arg1_type,const Arg1&>,
        is_same<typename function_traits<F>::arg1_type,Arg1>
      > >,
      mpl::not_<mpl::or_<
        is_same<typename function_traits<F>::arg2_type,const Arg2&>,
        is_same<typename function_traits<F>::arg2_type,Arg2>
      > >
    >
  >::type
>:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent<
  F,Arg1,Arg2,
  typename enable_if<
    is_function<typename remove_pointer<F>::type>
  >::type
>:is_transparent_function<typename remove_pointer<F>::type,Arg1,Arg2>{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* is_transparent.hpp
LtpyimnjhVzBHxe4iIxnMeLHYyY4I+/g642XWqsqPqBFqjJd4xAW+LP8eZRgdozH18eaRBTQjL4KWWYaRry64TkbT7o6VzhWxvb9AQVIQ9sMG4LJWHMvExeLvXYJHbsImTS+fpy25NLBIFmmeaw+EIjCT6qkevc3wXbWS0v2AWnogk2gBT/hcJ3BXZa8sH+tH6r0WVk41k5DBdqA0cd1Rl6Jv7kYqfHWOp1q47vNKBIhgzIEEISFqW+3AS5ctQEFLRezmOFJ+auibavEsMJyJgRm1og95LLy2w15m+Kid/keCb+VSaoMMCftGLNMn+9QFZrHl5rgt4haH/NCWRnwKxGmUGMSInxcArHv2nyppZ8OGJtR6X8FjDWhtiSxCJjvtu+3zN555rwO5IYOAemhxVrAmyrGkQJGoaC/nO3wiu0sn3SmaOgIQDTu3DiY6Rnzpce9uTNABVhszXXiufWHJJK+k3+K68lxv00QOhNVb5NURdQM9re5AxsGS0wUO2gCvFi6zqk/kOBmRVSc2rUxe+w7U9hzjDL31ume7rLbVaRBWFDsN1OThMHXaQ==
*/