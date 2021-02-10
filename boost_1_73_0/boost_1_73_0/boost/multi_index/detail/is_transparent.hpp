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
DE4M03hUJ94zU8Oaki27tTNzgSeGPoOiogpOF/N46H32AGop1ihYw8wYV1O0w6ltBHgPySKOrdGGYiloGY09XK9ruaQ14YKbgQ0gH+L0j0lMJnE8dA6M6u1u2yI9s2lmsHOc1Xdc6U1OcPLB5jP+V7eP4WQWzn04P+aYR9fhNE1mUR6liQ8DW+HQ5bnfIdHVdTrLomQa7pILsBFw769JvAifXsPOdNgSKPIxMheGib26vLw4H12+HvUy7DSz/sQBYDevpGr2oqCwqwH6DD17Ga0l9q89IFLUjIqudRCH4DUzXKzkM/oouUrJU6FkkVyHuQ+/uLPcw7sF/PTeqgafHdEuqzzMchLO5+RqEsWLeTi2Gghp8K1Uyt7lru7vpgXw5UeatVSb/6LY/1Co0YsL9Q1OtphOwyxzOO6+xu8GLwwGG7a/4Jeu77zncG97zWm9oVsNvXXHfii+Nx+Uc1v9C7vf3IuO/S1sdmPvi/cPUEsDBAoAAAAIAC1nSlK/e5AV2AQAAB4LAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTEyLmNVVAUAAbZIJGCtVW1z2jgQ/s6v2HKTFhIfDun1PuTl5gihTa4UMkDayTQZj7DXWK2RfJKclzb577eS7Ria
*/