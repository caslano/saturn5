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
d2BIriSP3k/nUjsU+87MQ0GwUug9gwHMcsgrwN7HIOKdgiLe7JNmj38Ji3Kf0fQGD8AX7awUH2EXStJcooVXURX/jF0iyGk0e5YC1fOMLg5GX3O7ECddRHJfQ1VKbmEXLGohrHCOfK3H71UbRJGTyD9Wtr6bwQufJT9FixZw9N8oVvrOQbjSq1gjMsJOjqSfxOrZZXpR8DiRXCadksvsEp89FUPJyO6jZtbGE9GW00tzTe2lsbVhXYo3hOJeLiCrizI7nqCNfFV/fKBZX1Wg8MefMhHbmQHcJMYZvfIE3+eI8guxvFEshFAchKO8Tf79k7ZNrvXIxwC/evzLyU7Sv3w+/cyA2ffrhg8Yj4BUCV0soWw5r8Pbn2BIBNWhtmG/3CoOAYw5OV83GixgNogJvhmvt7GXbqT1H/EevDhbWdmWI95CE2vbRHDM3xnPQkOzSVxpI2nPjKUc1HkprNpLC0lEVSuCOi/FyU7gKiSgipVkuIY2sEzehJkYt5upkV0IOYERGJ0zJCx7nZ9tpS+KkAz0MEuuwec5JEzBBAEvC69jVk5jhAju1GroVN9qXYCKnVqtdWp1qFOjV2MbWMaS099N4ZLTQyHJ6Vf0KPuk2/wU2XgaRCe6d/4M3TtfQGOM6njAFqGPU98hPI93n8d0JjNmC7uA2yh8AE76UJu2btgGrzoLXXKuRVi84z7BeLDARUR2mq5F0hldyQLU
*/