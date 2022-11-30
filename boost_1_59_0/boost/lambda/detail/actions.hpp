// -- Boost Lambda Library - actions.hpp ----------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see www.boost.org

// ----------------------------------------------------------------

#ifndef BOOST_LAMBDA_ACTIONS_HPP
#define BOOST_LAMBDA_ACTIONS_HPP

namespace boost { 
namespace lambda {



template<int Arity, class Act> class action;

// these need to be defined here, since the corresponding lambda 
// functions are members of lambda_functor classes

class assignment_action {};
class subscript_action {};

template <class Action> class other_action;

// action for specifying the explicit return type
template <class RET> class explicit_return_type_action {};

// action for preventing the expansion of a lambda expression
struct protect_action {};

  // must be defined here, comma is a special case
struct comma_action {};


  // actions, for which the existence of protect is checked in return type 
  // deduction.

template <class Action> struct is_protectable {
  BOOST_STATIC_CONSTANT(bool, value = false);
};

// NOTE: comma action is protectable. Other protectable actions
// are listed in operator_actions.hpp

template<> struct is_protectable<other_action<comma_action> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};


namespace detail {

  // this type is used in return type deductions to signal that deduction 
  // did not find a result. It does not necessarily mean an error, it commonly
  // means that something else should be tried.
  class unspecified {};
}

  // function action is a special case: bind functions can be called with 
  // the return type specialized explicitly e.g. bind<int>(foo);
  // If this call syntax is used, the return type is stored in the latter
  // argument of function_action template. Otherwise the argument gets the type
  // 'unspecified'.
  // This argument is only relevant in the return type deduction code
template <int I, class Result_type = detail::unspecified> 
class function_action {};
   
template<class T> class function_action<1, T> {
public:
  template<class RET, class A1>
  static RET apply(A1& a1) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1);
  }
};

template<class T> class function_action<2, T> {
public:
  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2);
  }
};

template<class T> class function_action<3, T> {
public:
  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3);
  }
};

template<class T> class function_action<4, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4);
  }
};

template<class T> class function_action<5, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5);
  }
};

template<class T> class function_action<6, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6);
  }
};

template<class T> class function_action<7, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5,  
           class A6, class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7);
  }
};

template<class T> class function_action<8, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template<class T> class function_action<9, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }
};

template<class T> class function_action<10, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9, A10& a10) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }
};

} // namespace lambda
} // namespace boost

#endif

/* actions.hpp
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
*/