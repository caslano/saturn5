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
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
*/