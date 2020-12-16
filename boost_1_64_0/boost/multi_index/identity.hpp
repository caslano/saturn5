/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_IDENTITY_HPP
#define BOOST_MULTI_INDEX_IDENTITY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/identity_fwd.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class Type> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* identity is a do-nothing key extractor that returns the [const] Type&
 * object passed.
 * Additionally, identity is overloaded to support referece_wrappers
 * of Type and "chained pointers" to Type's. By chained pointer to Type we
 * mean a  type  P such that, given a p of type P
 *   *...n...*x is convertible to Type&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. Type** or unique_ptr<Type*>.)
 */

template<typename Type>
struct const_identity_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<is_convertible<const ChainedPtr&,Type&>,Type&>::type
#else
  Type&
#endif 
  
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(
    const reference_wrapper<typename remove_const<Type>::type>& x

#if BOOST_WORKAROUND(BOOST_MSVC,==1310)
/* http://lists.boost.org/Archives/boost/2015/10/226135.php */
    ,int=0
#endif

  )const
  { 
    return x.get();
  }
};

template<typename Type>
struct non_const_identity_base
{
  typedef Type result_type;

  /* templatized for pointer-like types */
  
  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Type&>,Type&>::type
#else
  Type&
#endif 
    
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Type& x)const
  {
    return x;
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  const Type& operator()(const reference_wrapper<const Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }
};

} /* namespace multi_index::detail */

template<class Type>
struct identity:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_identity_base<Type>,detail::non_const_identity_base<Type>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* identity.hpp
8ta0Y77r62KmkLDufR/xrurY/IjqvLLBYHzvevdG8113G8oHllrBE50XGA5l2sd2jzKs9/KT/fr5fYpNm/QO7knv2kR5c+umMeB7MIYP5tXWzQbXTQ3lXky/t4T7H8TZwxlM2+IWxHm6daAU4+m+RLBbpXv7PZBH041hXEYcmyPKPvyeiLXmyU81ji+mUW7tXua7ukRilJIw/4E47u8zW0OvAIx5r1f1Gu94AU6nt9j8+/euPzJ0DjxO5/wHrTYXxx64/Qnvts3Ru2qvZHEnr6xU3rO7xR3gtkWxz9mxaRhnvO8P9ZN8HpyGQRZlYSCsZYK9Nzd6xZr3lWFQOVnO5Li7fNzneTiTBRfbURqkVSTaomrtEU0y2VDkZZnJJJGiNZl8r2GKyubCdbIiKqJQkBWfiescnsVQmVJUgcqepAoFW0HWUiizRmUK4akqEWd1ODizss9T3sxl3KrKgzINBB2hjQzOva0ykJEf+uBUdXBIrkWpDRcqWwnfc6tMVqXgPRHfx/0BC08FEzmxF+VRf81EPQUTG0o8bUFU5JEsC0FXsfZ5zq9YWI7IMj/KolKXc4tTYoHrOksuiuJI5okPcvQNl23naduneH6EUezHTgli5F0br0+7uEyV5nHuRwnKYEhk73yCyky6jg/O2VLIClb/0A+lsOKV5oFf+oHgOxFWPacyuSgKv/LyOFYyaNdiwFdaF2SYr93IzYrA1X6g2/McwztHZUsReVnpS0ewxaypu+jznIXnCC9K86SQkbCWsaZe4LkjT1sY5mnuOpE4DvtZL2ceAbEubf0QD0umMkvjXAmpTck6SegFjpbVw6ncpBd4jpsFJUhx/324f83S5AsvzdMwSxPiA3PAyTn6KmZxTOD8tkijwhEoQrybkuDp3t/WT1v7orGXujJ2xeqcuomtdjPrbcjFudVV2PubWdI7gMajaL1vt22vuqv5sHpfzmnZt3uS8ufWezjiQ/ft1um+ndPft3scGevODhvriL2xS3R8err0sixws8RU5ToLHmfa/gfo/bZEJqkLZ4tmE3630XmV6fSyUDpw4wuaLPrrxPM6yp30vMrJ0rLSpreQTOcE36d8LxNB6nuudO96Hm5s+FQfB33+EW7Bp8b/CbaQDN43cjA9c2Yd7Q39aBBHLQ9tdIhPAAcHbi3/yMYW0VGOGVkM/7rB0QiCFkc7RT+ycAye2vpQc5lXdXgc6X7Jtg2Aow4D43zw9Q1OLAIh9jvE0BoQ7t30NlJMq0S5GxSDHpNg0SjFYG5N5rSIQe/cl7m6yXzHpRtiP98MGOYxTA8wjv4WhjGbMN8ETNvzYHmHuL8VcZJ3xGYRxSEtJE5H72EwDLt/x1pjumc/Tufeb78nfAebGlZ8cO2NeGt83oz4YHz+YzASn0eaOexHoI7pQQPNOqySNvnly3y/OnBjP668u7hHy/erRz7OxuTMCUrHTwphmbDAO7Wm39lB5fZVQRUmnufovuRQY2t0De/GMm6QRKmMZAl9FBi74H3UbsZNZZH4WeWICpjwP/uc+8mMH1ZxUMZBIJ4zjD/B+FnqpA7cEAmH8Q8yfllmRVLlhVgZxvcZ3wtKV+ZhLFZtPtjx2L3XlLdd3Lpd49jyarCTAZT6EATr7vUOYADoZTSuC3duMN+pkQxuA+MScixDGWTv9skbDafFUAbp876JPGYZAvEXj3Lctptwg+MmmZgHb96EOBrjeCS+G0KMGj5A/B9bKY5BI/7Te1Acg8aw1+6JeG0tgsj+iWEYNOJiG8UxaNQt7k1xbgfjV4jxvRJ8a3IfxBdO1rKIXbgvYLAWAVyPIYj9h2F6rwLrxPx2wFomyaTe7Lgf5fA8xXcF3xyBPkw=
*/