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
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
*/