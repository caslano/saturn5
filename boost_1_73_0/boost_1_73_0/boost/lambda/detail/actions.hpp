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
WKXGtJvHLn6DiX78fHrNoqZkTm7MtWrITlWxDhk1s1Hgy0sjDmw1mA4gR977pd88hUyVBycvy2+vU4PG+Vg//K2wnloe7wH5UHgheTgrNdRJZiZu7yDSCwH0AzIu30GdJMR6Lyowm+BSKkhaawLo5ifWGH+JM7VPV96cNYRQkRvTz/0FE0NJw1lycQpkxPiSFOUTPTMDeTYzFPfbvrnJ9x+tUmUyGsGkRzHx4yd2luLxi9502ljVtIIv83B9QNJXpinY6A0/eyi+1LjEPtagLNmOdJ/tJalsfx1WUJPu2pX8j29+ZB/Wwk3k1NC40wagFnlQmkZP7tU7gqgW5Jycv5OUJy64vdWgmrdCqbObsHpOb9lwrvDM0TlHf7RqwHMBGAdO/PWqzAd8MJpS/LGLFxcHaVWXAbzN494jDJffFbQ95vbLKyX4VCT7ad1NXicPlwHUpD5m1pKvOtWaUgBRkE2D98lv9kcwj10Wmate4o7E9XW0PnzVn5r8QKfC7XQye+cIVHzpQA3X3CBiUPFljZ6hSuSuNLyPUtHNwBNWvUxzjRyzUcZNzaz3uJBfmWFm80ekMHA+CpA9eKvFFuFru7UYBRr/VPe2UL9iqgdC2EIdbCI3elfAyuEnD5LPG0Oos9UQODrAMV+Iahze
*/