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
T3+O//73X3/66c/wr3/+z3T/NY1//nf9a/ljrP/0pv/7I/4XRwL/QHFucr5tbWtcyyTvyoa3wdJfoDLGCqdylAqjYAS+HK2FXxBpO8oiTubXpFwYTI0+AjpejhZGJlsWQYOX1r1NXMzsDyR7Ojea2jQwMETZX7Z+jqlLiC3/ORp3AxHmi5WGJgKRpW2Dp7O1MZ8VM3Gjq5lfSX81yCu1QFB5gSD4n7uDCwmCr/8cOaad40ylYmdWgd79qlFmKWBmgij4XC48l9UIndF20OdS9Dz+yDa4A0JUHj+D2XjwTAU8QGNR+2e6QGUsYO3hUwmCaAvGIqZhIqKOMQa+kPuZ+zNADoLU8zPT55x7P2co0kJw68pk0xsA1OpMYnh68Zq1OsgX/cIlRgXtzaY1blcT1TbfifjLkmQRslvTijCANI5xulxMMCfsgI+RkeKnL6aeNkx0u7zv1xebOTbcMn7hmWhM3mgdsMe2KiLidh7YAa/Ig02+SkJ5sznAv9dApCXWK1bO8htNKo3s6/UvjnsLLFt/jy327HnUyWgpwzQYcJ3WftNxiXGLp5NpAM/6fe2qDN/K+ydWdfIbeMZFj5cKNeOp1MeAN9N7ZLYzKxZJkrxvOQptqkLv2zXavbMB4qZBUrkVK8bVX18V36li
*/