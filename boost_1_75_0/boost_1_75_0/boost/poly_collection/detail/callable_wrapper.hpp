/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_HPP
#define BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_invocable.hpp>
#include <functional>
#include <type_traits>
#include <typeinfo>

namespace boost{

namespace poly_collection{

namespace detail{

/* lightweight std::function look-alike over non-owned callable entities */

template<typename Signature>
class callable_wrapper;

template<typename R,typename... Args>
class callable_wrapper<R(Args...)>
{
public:
  // TODO: we should prevent assignment by user code
  template<
    typename Callable,
    typename std::enable_if<
      !std::is_same<Callable,callable_wrapper>::value&&
      is_invocable_r<R,Callable,Args...>::value
    >::type* =nullptr
  >
  explicit callable_wrapper(Callable& x)noexcept:pt{info(x)},px{&x}{}
  callable_wrapper(const callable_wrapper&)=default;
  callable_wrapper& operator=(const callable_wrapper&)=default;

  explicit operator bool()const noexcept{return true;}

  R operator()(Args... args)const
    {return pt->call(px,std::forward<Args>(args)...);}

  const std::type_info& target_type()const noexcept{return pt->info;}

  template<typename T>
  T*       target()noexcept
             {return typeid(T)==pt->info?static_cast<T*>(px):nullptr;}
  template<typename T>
  const T* target()const noexcept
             {return typeid(T)==pt->info?static_cast<const T*>(px):nullptr;}

  /* not in std::function interface */

  operator std::function<R(Args...)>()const noexcept{return pt->convert(px);}

  void*       data()noexcept{return px;}
  const void* data()const noexcept{return px;}

private:
  struct table
  {
    R(*call)(void*,Args...);
    const std::type_info& info;
    std::function<R(Args...)> (*convert)(void*);
  };

  template<typename Callable>
  static table* info(Callable&)noexcept
  {
    static table t={
      [](void* p,Args... args){
        auto r=std::ref(*static_cast<Callable*>(p));
        return static_cast<R>(r(std::forward<Args>(args)...));
      },
      typeid(Callable),
      [](void* p){
        auto r=std::ref(*static_cast<Callable*>(p));
        return std::function<R(Args...)>{r};
      }
    };
    return &t;
  }

  table* pt;
  void*  px;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* callable_wrapper.hpp
LeptznyaJgJJGIMFgEicSwBayHzEDzL6A/6kHSh+jsGDB3sYrjs1g5W1VIV4oHu4nWMLdadppiCRqTdI7luiUirLIqTXxY9J668BTdYpyB9vH7G+IQN6rdFAAN5CAEo2SKbTPYZk9UVqBeQKyfwVnJ7+aXJfItSd7MAXBiojndhFSkA/XCIdEx9dkciF8sMNHGDn0IzxKdLyIGny5hPinAVEJokEctUA0ljhrUMPjgTFSIw/IL9NlpIi9r9CPuu/hXz+f/xI/S+Y72Ug7y7h2lDL8cnDQt/j8bbhRMHZbni5wY49DjD9RefTNnPyVogwYof9tAFYOGfkDK20HBYq/1ORakbFNp9a7o2HNJUm7gdFqRkpZdr3LE+UL/6scJJYQxrwzuaZMZ7q0K1gTKteFWO/xoP8td/Y/URWsyt4zHssLY237mGXmxN4GKxecUdGWrj2UcpxZ8RGTZJGk0WDNEiqozNudLftaBU8rc8Gf1liukpW5swhOzHY9lyIXJegHGUCTfvZPho5y/LWRzFZOHgaueEW8lfEZ41+QvytQpPl+kSla9fshyG4VlIeAuO+OT/2thBfYhUR3Bc5Fu5yTPxJRykrseAJ8r3OQ18y08UxfHmC/Gj1XqT2dOUnVwcZK66PZUyjFXGe598b7XEcYlabJkJL4/kG+Peud+TuPZ/pxA0GqI+WnY7nFvfU7UmYw9G69toQvrfPw81z
*/