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
4dNOS6MMjGAuvf5xr3BOLmDem6UM7KwhxSZjxShONIjuTpG28I5xDyhyjWI3MJ+UJziL3eLne8YegsRnYnqllLkowFbmEEPpZrNeB5JjPG3xOCZ+tVpUz8Vj3HQcS4430yH9CTIm5DqxMeRsV/ezWkDRZKc/jUJjI5a2uqEWyqO3aMgeQEDCAjv9iWsFZmtJy5iuOLzjmFLHK+d1Yom/dut7LXnLaiHyQH9zdIs3qA2jitAJIExzH6tvKoQMLVDH8UqgABXu6ysXg8PLLxFAGfpC1ZCCUIS6WZNDY/cFoW07xo7ydqbUkOY7t3yDoD32zjTHxKacAjY20AgXcRnE0JR//eIsF5DQcRJerlyF9WAtjyXGGV1h0MBsmt0hPBREgrgugUob9LATxwCExtUo/IIPd5YDc1rWqC2q3uhzakRZZicS7eosQhwmU/YJnLn7eBPDVIs+KOgoO1SsrOCNDunkIOMHVpgEv40+5hoQ4lMg3Cm9jmSvq4i/DtGzZX2ry6Sy3o3n3Ltr86wHIorsEqtHzJJzisyoFfRmbG/M2CWSItsATHd6FKx4FQ==
*/