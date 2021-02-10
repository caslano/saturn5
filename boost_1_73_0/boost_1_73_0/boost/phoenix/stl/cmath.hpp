/*==============================================================================
    Copyright (c) 2011 Steven Watanabe

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_CMATH_HPP_INCLUDED
#define BOOST_PHOENIX_CMATH_HPP_INCLUDED

#include <boost/phoenix/core/limits.hpp>
#include <cmath>
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost {

#if (defined (BOOST_NO_CXX11_DECLTYPE) || \
     defined (BOOST_INTEL_CXX_VERSION) || \
             (BOOST_GCC_VERSION < 40500) )
#define BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)                \
    typename proto::detail::uncvref<A0>::type
#else
#define BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)                \
    decltype(name(BOOST_PP_ENUM_BINARY_PARAMS(                          \
                      n                                                 \
                    , boost::declval<typename proto::detail::uncvref<A  \
                    ,  >::type>() BOOST_PP_INTERCEPT)))
#endif
#define BOOST_PHOENIX_MATH_FUNCTION(name, n)                            \
    namespace phoenix_impl {                                            \
    struct name ## _impl {                                              \
        template<class Sig>                                             \
        struct result;                                                  \
        template<class This, BOOST_PHOENIX_typename_A(n)>               \
        struct result<This(BOOST_PHOENIX_A(n))>                         \
        {                                                               \
            typedef                                                     \
                BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)        \
                type;                                                   \
        };                                                              \
        template<BOOST_PHOENIX_typename_A(n)>                           \
        typename result<name ## _impl(BOOST_PHOENIX_A(n))>::type        \
        operator()(BOOST_PHOENIX_A_const_ref_a(n)) const {              \
            using namespace std;                                        \
            return name(BOOST_PHOENIX_a(n));                            \
        }                                                               \
    };                                                                  \
    }                                                                   \
    namespace phoenix {                                                 \
    BOOST_PHOENIX_ADAPT_CALLABLE(name, phoenix_impl::name ## _impl, n)  \
    }

BOOST_PHOENIX_MATH_FUNCTION(acos, 1)
BOOST_PHOENIX_MATH_FUNCTION(asin, 1)
BOOST_PHOENIX_MATH_FUNCTION(atan, 1)
BOOST_PHOENIX_MATH_FUNCTION(atan2, 2)
BOOST_PHOENIX_MATH_FUNCTION(ceil, 1)
BOOST_PHOENIX_MATH_FUNCTION(cos, 1)
BOOST_PHOENIX_MATH_FUNCTION(cosh, 1)
BOOST_PHOENIX_MATH_FUNCTION(exp, 1)
BOOST_PHOENIX_MATH_FUNCTION(fabs, 1)
BOOST_PHOENIX_MATH_FUNCTION(floor, 1)
BOOST_PHOENIX_MATH_FUNCTION(fmod, 2)
BOOST_PHOENIX_MATH_FUNCTION(frexp, 2)
BOOST_PHOENIX_MATH_FUNCTION(ldexp, 2)
BOOST_PHOENIX_MATH_FUNCTION(log, 1)
BOOST_PHOENIX_MATH_FUNCTION(log10, 1)
BOOST_PHOENIX_MATH_FUNCTION(modf, 2)
BOOST_PHOENIX_MATH_FUNCTION(pow, 2)
BOOST_PHOENIX_MATH_FUNCTION(sin, 1)
BOOST_PHOENIX_MATH_FUNCTION(sinh, 1)
BOOST_PHOENIX_MATH_FUNCTION(sqrt, 1)
BOOST_PHOENIX_MATH_FUNCTION(tan, 1)
BOOST_PHOENIX_MATH_FUNCTION(tanh, 1)

#undef BOOST_PHOENIX_MATH_FUNCTION

}

#endif

/* cmath.hpp
X148QorsnEga4ykkc7LjXQzsBHokKZ0Watiw9IXto4NaGHk/oglstZPT2kFVyU0EiDjJNlkRnQd8Ah8KMjbI3TPeC7gXQWlvWipsLwt7PwmoGbrFNgWu3l1Pbi9/ppf/vXx788tLbnE0dXeSTH4V6NLL21JLE0NSjbjMtRG4/4b6+4CA53lySs9wQeW/PVzSt98iVgKUkPplizs0m7G9k8FYRtDdF8VefkVrhJ+6W1Kwu2ZImzOQzubYf2HRU7ehQSIdR9d54PavSjNIYrvU901GlaX+CVBhKweJ9G3DroHzDf+KAJpkxN42bmZxAT49HQylwgEvi4sBVhR/ChA6kJpxEBuyAxY6SLi4nV3sNbCwRu5CUDtrFnHJ+Z8sMfXqX4Mk+SZeM4XUWGNy0NlEB6KBPtMBq+2WelBrlT+59rxf+39QSwMECgAAAAgALWdKUsh+LKGNGQAAT1MAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy90ZXN0Y3VybC5wbFVUBQABtkgkYOU8aVPbyLbf/Ssa4bq2GS+B2d7FcWYYs4QaAikgk0pB4pGltq2LLHm0YKgJ97e/c06vkmUgyXx4VS8zCXar+3SffekjNjd6eZr0xkHU49EtW/AkrG1u/XN/apvsyT8j+juCP/AT
*/