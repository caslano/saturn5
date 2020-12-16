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
ziZcD7R0W09e06ixff589WESqnV4BPfIPxSf3Es+8oWc+XMwOLqyP2V+xNoWIzxZOFxroFc9v0KevAmtfGEfvNsPl115vjdP6++aO7U31GxkvRsze7a5V/qxXDRQqmLgSfXd0DQ40KV0PZ3nB3act/tcc4M7CfBHE/G/Bj0YQ5l7/4T/oMJg7Vljf+6cW31Ey8n+2EEk4Lsny5+jZQmvf2rMkQkVG/5m5SJ2rv0P7ucFNtmraGGgkzCv8/jMpmT6fnup229r3I7r8V5MvRr4XN7PWFjIDuqParN0ob2eIaKlH/IBfCCIKcOaNBo7LlkYXj+2+5+9jtEUt9fMnhxRTq176zPUr5QPPul7ljzhdZelFi081t5J+wUCRZa/5Sg2nerzfyiH0cGsD6FfOFYbz7b0lNvGhfP4cG7mmu0Ej2bNZurzRV9RBN2sjOa8Yh9gDudj9Jo9/ijMwlnCRP6EEM8NhbvO4B7zJ4SCui+aHVXGaCbA3SJc9E8IBbhYcQTO2lh3sXBHZ8QFnBrZtpZ4+FP5+SBjn5OmTEj3hr71caKH9H6O6CdEt18NMrT4aWHaLt+mR0SLeCXIxyybE4GRjowu3y1M9JZQxkXhuk6fCYflLR9ZeoaLPZUtkIGtprNlHnu7h8HPmeviH3tLiZHzpPCRW0OsPUy3b8rZg9TVA5eLRev39hD1pfrYUoNKzP3twf30fu5X6v4U57Zprw3Po9Vid4ptVTnvmJA7OsFe8ueZMnomPWMpdK5yZTltSXfRpTJqi/P8Qm3NVIp/Zh/GTYftfRh1sbrm9bU1GzZWndo+jIps1THq2aD6jtv11dXH1m9oXt/SULU+lhxCenfiunblziS7JrvWLl+7cu3Smmpe//VeS+xNQaOulKmr/Mbcuhobmpqbmmpb/pu6znGe7sfeEk7RdUeqbBeqoF+LdlFRiKYNaabsrTbdfdOJwqbs6lkhmgob+jGLjrL6koQMdvoG5We79DRhiHbZ5bk3SRRV/1MchX4qrhCU6S52y5ySq/plzi1xy5ya+5gyJ7JlTs29V8mmK063bFpdFWtpWbe+prmuLuY1iEH1FtvapVVVGNCUqw+Va6pfX7uxfn1zzGs0VC7o5+lZRW6/YJpXkUgxGpv74/P9+0QZ1uB0f6Qh2AdHdAx+/SLhvgzB+3PWbyfEN/jYAKctt/7+6qFi045+LEDvH4XegRp9VYCjXfZ872YT9A5WendTlzCvCDCIm+zVK38IoLV/xY9X+rhCGwP7fXlHAmz0j25Y75rs8bH6YZlO3tuELhtN34CNzL5WlK2X0UTH1z9g0S2EoY/Y9MqA7vO6w9tLhnNlGR101ZndeuZGgeHBFG2do7oeZiwsBtvDCwqJPUPAg9+zuT53XCBlY0+o9c7cWB6dZbfhwFYfzC+f2ksdvb3BPrpZW8KY9EDayyeSpp1b8+pJDw91m32pCHOZvc+WIcnbo+vTD4f38PYDsPa8PpStn7X+eJvesHWGTdm/b7LLahikrOkfd/t7TpHN2tf6E3M/2zuyOV/a2GfK0PR6e+fylZWreJPPnS4tL39upf2OzW9mwK6uuCSL9eXYmsWyNJXo7+mqHOonbBnaSeoRrbe/ErJFW7XNpw0ZmrHPg0E5OlH2TXFmf+673sG7Lg9HYYjvWZjVToe3l9l9rNpU673f3mNoP9xk05hJQjP1/9GnaSnfyymvdEevXdY70/+CD+Fq6b7705kG8k66qxWLiq8IYzal6TzYPOi/Z+Rh1rlRxG/n95uj+MH+VjsfuSwCE9rH/GhQDyGxgnFU8Wubfb9yJZsB2g3t7Tm05atXQDN8nwhoydRQgoJMZjqD92GWGLr27PbsSg0=
*/