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
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
*/