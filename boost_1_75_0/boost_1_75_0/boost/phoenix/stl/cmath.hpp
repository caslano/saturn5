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
MmqNFLO9CN+55c2O5B7eCH+9R662h6byr+wfMA846P9hri0bE6HUpFjSEnYhh86J66ZZop/YlxtxmfXw2kew326pS2dm7jqgUoMKgLzAZhkK4Vyi8PazO8dWqXIQ/bX6VFG3UdDPLK4dxT7nQ/HJvU62xFJsUtEZ/3eHP+azslKJS2+GviMsZ+AlrIB1Sw+kPkuu+vPh816nc/1FGZW9XIfujFnpJAb6/nAfxu2zhE9SXrWZ4r2GUFXsLnfbtp6Z4eG19Ss2kwGu0XbAxTOfI41ogHkg/7VWZen3cbdvvjhmtfmxF4jX15dSpc8PEqNbU4niYMGLau/QRcVS93ltATQuNULlTzi+NsT/jLXAAPsohV6z3Zz/Bn/QHs/qcD3lmjFV3bsuyONLetlIiFfeFAZ8dhZDhBm6LoK3bo0+tTjkNzWlpUubaKguFMt6r5o3hA/m4czOReU/cU/RWgDVjypeHYpNsnkBHT+BxMgDyMRtP5mte/lJBufURhy8OaJGDwU7DrkYFMIHJ+lNHTJFV4zCXJ8e/cMOojjk7f31x0T0FF/1xWXXGxFwK1hMa6S3Xk11ia9rZGvWdwlpiHqcxLU/4WXjm0bHYyuUpN0r0cpoQM4+TmXmgq78ffew5gkVUjwtteFnD9+a6ulrCNOW0k+i1vfGfN6gV5rpLznAIclDsXxTH6zaF8de+3wtlXri8+hVBZ3vE/ESthTc
*/