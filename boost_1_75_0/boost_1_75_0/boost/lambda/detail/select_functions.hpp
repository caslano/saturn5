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
+llr5MC89LX/ZqILtvbaLj00XEIw952bgpK9vLSzu6P4n+22tqutDNNagOWwmLG+nMts+9Mm32bfZuY2q/UFl6p5VauJDIqCVta+FMiv/kX+/eZFZf0cPe5A3qFgZuzektRJ71guXEuZDXwPQpFY7ybNTGuh7dOmUeGPAY4DFzrYp8IKa7WhdcgcTPMSNDY0VxJmb0tyKxkEY1GnWCmLjPTgcuqbpumftpKE1Iq+jll/GVMbCfjY+LuSOomx36nfWhrHryNn0ic3dERbjo+ApiDF5z4PWPYQG3a7Fsbd26V1flpivJnT6Y94hh0etpjE9snfOYutVw+6G0VRV+M3GsCJb6/eBF8bHQweOue6uhwr5bqdNtForL90LJoW9cJBpJyLBvkXjmnVjtl7pyhD2gYvXSvMZQ+FTwqlWjPufrqsJd9rCv889EJjbHS8PPSH/V6tKNg2WCQW1/IoQZttGlhQPVM435kp1xcNeinqOHZMPA/ZivKpyFNiR0cWC34ldD7+4BjdZQ3gwFfRIZJeFHU+4Zv5knqHttifNzMb9aYBXzTnatqK3dOwcvzgDSh5IwiI6xAnS7DQc+zApimjrg9jy4vikolpKSdFnBxLwaBHVaGd9/NPR+h2R4hm2MuwiPDY8LcIh6vUpDG98D/0kBT7z37BRD/aZj0K69OlNbTnBJr3y5NmW5oPOm7A7vFQr1932LmuoDkoTAKG
*/