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
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
*/