/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_FUNCTIONAL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <tuple>
#include <utility>

/* Assorted functional utilities. Much of this would be almost trivial with
 * C++14 generic lambdas. 
 */

#if BOOST_WORKAROUND(BOOST_MSVC,>=1910)
/* https://lists.boost.org/Archives/boost/2017/06/235687.php */

#define BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(name,f) \
struct name                                               \
{                                                         \
  template<typename... Args>                              \
  auto operator()(Args&&... args)const                    \
  {                                                       \
    return f(std::forward<Args>(args)...);                \
  }                                                       \
};
#else
#define BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(name,f) \
struct name                                               \
{                                                         \
  template<typename... Args>                              \
  auto operator()(Args&&... args)const->                  \
    decltype(f(std::forward<Args>(args)...))              \
  {                                                       \
    return f(std::forward<Args>(args)...);                \
  }                                                       \
};
#endif

namespace boost{

namespace poly_collection{

namespace detail{

template<typename F,typename... TailArgs>
struct tail_closure_class
{
  tail_closure_class(const F& f,std::tuple<TailArgs...> t):f(f),t(t){}

  template<typename... Args>
  using return_type=decltype(
    std::declval<F>()(std::declval<Args>()...,std::declval<TailArgs>()...));

  template<typename... Args,std::size_t... I>
  return_type<Args&&...> call(mp11::index_sequence<I...>,Args&&... args)
  {
    return f(std::forward<Args>(args)...,std::get<I>(t)...);
  }

  template<typename... Args>
  return_type<Args&&...> operator()(Args&&... args)
  {
    return call(
      mp11::make_index_sequence<sizeof...(TailArgs)>{},
      std::forward<Args>(args)...);
  }
  
  F                       f;
  std::tuple<TailArgs...> t; 
};

template<typename F,typename... Args>
tail_closure_class<F,Args&&...> tail_closure(const F& f,Args&&... args)
{
  return {f,std::forward_as_tuple(std::forward<Args>(args)...)};
}

template<typename F,typename... HeadArgs>
struct head_closure_class
{
  head_closure_class(const F& f,std::tuple<HeadArgs...> t):f(f),t(t){}

  template<typename... Args>
  using return_type=decltype(
    std::declval<F>()(std::declval<HeadArgs>()...,std::declval<Args>()...));

  template<typename... Args,std::size_t... I>
  return_type<Args&&...> call(mp11::index_sequence<I...>,Args&&... args)
  {
    return f(std::get<I>(t)...,std::forward<Args>(args)...);
  }

  template<typename... Args>
  return_type<Args&&...> operator()(Args&&... args)
  {
    return call(
      mp11::make_index_sequence<sizeof...(HeadArgs)>{},
      std::forward<Args>(args)...);
  }
  
  F                       f;
  std::tuple<HeadArgs...> t; 
};

template<typename F,typename... Args>
head_closure_class<F,Args&&...> head_closure(const F& f,Args&&... args)
{
  return {f,std::forward_as_tuple(std::forward<Args>(args)...)};
}

template<typename ReturnType,typename F>
struct cast_return_class
{
  cast_return_class(const F& f):f(f){}

  template<typename... Args>
  ReturnType operator()(Args&&... args)const
  {
    return static_cast<ReturnType>(f(std::forward<Args>(args)...));
  }

  F f;
};

template<typename ReturnType,typename F>
cast_return_class<ReturnType,F> cast_return(const F& f)
{
  return {f};
}

template<typename F>
struct deref_to_class
{
  deref_to_class(const F& f):f(f){}

  template<typename... Args>
  auto operator()(Args&&... args)->decltype(std::declval<F>()(*args...))
  {
    return f(*args...);
  }

  F f;
};

template<typename F>
deref_to_class<F> deref_to(const F& f)
{
  return {f};
}

template<typename F>
struct deref_1st_to_class
{
  deref_1st_to_class(const F& f):f(f){}

  template<typename Arg,typename... Args>
  auto operator()(Arg&& arg,Args&&... args)
    ->decltype(std::declval<F>()(*arg,std::forward<Args>(args)...))
  {
    return f(*arg,std::forward<Args>(args)...);
  }

  F f;
};

template<typename F>
deref_1st_to_class<F> deref_1st_to(const F& f)
{
  return {f};
}

struct transparent_equal_to
{
  template<typename T,typename U>
  auto operator()(T&& x,U&& y)const
    noexcept(noexcept(std::forward<T>(x)==std::forward<U>(y)))
    ->decltype(std::forward<T>(x)==std::forward<U>(y))
  {
    return std::forward<T>(x)==std::forward<U>(y);
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* functional.hpp
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
*/