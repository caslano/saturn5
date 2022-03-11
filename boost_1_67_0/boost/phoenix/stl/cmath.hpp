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