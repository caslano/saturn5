// - casts.hpp -- BLambda Library -------------
//
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

// -----------------------------------------------

#if !defined(BOOST_LAMBDA_CASTS_HPP)
#define BOOST_LAMBDA_CASTS_HPP

#include "boost/lambda/detail/suppress_unused.hpp"
#include "boost/lambda/core.hpp"

#include <typeinfo>

namespace boost { 
namespace lambda {

template<class Act, class Args>
struct return_type_N;

template<class T> class cast_action;

template<class T> class static_cast_action;
template<class T> class dynamic_cast_action;
template<class T> class const_cast_action;
template<class T> class reinterpret_cast_action;

class typeid_action;
class sizeof_action;

// Cast actions

template<class T> class cast_action<static_cast_action<T> > 
{
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return static_cast<RET>(a1);
  }
};

template<class T> class cast_action<dynamic_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return dynamic_cast<RET>(a1);
  }
};

template<class T> class cast_action<const_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return const_cast<RET>(a1);
  }
};

template<class T> class cast_action<reinterpret_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return reinterpret_cast<RET>(a1);
  }
};

// typeid action
class typeid_action {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    detail::suppress_unused_variable_warnings(a1);
    return typeid(a1);
  }
};

// sizeof action
class sizeof_action
{
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return sizeof(a1);
  }
};


// return types of casting lambda_functors (all "T" type.)

template<template <class> class cast_type, class T, class A>
struct return_type_N<cast_action< cast_type<T> >, A> { 
  typedef T type;
};

// return type of typeid_action
template<class A>
struct return_type_N<typeid_action, A> { 
  typedef std::type_info const & type;
};

// return type of sizeof_action

template<class A>
struct return_type_N<sizeof_action, A> { 
  typedef std::size_t type;
};


// the four cast & typeid overloads.
// casts can take ordinary variables (not just lambda functors)

// static_cast 
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<static_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_static_cast(const Arg1& a1) { 
  return 
    lambda_functor_base<
      action<1, cast_action<static_cast_action<T> > >, 
      tuple<typename const_copy_argument <const Arg1>::type> 
    >
  ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// dynamic_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<dynamic_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_dynamic_cast(const Arg1& a1) { 
  return 
    lambda_functor_base<
      action<1, cast_action<dynamic_cast_action<T> > >, 
      tuple<typename const_copy_argument <const Arg1>::type>
    > 
  ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// const_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<const_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_const_cast(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, cast_action<const_cast_action<T> > >, 
        tuple<typename const_copy_argument <const Arg1>::type>
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// reinterpret_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<reinterpret_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_reinterpret_cast(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, cast_action<reinterpret_cast_action<T> > >, 
        tuple<typename const_copy_argument <const Arg1>::type> 
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// typeid
// can be applied to a normal variable as well (can refer to a polymorphic
// class object)
template <class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, typeid_action>, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_typeid(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, typeid_action>, 
        tuple<typename const_copy_argument <const Arg1>::type>
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// sizeof(expression)
// Always takes a lambda expression (if not, built in sizeof will do)
template <class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, sizeof_action>, 
    tuple<lambda_functor<Arg1> >
  > 
>
ll_sizeof(const lambda_functor<Arg1>& a1) { 
  return 
      lambda_functor_base<
        action<1, sizeof_action>, 
        tuple<lambda_functor<Arg1> >
      > 
      ( tuple<lambda_functor<Arg1> >(a1));
}

} // namespace lambda 
} // namespace boost

#endif

/* casts.hpp
EB6Qg0p5foQNbKWLlVgIgAtqMcTnQlARc8uiqJpSA/rnXo5ZoE9swWsBhBmfHqII400vf4bp7WrmMEh2LjElDgi1M2PUjx8pNes3jH71ML6N/uPlkCh8LBkXhGl8AxXyiB044r4cujEt7do00OSkY5N78Y4Vv4sLC+YnMQTXBorFoE+jaHl3KWZPleRRGaKNVHMxWuBaIv3oW1meL1lM9kGjPZRQyhep8cyBXt0Ee/d0LnyDtOdN6AOSbp5gWIDn1e8N9mI/7SO7oaUDyM9ZYWvg2hhvISNLEDuXSGjCafHwB4j4D5t6tgoQMTMVSaW6BykUhaglZ/QZZ5aaPWYjtVLwO4EmAyFaz1IZ4hc0cURnrbnK5Dv4mMvz7fXAWss3IoEwsHzseagcjGzmg4q0u4O1OaCqh5/g6KdkdDeKycLMLeq/703ktkWTgpPwykQxk54nFM7kxqWiIq02yv55lgHt8sMiFTCKWBLu/DuSm6WK0pZVbEekFeTVuuikSP/BVG9TXkhXeFp2F0Jkt2hTSgL7Z0w8s9SWFEEjSrAkppH/aKyCM580M8p49CI9h+szX/4xLxcu3H5VzCS+kK9rq7C95lxx+eSjpYowjlHyTOIuNVhc90EzX9dhSFtKMkGcOdkynQGdULyzNPgUFsflWGBfOHhvTqkAsOTjG4H8UdUzyltbQ1VeD4XPM1nAwZ7AOAPJf9pJa9yzOFux
*/