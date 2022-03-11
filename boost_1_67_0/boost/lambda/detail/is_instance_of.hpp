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