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
YH1geyDT4byuffmeb6mvm2pJpz7TCWE6oUwnzJLO9lrSqWdtF7Wk8zH19xnr61GW7zFru6glnY+s7SK45nQaMz/RzE8M89NM5wcUXHM6EZb8JNaSzo/Mj4vpuJlOAFDXg1rSOW1pBwXkG2HTDuL4rZj2wFBgPPcWdOK3cDpzz0kCv5XSBTgM2A04HNgdqMvHK49NfhYxP7exfMqAIcA7dflwDgkQYZOfheRLMHnJF2DTr25lOr9jOr+3xJ/gqbmdPqPbKcgrh0073cX432D8bzIfbwFl7GHtpxhPlE16r1nyU1JLfq5neiVMbwFQt89a8jOffAWgNeTLJl+w3NPmyP+hKcCuwKnAHsCrgb3NeIAXAfOAg4AzgcOAhcAxwDnACcB5wCzy89s8HEvjv5bpWr/NcxnTHcz3hKHAhsDhwPOAo4BNgeOAzYFplG8C0Ku3DG/8NnprxXqNZwnXRtdTjjtrqKeXsH0nsb31B4YAB1j7qwY119N+5t44109/62UZaNGSQLUatBW0B3QUpH4dqGJAyaBc0DLQblDQLYEqDpQGmgfaBCoHnQSFlwaqeFAqaBFoOWgLaD/oFCjh1kA1FDQPtBq0G1QBar00UCWCCkCLQGtAvbD/JxVUCPLdE1QBDB125t6gPjdU7g9K9dkjtBPx+e4TOgn0XFm5XygeaL9nCLiw+r6hrbgvB7lS4LYI+1WAyaDF8MsF7lnq1HuKivG8DbjHZ2/RJu/+ohuxjyUFaO4rGuBWFSlV+40ihyPvpvuN9vuOin32Hm0E7gDZ7T9af1PVHqRNg7HPZkTlXqQ4YCKopj1JxXBbDUq+BH7ADOAhYE17lAq4T2kLaJ9lv9Kp3S7Zs3RyZO3fyokchXhNN2AKyLuHKXeU3sckL8vLQN79TFvMe1DZr6vva4odXfvepnLL/qbwMVV7nNKAJaA1oIQh1fc87eO+p0OoT3bf2ym5peY9UKlwKwatBm0F1bQn6ijcgkqr741qDRrKPVKlPvuk1qRW7ZXamQrZQL57ptQ46PMNl+ydisP9IFAG91CVAFeDzL1UrtvQFkHJoFxQKWgL6BDIUxao+oDSQCWgNaAdoEMgz+1o26A00CLQFtB+kOeOQNUNlA0qBW0FHQKF3ok0QLmgZaCtoHJQ6DLs5QIVgJaBtoPKl/n3cPkv/+W//Jf/8l/+y3/5L//lv/yX//rfuP7F3/+bmp2TmTY1fTa25P/87/+Ze1jH6+/3iV1TriWcV10Mmm+eGY5dnqZJMfnSpHRsJ8MRhiJNOoSQ9UPXyZqonGk1nOPL8IaFN1t4G/LM6afFf4H9meAMW79q7aY+h/pP4jfLckZ1Ife7mloIhl9bPMPPJbPSBd40I4E7JOxIi3+h9m8C/IP45+k9aldFg2zWOYbWsG7JzGcEdcLzD+mGvPvsxxvExU+pBvyBY4G/Am8G8mDVe06+1rvtNwvOA2ZLmNVyljaiZRzNtE7p5lMe06qtZcsX/zvsyoNhreUxVev0CsP0m8JnZEKeY7Qs8yXsxUZDXV6zKs+UpewXCH8G4m4G20hTLY9D3Bsxj4Z6Sp7dyhJPV2t9ChT/W/js5Xda+ROUZb91f/FPNiXVeYkRt/qUwRuHw1JfphUqyxriHyVvz9a5fuizks+oH9P0+r7O3rNc3UqukSCvze35Noi7cm/51PxrcrDNU+n8Gap4ar59W5QwLHuu5ZzUxaq7ePFvL+XbyKe99RS/dvrc9wR5DrTwFup6eJn4efjs5XVa0s2XdBtR323EvzNsHo0s8c3U+9P7iX8LpNbQGkdXazlGCM8V4KmWv67WcsoUHofuJzrIc886l5ucRU39etfuRYKWtDbX1jX4c0Q=
*/