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
0gqmvtJYoD6yWV1Rb66ceI6srCtXEK4UqI7sRpQGRLdQnLJOdUnbVKq+cLu2IMTnQVNSIDY2fFcbAERCOm1p+kuKTqO1S1pPCnqtKWWrVSkyn/Z7ETHA6xquJHllSWDSe60nFJSmcrfb/aTsBd7CN64IlrwMoO0Td5r2yTgvqv6DUkPXaHWXoUu3fmhDc15RJp73h6Yw/TKxs9wxzf3yHv0UgB4MualZvuICq7xednCJbR4xGiN8Y6NZz7pbtsH2Ww07uuOUhlO/w83m40fxVfOnpC9b7x9QSwMECgAAAAgALWdKUlODSCOLCQAA0iQAACEACQBjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxNjUwLmNVVAUAAbZIJGDtWntT20gS/9+fotepUDYIYxmwk7DsnQMkoUIwB6b2UoFSCWkcD5Eln0YKkITvft0zo6clnLC52turE9GrZ/oxv+7p6ZGzsfrzjgaswtLDkqeFB94lx0kYXDMnqu5tWd9A/SHXBd6XKdmAjOWb1YblLN+gJVksreVXerasZYouyDa6bBDnhUWPSEE24twL5nch/ziNoLXXhl7XfAbreOt1Ddi3fc48OIuYf8XCjwb86krK36f27W1HsN8MYBHYXkeLGk+5ABFMohs7ZIDP
*/