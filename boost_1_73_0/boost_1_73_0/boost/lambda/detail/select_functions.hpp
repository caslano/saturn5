// -- select_functions.hpp -- Boost Lambda Library --------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org


#ifndef BOOST_LAMBDA_SELECT_FUNCTIONS_HPP
#define BOOST_LAMBDA_SELECT_FUNCTIONS_HPP

namespace boost { 
namespace lambda {
namespace detail {


// select functions -------------------------------
template<class Any, CALL_TEMPLATE_ARGS>
inline Any& select(Any& any, CALL_FORMAL_ARGS) { CALL_USE_ARGS; return any; }


template<class Arg, CALL_TEMPLATE_ARGS>
inline typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
select ( const lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) { 
  return op.template call<
    typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
  >(CALL_ACTUAL_ARGS); 
}
template<class Arg, CALL_TEMPLATE_ARGS>
inline typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
select ( lambda_functor<Arg>& op, CALL_FORMAL_ARGS) { 
  return op.template call<
    typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
  >(CALL_ACTUAL_ARGS); 
}

// ------------------------------------------------------------------------
// select functions where the return type is explicitly given
// Note: on many functions, this return type is just discarded.
// The select functions are inside a class template, and the return type
// is a class template argument.
// The first implementation used function templates with an explicitly 
// specified template parameter.
// However, this resulted in ambiguous calls (at least with gcc 2.95.2 
// and edg 2.44). Not sure whether the compilers were right or wrong. 
  
template<class RET> struct r_select {

// Any == RET
  template<class Any, CALL_TEMPLATE_ARGS>
  static 
  inline RET go (Any& any, CALL_FORMAL_ARGS) { CALL_USE_ARGS; return any; }


  template<class Arg, CALL_TEMPLATE_ARGS> 
  static 
  inline RET go (const lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) {
    return op.template call<RET>(CALL_ACTUAL_ARGS); 
  }
  template<class Arg, CALL_TEMPLATE_ARGS> 
  static 
  inline RET go (lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) { 
    return op.template call<RET>(CALL_ACTUAL_ARGS); 
  }
};
   
} // namespace detail
} // namespace lambda
} // namespace boost

#endif

/* select_functions.hpp
ZDr5EP7Pz5aT+WyX7ahaPlllgRsPQ9so4Tx0EM6a23Rgim+B7Lf8Cqsc0+a65XM2NpKJqGvUeX8A64kDAZxjfc0l48Ioqf+jdDN+tK5I0eiM+xcyKkCKLNe094UWpJZeCiW/i4DpwLS7ouZqUWu3bpezH/fIuKE31SY2GO5H+RuAJ1Hvz69EGhn1qYesFBaGufBi0PtBpFaNb1YSJGGocZVIjxW831neuM8uplO6M8w/6hFfFv1nG8IgBGGpwlYDAzsEKwzgR9gPJu/pkiplsr6T39EU+4carMV/J8NuSIVFTEim3wVw1IIexMALP3ud9+FxIW0IYUM72tkLLbW/1coxgheC2BZ+eKzxdp/0QG0fy4AHmj9DS6cImt674f2SKaQOaWrCOdPYjDqbmuPGyHzbtt35H22JdX27BO4cJOT2sTzupCekkjfC4iCE+JwaQBZAkf7hznKYvwBQSwMECgAAAAgALWdKUirFegUJAwAA3QYAABoACQBjdXJsLW1hc3Rlci9zcmMvc2xpc3Rfd2MuaFVUBQABtkgkYK1VwW7bOBC9+ysekktiqFbb02ZTLNa13UbY1A5sF0GAAAQtjSJuaVIgKTtGs//eoeQm7SZpLqVhkSJn5r03M5IOVWkKKnE2GY4nczH6PD8X
*/