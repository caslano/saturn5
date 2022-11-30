// Boost Lambda Library - is_instance_of.hpp ---------------------

// Copyright (C) 2001 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_IS_INSTANCE_OF
#define BOOST_LAMBDA_IS_INSTANCE_OF

#include "boost/config.hpp" // for BOOST_STATIC_CONSTANT
#include "boost/type_traits/conversion_traits.hpp" // for is_convertible
#include "boost/preprocessor/enum_shifted_params.hpp"
#include "boost/preprocessor/repeat_2nd.hpp"

// is_instance_of --------------------------------
// 
// is_instance_of_n<A, B>::value is true, if type A is 
// an instantiation of a template B, or A derives from an instantiation 
// of template B
//
// n is the number of template arguments for B
// 
// Example:
// is_instance_of_2<std::istream, basic_stream>::value == true

// The original implementation was somewhat different, with different versions
// for different compilers. However, there was still a problem
// with gcc.3.0.2 and 3.0.3 compilers, which didn't think regard
// is_instance_of_N<...>::value was a constant.
// John Maddock suggested the way around this problem by building 
// is_instance_of templates using boost::is_convertible.
// Now we only have one version of is_instance_of templates, which delagate
// all the nasty compiler tricks to is_convertible. 

#define BOOST_LAMBDA_CLASS(z, N,A) BOOST_PP_COMMA_IF(N) class
#define BOOST_LAMBDA_CLASS_ARG(z, N,A) BOOST_PP_COMMA_IF(N) class A##N 
#define BOOST_LAMBDA_ARG(z, N,A) BOOST_PP_COMMA_IF(N) A##N 

#define BOOST_LAMBDA_CLASS_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS, NAME)

#define BOOST_LAMBDA_CLASS_ARG_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS_ARG, NAME)

#define BOOST_LAMBDA_ARG_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_ARG, NAME)

namespace boost {
namespace lambda {

#define BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE(INDEX)                         \
                                                                            \
namespace detail {                                                          \
                                                                            \
template <template<BOOST_LAMBDA_CLASS_LIST(INDEX,T)> class F>               \
struct BOOST_PP_CAT(conversion_tester_,INDEX) {                             \
  template<BOOST_LAMBDA_CLASS_ARG_LIST(INDEX,A)>                            \
  BOOST_PP_CAT(conversion_tester_,INDEX)                                    \
    (const F<BOOST_LAMBDA_ARG_LIST(INDEX,A)>&);                             \
};                                                                          \
                                                                            \
} /* end detail */                                                          \
                                                                            \
template <class From, template <BOOST_LAMBDA_CLASS_LIST(INDEX,T)> class To> \
struct BOOST_PP_CAT(is_instance_of_,INDEX)                                  \
{                                                                           \
 private:                                                                   \
   typedef ::boost::is_convertible<                                         \
     From,                                                                  \
     BOOST_PP_CAT(detail::conversion_tester_,INDEX)<To>                     \
   > helper_type;                                                           \
                                                                            \
public:                                                                     \
  BOOST_STATIC_CONSTANT(bool, value = helper_type::value);                  \
};


#define BOOST_LAMBDA_HELPER(z, N, A) BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE( BOOST_PP_INC(N) )

// Generate the traits for 1-4 argument templates

BOOST_PP_REPEAT_2ND(4,BOOST_LAMBDA_HELPER,FOO)

#undef BOOST_LAMBDA_HELPER
#undef BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE
#undef BOOST_LAMBDA_CLASS
#undef BOOST_LAMBDA_ARG
#undef BOOST_LAMBDA_CLASS_ARG
#undef BOOST_LAMBDA_CLASS_LIST
#undef BOOST_LAMBDA_ARG_LIST
#undef BOOST_LAMBDA_CLASS_ARG_LIST

} // lambda
} // boost

#endif






/* is_instance_of.hpp
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
*/