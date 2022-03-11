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