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